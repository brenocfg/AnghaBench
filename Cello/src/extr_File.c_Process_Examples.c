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

__attribute__((used)) static struct Example* Process_Examples(void) {
  
  static struct Example examples[] = {
    {
      "Usage",
      "var x = new(Process, $S(\"ls\"), $S(\"r\"));\n"
      "char c;\n"
      "while (not seof(x)) {\n"
      "  sread(x, &c, 1);\n"
      "  print(\"%c\", $I(c));\n"
      "}\n"
      "sclose(x);\n"
    }, {NULL, NULL}
  };

  return examples;
  
}