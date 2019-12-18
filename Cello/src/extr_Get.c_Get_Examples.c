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

__attribute__((used)) static struct Example* Get_Examples(void) {
  
  static struct Example examples[] = {
    {
      "Usage 1",
      "var x = new(Array, String, \n"
      "  $S(\"Hello\"), $S(\"There\"));\n"
      "\n"
      "show(get(x, $I(0))); /* Hello */\n"
      "show(get(x, $I(1))); /* There */\n"
      "set(x, $I(1), $S(\"Blah\"));\n"
      "show(get(x, $I(1))); /* Blah */\n"
    }, {
      "Usage 2",
      "var prices = new(Table, String, Int, \n"
      "  $S(\"Apple\"),  $I(12),\n"
      "  $S(\"Banana\"), $I( 6),\n"
      "  $S(\"Pear\"),   $I(55));\n"
      "\n"
      "var pear_price   = get(prices, $S(\"Pear\"));\n"
      "var banana_price = get(prices, $S(\"Banana\"));\n"
      "var apple_price  = get(prices, $S(\"Apple\"));\n"
      "\n"
      "show(pear_price);   /* 55 */\n"
      "show(banana_price); /*  6 */\n"
      "show(apple_price);  /* 12 */\n"
    }, {NULL, NULL}
  };

  return examples;
  
}