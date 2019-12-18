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

__attribute__((used)) static const char* Format_Definition(void) {
  return 
    "struct Format {\n"
    "  int (*format_to)(var,int,const char*,va_list);\n"
    "  int (*format_from)(var,int,const char*,va_list);\n"
    "};\n";
}