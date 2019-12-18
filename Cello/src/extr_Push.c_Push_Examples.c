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

__attribute__((used)) static struct Example* Push_Examples(void) {
  
  static struct Example examples[] = {
    {
      "Usage",
      "var x = new(Array, Int);\n"
      "\n"
      "push(x, $I( 0));\n"
      "push(x, $I( 5));\n"
      "push(x, $I(10));\n"
      "\n"
      "show(get(x, $I(0))); /*  0 */\n"
      "show(get(x, $I(1))); /*  5 */\n"
      "show(get(x, $I(2))); /* 10 */\n"
      "\n"
      "pop_at(x, $I(1));\n"
      "\n"
      "show(get(x, $I(0))); /*  0 */\n"
      "show(get(x, $I(1))); /* 10 */\n"
    }, {NULL, NULL}
  };

  return examples;
  
}