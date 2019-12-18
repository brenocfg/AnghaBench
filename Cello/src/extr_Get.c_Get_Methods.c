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

__attribute__((used)) static struct Method* Get_Methods(void) {
  
  static struct Method methods[] = {
    {
      "get", 
      "var get(var self, var key);",
      "Get the value at a given `key` for object `self`."
    }, {
      "set", 
      "void set(var self, var key, var val);",
      "Set the value at a given `key` for object `self`."
    }, {
      "mem", 
      "bool mem(var self, var key);",
      "Returns true if `key` is a member of the object `self`."
    }, {
      "rem", 
      "void rem(var self, var key);",
      "Removes the `key` from object `self`."
    }, {
      "key_type", 
      "var key_type(var self);",
      "Returns the key type for the object `self`."
    }, {
      "val_type", 
      "var val_type(var self);",
      "Returns the value type for the object `self`."
    }, {NULL, NULL, NULL}
  };
  
  return methods;
}