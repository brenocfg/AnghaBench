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

__attribute__((used)) static struct Example* Function_Examples(void) {
  
  static struct Example examples[] = {
    {
      "Usage",
      "var increment(var args) {\n"
      "  struct Int* i = get(args, $I(0));\n"
      "  i->val++;\n"
      "  return NULL;\n"
      "}\n"
      "\n"
      "var x = $I(0);\n"
      "show(x); /* 0 */\n"
      "call($(Function, increment), x);\n"
      "show(x); /* 1 */\n"
    }, {
      "Usage 2",
      "var hello_person(var args) {\n"
      "  print(\"Hello %$!\", get(args, $I(0)));\n"
      "  return NULL;\n"
      "}\n"
      "\n"
      "call($(Function, hello_person), $S(\"Dan\"));\n"
    }, {
      "Usage 3",
      "var add_print(var args) {\n"
      "  int64_t fst = c_int(get(args, $I(0)));\n"
      "  int64_t snd = c_int(get(args, $I(1)));\n"
      "  println(\"%i + %i = %i\", $I(fst), $I(snd), $I(fst+snd));\n"
      "  return NULL;\n"
      "}\n"
      "\n"
      "call($(Function, add_print), $I(10), $I(21));\n"
    }, {NULL, NULL}
  };

  return examples;
  
}