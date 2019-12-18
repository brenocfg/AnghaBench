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
typedef  int /*<<< orphan*/  lang_output_section_statement_type ;

/* Variables and functions */
 int /*<<< orphan*/ * lang_output_section_statement_lookup_1 (char const* const,int /*<<< orphan*/ ) ; 

lang_output_section_statement_type *
lang_output_section_statement_lookup (const char *const name)
{
  return lang_output_section_statement_lookup_1 (name, 0);
}