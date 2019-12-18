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

__attribute__((used)) static struct Method* Push_Methods(void) {
  
  static struct Method methods[] = {
    {
      "push", 
      "void push(var self, var obj);",
      "Push the object `obj` onto the top of object `self`."
    }, {
      "pop", 
      "void pop(var self);",
      "Pop the top item from the object `self`."
    }, {
      "push_at", 
      "void push_at(var self, var obj, var key);",
      "Push the object `obj` onto the object `self` at a given `key`."
    }, {
      "pop_at", 
      "void pop_at(var self, var key);",
      "Pop the object from the object `self` at a given `key`."
    }, {NULL, NULL, NULL}
  };
  
  return methods;
}