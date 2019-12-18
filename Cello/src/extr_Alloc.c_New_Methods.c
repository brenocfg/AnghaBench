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

__attribute__((used)) static struct Method* New_Methods(void) {
  
  static struct Method methods[] = {
    {
      "new", 
      "#define new(T, ...)\n"
      "#define new_raw(T, ...)\n"
      "#define new_root(T, ...)\n"
      "var new_with(var type, var args);\n"
      "var new_raw_with(var type, var args);\n"
      "var new_root_with(var type, var args);",
      "Construct a new object of a given `type`. Use `new_raw` to avoid the "
      "Garbage Collector completely, and `new_root` to register the allocation "
      "as a Garbage Collection root. In the case of raw and root allocations "
      "they must be destructed with the corresponding deletion functions."
    }, {
      "del",
      "void del(var self);\n"
      "void del_raw(var self);\n"
      "void del_root(var self);",
      "Destruct the object `self` manually. If registered with the "
      "Garbage Collector then entry will be removed. If `del_raw` is used then"
      "the destruction will be done without going via the Garbage Collector."
    }, {
      "construct",
      "#define construct(self, ...)\n"
      "var construct_with(var self, var args);",
      "Call the constructor on object `self` which has already been allocated."
    }, {
      "destruct",
      "var destruct(var self);",
      "Call the destructor on object `self` without deallocating the memory "
      "for it."
    }, {NULL, NULL, NULL}
  };
  
  return methods;
}