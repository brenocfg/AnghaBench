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

__attribute__((used)) static struct Example* Slice_Examples(void) {
  
  static struct Example examples[] = {
    {
      "Usage",
      "var x = tuple(\n"
      "  $S(\"Hello\"), $S(\"There\"), $S(\"World\"), $S(\"!\"));\n"
      "\n"
      "/* Iterate over elements 0 to 2 */\n"
      "foreach (s in slice(x, $I(2))) {\n"
      "  print(\"%s\\n\", s);\n"
      "}\n"
      "\n"
      "/* Iterate over elements 1 to 2 */\n"
      "foreach (s in slice(x, $I(1), $I(2))) {\n"
      "  print(\"%s\\n\", s);\n"
      "}\n"
      "\n"
      "/* Iterate over every other element */\n"
      "foreach (s in slice(x, _, _, $I(2))) {\n"
      "  print(\"%s\\n\", s);\n"
      "}\n"
      "\n"
      "/* Iterate backwards, starting from element 3 */\n"
      "foreach (s in slice(x, _, $I(2), $I(-1))) {\n"
      "  print(\"%s\\n\", s);\n"
      "}\n"
    }, {NULL, NULL}
  };

  return examples;
  
}