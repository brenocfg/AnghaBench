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

__attribute__((used)) static struct Example* Map_Examples(void) {
  
  static struct Example examples[] = {
    {
      "Usage",
      "var convert_to_int(var x) {\n"
      "  var y = new(Int);\n"
      "  look_from(y, x, 0);\n"
      "  return y;\n"
      "}\n"
      "\n"
      "var x = tuple($S(\"1\"), $S(\"2\"), $S(\"3\"));\n"
      "\n"
      "foreach (y in map(x, $(Function, convert_to_int))) {\n"
      "  show(y); /* 1, 2, 3 */\n"
      "};\n"
    }, {
      "Usage 2",
      "var print_object(var x) {\n"
      "  println(\"Object %$ is of type %$\", x, type_of(x));\n"
      "  return NULL;\n"
      "}\n"
      "\n"
      "var x = tuple($I(0), $S(\"Hello!\"), $F(2.4));\n"
      "\n"
      "call(map(x, $(Function, print_object)));\n"
    }, {NULL, NULL}
  };

  return examples;
  
}