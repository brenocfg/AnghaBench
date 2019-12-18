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

__attribute__((used)) static struct Example* Alloc_Examples(void) {
  
  static struct Example examples[] = {
    {
     "Usage",
     "/* Allocation deallocated by Garbage Collector */\n"
     "var x = alloc(Int);\n"
     "construct(x, $I(10));\n",
    }, {
     "Avoid Garbage Collection",
     "/* Allocation must be manually deallocated */\n"
     "var x = alloc_raw(Int);\n"
     "construct(x, $I(10));\n"
     "destruct(x);\n"
     "dealloc_raw(x);\n",
    }, {NULL, NULL}
  };
  
  return examples;
}