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

__attribute__((used)) static struct Example* Int_Examples(void) {
  
  static struct Example examples[] = {
    {
      "Usage",
      "var i0 = $(Int, 1);\n"
      "var i1 = new(Int, $I(24313));\n"
      "var i2 = copy(i0);\n"
      "\n"
      "show(i0); /*     1 */\n"
      "show(i1); /* 24313 */\n"
      "show(i2); /*     1 */\n"
    }, {NULL, NULL}
  };

  return examples;
  
}