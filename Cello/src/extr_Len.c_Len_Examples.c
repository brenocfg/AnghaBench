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

__attribute__((used)) static struct Example* Len_Examples(void) {
  
  static struct Example examples[] = {
    {
      "Usage",
      "var x = new(Array, Int, $I(1), $I(2), $I(5));\n"
      "show($I(len(x))); /* 3 */\n"
      "var y = $S(\"Test\");\n"
      "show($I(len(y))); /* 4 */\n"
    }, {NULL, NULL}
  };

  return examples;
  
}