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
typedef  enum glslang_format { ____Placeholder_glslang_format } glslang_format ;

/* Variables and functions */
 char const** glslang_formats ; 

const char *glslang_format_to_string(enum glslang_format fmt)
{
   return glslang_formats[fmt];
}