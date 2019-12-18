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

/* Variables and functions */

__attribute__((used)) static const char* Range_Definition(void) {
  return
    "struct Range {\n"
    "  var value;\n"
    "  int64_t start;\n"
    "  int64_t stop;\n"
    "  int64_t step;\n"
    "};\n";
}