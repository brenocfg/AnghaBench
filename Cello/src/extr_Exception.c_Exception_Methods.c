#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct Method {char* member_0; char* member_1; char* member_2; } ;

/* Variables and functions */

__attribute__((used)) static struct Method* Exception_Methods(void) {
  
  static struct Method methods[] = {
    {
      "try", 
      "#define try",
      "Start an exception `try` block."
    }, {
      "catch", 
      "#define catch(...)",
      "Start an exception `catch` block, catching any objects listed in `...` "
      "as the first name given. To catch any exception object leave argument "
      "list empty other than caught variable name."
    }, {
      "#define throw",
      "throw(E, F, ...)",
      "Throw exception object `E` with format string `F` and arguments `...`."
    }, {
      "exception_signals",
      "void exception_signals(void);",
      "Register the standard C signals to throw corresponding exceptions."
    }, {
      "exception_object",
      "void exception_object(void);\n",
      "Retrieve the current exception object."
    }, {
      "exception_message",
      "void exception_message(void);\n",
      "Retrieve the current exception message."
    }, {NULL, NULL, NULL}
  };
  
  return methods;
}