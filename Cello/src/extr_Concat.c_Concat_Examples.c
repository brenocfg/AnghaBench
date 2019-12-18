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

__attribute__((used)) static struct Example* Concat_Examples(void) {
  
  static struct Example examples[] = {
    {
      "Usage",
      "var x = new(Array, Float, $F(9.9), $F(2.8));\n"
      "var y = new(Array, Float, $F(1.1), $F(6.5));\n"
      "\n"
      "show(x); /* <'Array' At 0x00414603 [9.9, 2.8]> */\n"
      "show(y); /* <'Array' At 0x00414603 [1.1, 6.5]> */\n"
      "append(x, $F(2.5));\n"
      "show(x); /* <'Array' At 0x00414603 [9.9, 2.8, 2.5]> */\n"
      "concat(x, y);\n"
      "show(x); /* <'Array' At 0x00414603 [9.9, 2.8, 2.5, 1.1, 6.5]> */\n"
    }, {NULL, NULL}
  };

  return examples;
  
}