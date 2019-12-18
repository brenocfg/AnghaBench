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
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  ASM_GENERATE_INTERNAL_LABEL (char* const,char const*,unsigned long) ; 
 int /*<<< orphan*/  ASM_OUTPUT_INTERNAL_LABEL (int /*<<< orphan*/ *,char* const) ; 
 char* alloca (scalar_t__) ; 
 scalar_t__ strlen (char const*) ; 

void
default_internal_label (FILE *stream, const char *prefix,
			unsigned long labelno)
{
  char *const buf = alloca (40 + strlen (prefix));
  ASM_GENERATE_INTERNAL_LABEL (buf, prefix, labelno);
  ASM_OUTPUT_INTERNAL_LABEL (stream, buf);
}