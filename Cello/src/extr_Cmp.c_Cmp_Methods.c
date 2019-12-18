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

__attribute__((used)) static struct Method* Cmp_Methods(void) {
  
  static struct Method methods[] = {
    {
      "cmp", 
      "int cmp(var self, var obj);",
      "The return value of `cmp` is `< 0` if `self` is less than `obj`, `> 0` "
      "if `self` is greater than `obj` and `0` if they are equal."
    }, {
      "eq", 
      "bool eq(var self, var obj);",
      "Returns true if the object `self` is equal to the object `obj`."
    }, {
      "neq", 
      "bool neq(var self, var obj);",
      "Returns false if the object `self` is equal to the object `obj`."
    }, {
      "gt", 
      "bool gt(var self, var obj);",
      "Returns true if the object `self` is greater than the object `obj`."
    }, {
      "lt", 
      "bool lt(var self, var obj);",
      "Returns false if the object `self` is less than the object `obj`."
    }, {
      "ge", 
      "bool ge(var self, var obj);",
      "Returns false if the object `self` is greater than or equal to the "
      "object `obj`."
    }, {
      "le", 
      "bool le(var self, var obj);",
      "Returns false if the object `self` is less than or equal to the "
      "object `obj`."
    }, {NULL, NULL, NULL}
  };
  
  return methods;
}