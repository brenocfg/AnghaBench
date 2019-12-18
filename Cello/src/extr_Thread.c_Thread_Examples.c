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

__attribute__((used)) static struct Example* Thread_Examples(void) {
  
  static struct Example examples[] = {
    {
      "Usage",
      "var set_value(var args) {\n"
      "  assign(get(args, $I(0)), $I(1));\n"
      "  return NULL;\n"
      "}\n"
      "\n"
      "var i = $I(0);\n"
      "\n"
      "var x = new(Thread, $(Function, set_value));\n"
      "call(x, i);\n"
      "join(x);\n"
      "\n"
      "show(i); /* 1 */\n"
    }, {
      "Exclusive Resource",
      "var increment(var args) {\n"
      "  var mut = get(args, $I(0));\n"
      "  var tot = get(args, $I(1));\n"
      "  lock(mut);\n"
      "  assign(tot, $I(c_int(tot)+1));\n"
      "  unlock(mut);\n"
      "  return NULL;\n"
      "}\n"
      "\n"
      "var mutex = new(Mutex);\n"
      "var total = $I(0);\n"
      "\n"
      "var threads = new(Array, Box,\n"
      "  new(Thread, $(Function, increment)),\n"
      "  new(Thread, $(Function, increment)),\n"
      "  new(Thread, $(Function, increment)));\n"
      "\n"
      "show(total); /* 0 */\n"
      "\n"
      "foreach (t in threads) {\n"
      "  call(deref(t), mutex, total);\n"
      "}\n"
      "\n"
      "foreach (t in threads) {\n"
      "  join(deref(t));\n"
      "}\n"
      "\n"
      "show(total); /* 3 */\n"
    }, {NULL, NULL}
  };
  
  return examples;
}