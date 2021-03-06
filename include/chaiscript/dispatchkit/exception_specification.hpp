// This file is distributed under the BSD License.
// See "license.txt" for details.
// Copyright 2009-2011, Jonathan Turner (jonathan@emptycrate.com)
// and Jason Turner (jason@emptycrate.com)
// http://www.chaiscript.com

#ifndef CHAISCRIPT_EXCEPTION_SPECIFICATION_HPP_
#define CHAISCRIPT_EXCEPTION_SPECIFICATION_HPP_

#include "boxed_cast.hpp"

namespace chaiscript
{
  namespace detail
  {
    struct Exception_Handler_Base
    {
      virtual void handle(const Boxed_Value &bv) = 0;

      protected:
        template<typename T>
        void throw_type(const Boxed_Value &bv)
        {
          try { T t = boxed_cast<T>(bv); throw t; } catch (const exception::bad_boxed_cast &) {}
        }
    };

    template<typename T1>
      struct Exception_Handler_Impl1 : Exception_Handler_Base
      {
        virtual void handle(const Boxed_Value &bv)
        {
          throw_type<T1>(bv);
        }
      };
    template<typename T1, typename T2>
      struct Exception_Handler_Impl2 : Exception_Handler_Base
      {
        virtual void handle(const Boxed_Value &bv)
        {
          throw_type<T1>(bv);
          throw_type<T2>(bv);
        }
      };

    template<typename T1, typename T2, typename T3>
      struct Exception_Handler_Impl3 : Exception_Handler_Base
      {
        virtual void handle(const Boxed_Value &bv)
        {
          throw_type<T1>(bv);
          throw_type<T2>(bv);
          throw_type<T3>(bv);
        }
      };
    template<typename T1, typename T2, typename T3, typename T4>
      struct Exception_Handler_Impl4 : Exception_Handler_Base
      {
        virtual void handle(const Boxed_Value &bv)
        {
          throw_type<T1>(bv);
          throw_type<T2>(bv);
          throw_type<T3>(bv);
          throw_type<T4>(bv);
        }
      };
    template<typename T1, typename T2, typename T3, typename T4, typename T5>
      struct Exception_Handler_Impl5 : Exception_Handler_Base
      {
        virtual void handle(const Boxed_Value &bv)
        {
          throw_type<T1>(bv);
          throw_type<T2>(bv);
          throw_type<T3>(bv);
          throw_type<T4>(bv);
          throw_type<T5>(bv);
        }
      };
  }

  /// \brief Used in the automatic unboxing of exceptions thrown during script evaluation
  ///
  /// Exception specifications allow the user to tell ChaiScript what possible exceptions are expected from the script
  /// being executed. Exception_Handler objects are created with the chaiscript::exception_specification() function.
  ///
  /// Example:
  /// \code
  /// chaiscript::ChaiScript chai;
  ///
  /// try {
  ///   chai.eval("throw(runtime_error(\"error\"))", chaiscript::exception_specification<int, double, float, const std::string &, const std::exception &>());
  /// } catch (const double e) {
  /// } catch (int) {
  /// } catch (float) {
  /// } catch (const std::string &) {
  /// } catch (const std::exception &e) {
  ///   // This is the one what will be called in the specific throw() above
  /// }
  /// \endcode
  ///
  /// It is recommended that if catching the generic \c std::exception& type that you specifically catch
  /// the chaiscript::exception::eval_error type, so that there is no confusion.
  ///
  /// \code
  /// try {
  ///   chai.eval("throw(runtime_error(\"error\"))", chaiscript::exception_specification<const std::exception &>());
  /// } catch (const chaiscript::exception::eval_error &) {
  ///   // Error in script parsing / execution
  /// } catch (const std::exception &e) {
  ///   // Error explicitly thrown from script
  /// }
  /// \endcode
  ///
  /// Similarly, if you are using the ChaiScript::eval form that unboxes the return value, then chaiscript::exception::bad_boxed_cast
  /// should be handled as well.
  /// 
  /// \code
  /// try {
  ///   chai.eval<int>("1.0", chaiscript::exception_specification<const std::exception &>());
  /// } catch (const chaiscript::exception::eval_error &) {
  ///   // Error in script parsing / execution
  /// } catch (const chaiscript::exception::bad_boxed_cast &) {
  ///   // Error unboxing return value
  /// } catch (const std::exception &e) {
  ///   // Error explicitly thrown from script
  /// }
  /// \endcode
  ///
  /// \sa chaiscript::exception_specification for creation of chaiscript::Exception_Handler objects
  /// \sa \ref exceptions
  typedef boost::shared_ptr<detail::Exception_Handler_Base> Exception_Handler;

  /// \brief creates a chaiscript::Exception_Handler which handles one type of exception unboxing
  /// \sa \ref exceptions
  template<typename T1>
  Exception_Handler exception_specification()
  {
    return Exception_Handler(new detail::Exception_Handler_Impl1<T1>());
  }

  /// \brief creates a chaiscript::Exception_Handler which handles two types of exception unboxing
  /// \sa \ref exceptions
  template<typename T1, typename T2>
  Exception_Handler exception_specification()
  {
    return Exception_Handler(new detail::Exception_Handler_Impl2<T1, T2>());
  }

  /// \brief creates a chaiscript::Exception_Handler which handles three types of exception unboxing
  /// \sa \ref exceptions
  template<typename T1, typename T2, typename T3>
  Exception_Handler exception_specification()
  {
    return Exception_Handler(new detail::Exception_Handler_Impl3<T1, T2, T3>());
  }

  /// \brief creates a chaiscript::Exception_Handler which handles four types of exception unboxing
  /// \sa \ref exceptions
  template<typename T1, typename T2, typename T3, typename T4>
  Exception_Handler exception_specification()
  {
    return Exception_Handler(new detail::Exception_Handler_Impl4<T1, T2, T3, T4>());
  }

  /// \brief creates a chaiscript::Exception_Handler which handles five types of exception unboxing
  /// \sa \ref exceptions
  template<typename T1, typename T2, typename T3, typename T4, typename T5>
  Exception_Handler exception_specification()
  {
    return Exception_Handler(new detail::Exception_Handler_Impl5<T1, T2, T3, T4, T5>());
  }
}


#endif

