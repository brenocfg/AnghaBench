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
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  bfd_error_system_call ; 
 int /*<<< orphan*/  bfd_set_error (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  einfo (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/ * ldfile_find_command_file (char const*,char*) ; 
 char const* ldfile_input_filename ; 
 int /*<<< orphan*/  lex_push_file (int /*<<< orphan*/ *,char const*) ; 
 int lineno ; 
 int /*<<< orphan*/ * saved_script_handle ; 

void
ldfile_open_command_file (const char *name)
{
  FILE *ldlex_input_stack;
  ldlex_input_stack = ldfile_find_command_file (name, "");

  if (ldlex_input_stack == NULL)
    {
      bfd_set_error (bfd_error_system_call);
      einfo (_("%P%F: cannot open linker script file %s: %E\n"), name);
    }

  lex_push_file (ldlex_input_stack, name);

  ldfile_input_filename = name;
  lineno = 1;

  saved_script_handle = ldlex_input_stack;
}