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

__attribute__((used)) static struct Example* Range_Examples(void) {
  
  static struct Example examples[] = {
    {
      "Usage",
      "/* Iterate 0 to 10 */\n"
      "foreach (i in range($I(10))) {\n"
      "  print(\"%i\\n\", i);\n"
      "}\n"
      "\n"
      "/* Iterate 10 to 20 */\n"
      "foreach (i in range($I(10), $I(20))) {\n"
      "  print(\"%i\\n\", i);\n"
      "}\n"
      "\n"
      "/* Iterate 10 to 20 with a step of 5 */\n"
      "foreach (i in range($I(10), $I(20), $I(5))) {\n"
      "  print(\"%i\\n\", i);\n"
      "}\n"
      "\n"
      "/* Iterate 20 to 10 */\n"
      "foreach (i in range($I(10), $I(20), $I(-1))) {\n"
      "  print(\"%i\\n\", i);\n"
      "}\n"
    }, {NULL, NULL}
  };

  return examples;
  
}