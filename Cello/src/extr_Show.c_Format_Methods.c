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

__attribute__((used)) static struct Method* Format_Methods(void) {
  
  static struct Method methods[] = {
    {
      "format_to", 
      "int format_to(var self, int pos, const char* fmt, ...);\n"
      "int format_to_va(var self, int pos, const char* fmt, va_list va);",
      "Write a formatted string `fmt` to the object `self` at position `pos`."
    }, {
      "format_from", 
      "int format_from(var self, int pos, const char* fmt, ...);\n"
      "int format_from_va(var self, int pos, const char* fmt, va_list va);",
      "Read a formatted string `fmt` from the object `self` at position `pos`."
    }, {NULL, NULL, NULL}
  };
  
  return methods;
}