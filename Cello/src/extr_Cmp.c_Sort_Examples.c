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

__attribute__((used)) static struct Example* Sort_Examples(void) {
  
  static struct Example examples[] = {
    {
      "Usage",
      "var x = new(Array, Float, \n"
      "  $F(5.2), $F(7.1), $F(2.2));\n"
      "\n"
      "show(x); /* <'Array' At 0x00414603 [5.2, 7.1, 2.2]> */\n"
      "sort(x);\n"
      "show(x); /* <'Array' At 0x00414603 [2.2, 5.2, 7.1]> */\n"
    }, {NULL, NULL}
  };
  
  return examples;
}