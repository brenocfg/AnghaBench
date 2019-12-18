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

__attribute__((used)) static struct Method* Type_Methods(void) {

  static struct Method methods[] = {
    {
      "type_of", 
      "var type_of(var self);",
      "Returns the `Type` of an object `self`."
    }, {
      "instance", 
      "var instance(var self, var cls);\n"
      "var type_instance(var type, var cls);",
      "Returns the instance of class `cls` implemented by object `self` or "
      "type `type`. If class is not implemented then returns `NULL`."
    }, {
      "implements", 
      "bool implements(var self, var cls);\n"
      "bool type_implements(var type, var cls);",
      "Returns if the object `self` or type `type` implements the class `cls`."
    }, {
      "method", 
      "#define method(X, C, M, ...)\n"
      "#define type_method(T, C, M, ...)",
      "Returns the result of the call to method `M` of class `C` for object `X`"
      "or type `T`. If class is not implemented then an error is thrown."
    }, {
      "implements_method", 
      "#define implements_method(X, C, M)\n"
      "#define type_implements_method(T, C, M)",
      "Returns if the type `T` or object `X` implements the method `M` of "
      "class C."
    }, {NULL, NULL, NULL}
  };
  
  return methods;
  
}