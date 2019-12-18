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

__attribute__((used)) static struct Example* Float_Examples(void) {
  
  static struct Example examples[] = {
    {
      "Usage",
      "var f0 = $(Float, 1.0);\n"
      "var f1 = new(Float, $F(24.313));\n"
      "var f2 = copy(f0);\n"
      "\n"
      "show(f0); /*  1.000 */\n"
      "show(f1); /* 24.313 */\n"
      "show(f2); /*  1.000 */\n"
    }, {NULL, NULL}
  };

  return examples;
  
}