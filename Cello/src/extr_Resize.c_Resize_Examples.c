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

__attribute__((used)) static struct Example* Resize_Examples(void) {
  
  static struct Example examples[] = {
    {
      "Usage",
      "var x = new(Array, Int);\n"
      "resize(x, 10000); /* Reserve space in Array */ \n"
      "for (size_t i = 0; i < 10000; i++) {\n"
      "  push(x, $I(i));\n"
      "}\n"
    }, {
      "Usage 2",
      "var x = new(Array, Int, $I(0), $I(1), $I(2));\n"
      "resize(x, 0); /* Clear Array of items */\n"
    }, {NULL, NULL}
  };

  return examples;
  
}