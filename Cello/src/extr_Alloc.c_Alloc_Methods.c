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

__attribute__((used)) static struct Method* Alloc_Methods(void) {
  
  static struct Method methods[] = {
    {
      "$",
      "#define $(T, ...)\n"
      "#define $I(X)\n"
      "#define $F(X)\n"
      "#define $S(X)\n"
      "#define $R(X)\n"
      "#define $B(X)",
      "Allocate memory for the given type `T` on the stack and copy in the "
      "given arguments `...` as struct members. Shorthand constructors exist "
      "for native types:\n\n* `$I -> Int` `$F -> Float` `$S -> String`\n*"
      " `$R -> Ref` `$B -> Box`\n\n"
    }, {
      "alloc", 
      "#define alloc_stack(T)\n"
      "var alloc(var type);\n"
      "var alloc_raw(var type);\n"
      "var alloc_root(var type);",
      "Allocate memory for a given `type`. To avoid the Garbage Collector "
      "completely use `alloc_raw`, to register the allocation as a root use "
      "`alloc_root`. In the case of raw or root allocations the corresponding "
      "`dealloc` function should be used when done. Memory allocated with "
      "`alloc_stack` is not managed by the Garbage Collector."
    }, {
      "dealloc",
      "void dealloc(var self);\n"
      "void dealloc_raw(var self);\n"
      "void dealloc_root(var self);",
      "Deallocate memory for object `self` manually. If registered with the "
      "Garbage Collector then entry will be removed. If the `raw` variation is "
      "used memory will be deallocated without going via the Garbage Collector." 
    }, {NULL, NULL, NULL}
  };
  
  return methods;
}