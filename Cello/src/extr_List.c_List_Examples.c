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

__attribute__((used)) static struct Example* List_Examples(void) {
  
  static struct Example examples[] = {
    {
      "Construction & Deletion",
      "var x = new(List, Int);\n"
      "push(x, $I(32));\n"
      "push(x, $I(6));\n"
      "\n"
      "/* <'List' At 0x0000000000414603 [32, 6]> */\n"
      "show(x);\n",
    }, {
      "Element Access",
      "var x = new(List, Float, $F(0.01), $F(5.12));\n"
      "\n"
      "show(get(x, $I(0))); /* 0.01 */\n"
      "show(get(x, $I(1))); /* 5.12 */\n"
      "\n"
      "set(x, $I(0), $F(500.1));\n"
      "show(get(x, $I(0))); /* 500.1 */\n",
    }, {
      "Membership",
      "var x = new(List, Int, $I(1), $I(2), $I(3), $I(4));\n"
      "\n"
      "show($I(mem(x, $I(1)))); /* 1 */\n"
      "show($I(len(x)));        /* 4 */\n"
      "\n"
      "rem(x, $I(3));\n"
      "\n"
      "show($I(mem(x, $I(3)))); /* 0 */\n"
      "show($I(len(x)));        /* 3 */\n"
      "show($I(empty(x)));      /* 0 */\n"
      "\n"
      "resize(x, 0);\n"
      "\n"
      "show($I(empty(x)));      /* 1 */\n",
    }, {
      "Iteration",
      "var greetings = new(List, String, \n"
      "  $S(\"Hello\"), $S(\"Bonjour\"), $S(\"Hej\"));\n"
      "\n"
      "foreach(greet in greetings) {\n"
      "  show(greet);\n"
      "}\n",
    }, {NULL, NULL}
  };
  
  return examples;
}