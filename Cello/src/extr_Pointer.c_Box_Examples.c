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
struct Example {char* member_0; char* member_1; } ;

/* Variables and functions */

__attribute__((used)) static struct Example* Box_Examples(void) {
  
  static struct Example examples[] = {
    {
      "Usage",
      "var obj0 = $F(1.0), obj1 = $F(2.0);\n"
      "var r = $(Box, obj0);\n"
      "show(r);\n"
      "show(deref(r)); /* 1.0 */\n"
      "ref(r, obj1);\n"
      "show(deref(r)); /* 2.0 */\n"
      "assign(r, obj0);\n"
      "show(deref(r)); /* 1.0 */\n"
    }, {
      "Lifetimes",
      "var quote = $S(\"Life is long\");\n"
      "\n"
      "with (r in $B(new(String, quote))) {\n"
      "  println(\"This reference is: %$\", r);\n"
      "  println(\"This string is alive: '%s'\", deref(r));\n"
      "}\n"
      "\n"
      "print(\"Now it has been cleared up!\\n\");\n"
    }, {
      "Collection",
      "/* Multiple Types in one Collection */\n"
      "var x = new(Array, Box, \n"
      "  new(String, $S(\"Hello\")), \n"
      "  new(String, $S(\"There\")), \n"
      "  new(Int, $I(10)));\n"
      "\n"
      "print(deref(get(x, $I(0)))); /* Hello */ \n"
      "\n"
      "del(x); /* Contents of `x` deleted with it */\n"
    }, {NULL, NULL}
  };

  return examples;
  
}