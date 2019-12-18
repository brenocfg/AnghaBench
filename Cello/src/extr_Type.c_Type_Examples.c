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

__attribute__((used)) static struct Example* Type_Examples(void) {
  
  static struct Example examples[] = {
    {
      "Usage",
      "var t = type_of($I(5));\n"
      "show(t); /* Int */\n"
      "\n"
      "show($I(type_implements(t, New)));  /* 1 */\n"
      "show($I(type_implements(t, Cmp)));  /* 1 */\n"
      "show($I(type_implements(t, Hash))); /* 1 */\n"
      "\n"
      "show($I(type_method(t, Cmp, cmp, $I(5), $I(6))));\n"
    }, {NULL, NULL}
  };

  return examples;
  
}