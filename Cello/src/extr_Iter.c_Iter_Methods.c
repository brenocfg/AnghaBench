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

__attribute__((used)) static struct Method* Iter_Methods(void) {
  
  static struct Method methods[] = {
    {
      "foreach", 
      "#define foreach(...)\n",
      "Iterate over elements in a loop."
    }, {
      "iter_init", 
      "var iter_init(var self);\n"
      "var iter_last(var self);",
      "Return the initial item (or final item) in the iteration over `self`."
    }, {
      "iter_next", 
      "var iter_next(var self, var curr);\n"
      "var iter_prev(var self, var curr);",
      "Given the current item `curr`, return the next (or previous) item in "
      "the iteration over `self`."
    }, {
      "iter_type", 
      "var iter_type(var self);",
      "Returns the type of item that can be expected to be returned by the "
      "iterable."
    }, {NULL, NULL, NULL}
  };
  
  return methods;
}