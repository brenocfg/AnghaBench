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

__attribute__((used)) static struct Example* Filter_Examples(void) {
  
  static struct Example examples[] = {
    {
      "Usage",
      "var greater_than_two(var x) {\n"
      "  return c_int(x) > 2 ? x : NULL;\n"
      "}\n"
      "\n"
      "var x = new(Array, Int, $I(0), $I(5), $I(2), $I(9));\n"
      "\n"
      "foreach (n in filter(x, $(Function, greater_than_two))) {\n"
      "  show(n); /* 5, 9 */\n"
      "}\n"
    }, {
      "Usage 2",
      "var mem_hello(var x) {\n"
      "  return mem(x, $S(\"Hello\")) ? x : NULL;\n"
      "}\n"
      "\n"
      "var x = new(Tuple, \n"
      "  $S(\"Hello World\"), $S(\"Hello Dan\"), \n"
      "  $S(\"Bonjour\"));\n"
      "\n"
      "var y = new(Tuple);\n"
      "assign(y, filter(x, $(Function, mem_hello)));\n"
      "show(y); /* tuple(\"Hello World\", \"Hello Dan\") */\n"
    }, {NULL, NULL}
  };

  return examples;
  
}