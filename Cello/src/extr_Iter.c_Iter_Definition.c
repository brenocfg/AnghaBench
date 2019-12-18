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

__attribute__((used)) static const char* Iter_Definition(void) {
  return
    "struct Iter {\n"
    "  var (*iter_init)(var);\n"
    "  var (*iter_next)(var, var);\n"
    "  var (*iter_prev)(var, var);\n"
    "  var (*iter_last)(var);\n"
    "  var (*iter_type)(var);\n"
    "};\n";
}