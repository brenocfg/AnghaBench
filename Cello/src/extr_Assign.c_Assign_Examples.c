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

__attribute__((used)) static struct Example* Assign_Examples(void) {
  
  static struct Example examples[] = {
    {
      "Usage",
      "var x = new(Int, $I(10));\n"
      "var y = new(Int, $I(20));\n"
      "\n"
      "show(x); /* 10 */\n"
      "show(y); /* 20 */\n"
      "\n"
      "assign(x, y);\n"
      "\n"
      "show(x); /* 20 */\n"
      "show(y); /* 20 */\n"
    }, {NULL, NULL}
  };
  
  return examples;
}