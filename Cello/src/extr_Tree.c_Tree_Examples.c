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

__attribute__((used)) static struct Example* Tree_Examples(void) {
  
  static struct Example examples[] = {
    {
      "Usage",
      "var prices = new(Tree, String, Int);\n"
      "set(prices, $S(\"Apple\"),  $I(12));\n"
      "set(prices, $S(\"Banana\"), $I( 6));\n"
      "set(prices, $S(\"Pear\"),   $I(55));\n"
      "\n"
      "foreach (key in prices) {\n"
      "  var price = get(prices, key);\n"
      "  println(\"Price of %$ is %$\", key, price);\n"
      "}\n"
    }, {
      "Manipulation",
      "var t = new(Tree, String, Int);\n"
      "set(t, $S(\"Hello\"), $I(2));\n"
      "set(t, $S(\"There\"), $I(5));\n"
      "\n"
      "show($I(len(t))); /* 2 */\n"
      "show($I(mem(t, $S(\"Hello\")))); /* 1 */\n"
      "\n"
      "rem(t, $S(\"Hello\"));\n"
      "\n"
      "show($I(len(t))); /* 1 */\n"
      "show($I(mem(t, $S(\"Hello\")))); /* 0 */\n"
      "show($I(mem(t, $S(\"There\")))); /* 1 */\n"
      "\n"
      "resize(t, 0);\n"
      "\n"
      "show($I(len(t))); /* 0 */\n"
      "show($I(mem(t, $S(\"Hello\")))); /* 0 */\n"
      "show($I(mem(t, $S(\"There\")))); /* 0 */\n"
    }, {NULL, NULL}
  };

  return examples;
  
}