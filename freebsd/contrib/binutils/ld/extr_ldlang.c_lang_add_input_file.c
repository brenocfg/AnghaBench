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
typedef  int /*<<< orphan*/  lang_input_statement_type ;
typedef  int /*<<< orphan*/  lang_input_file_enum_type ;

/* Variables and functions */
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/ * new_afile (char const*,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 

lang_input_statement_type *
lang_add_input_file (const char *name,
		     lang_input_file_enum_type file_type,
		     const char *target)
{
  return new_afile (name, file_type, target, TRUE);
}