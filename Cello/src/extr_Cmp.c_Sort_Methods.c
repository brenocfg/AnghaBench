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

__attribute__((used)) static struct Method* Sort_Methods(void) {
  
  static struct Method methods[] = {
    {
      "sort", 
      "void sort(var self);",
      "Sorts the object `self`."
    }, {
      "sort_by", 
      "void sort_by(var self, bool(*f)(var,var));",
      "Sorts the object `self` using the function `f`."
    }, {NULL, NULL, NULL}
  };
  
  return methods;
}