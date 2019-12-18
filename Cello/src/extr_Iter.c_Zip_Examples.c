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

__attribute__((used)) static struct Example* Zip_Examples(void) {
  
  static struct Example examples[] = {
    {
      "Usage",
      "/* Iterate over two iterables at once */\n"
      "var x = new(Array, Int, $I(100), $I(200), $I(130));\n"
      "var y = new(Array, Float, $F(0.1), $F(0.2), $F(1.3));\n"
      "foreach (pair in zip(x, y)) {\n"
      "  print(\"x: %$\\n\", get(pair, $I(0)));\n"
      "  print(\"y: %$\\n\", get(pair, $I(1)));\n"
      "}\n"
      "\n"
      "/* Iterate over iterable with count */\n"
      "foreach (pair in enumerate(x)) {\n"
      "  print(\"%i: %$\\n\", get(pair, $I(0)), get(pair, $I(1)));\n"
      "}\n"
    }, {NULL, NULL}
  };

  return examples;
  
}