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
 int /*<<< orphan*/  PIDGET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SOLIB_CREATE_CATCH_LOAD_HOOK (int /*<<< orphan*/ ,int,char*,char*) ; 
 char* ep_parse_optional_filename (char**) ; 
 char* ep_parse_optional_if_clause (char**) ; 
 int /*<<< orphan*/  ep_skip_leading_whitespace (char**) ; 
 int /*<<< orphan*/  error (char*) ; 
 int /*<<< orphan*/  inferior_ptid ; 
 int /*<<< orphan*/  isspace (char) ; 

__attribute__((used)) static void
catch_load_command_1 (char *arg, int tempflag, int from_tty)
{
  char *dll_pathname = NULL;
  char *cond_string = NULL;

  ep_skip_leading_whitespace (&arg);

  /* The allowed syntax is:
     catch load
     catch load if <cond>
     catch load <filename>
     catch load <filename> if <cond>

     The user is not allowed to specify the <filename> after an
     if clause.

     We'll ignore the pathological case of a file named "if".

     First, check if there's an if clause.  If so, then there
     cannot be a filename. */
  cond_string = ep_parse_optional_if_clause (&arg);

  /* If there was an if clause, then there cannot be a filename.
     Else, there might be a filename and an if clause. */
  if (cond_string == NULL)
    {
      dll_pathname = ep_parse_optional_filename (&arg);
      ep_skip_leading_whitespace (&arg);
      cond_string = ep_parse_optional_if_clause (&arg);
    }

  if ((*arg != '\0') && !isspace (*arg))
    error ("Junk at end of arguments.");

  /* Create a load breakpoint that only triggers when a load of
     the specified dll (or any dll, if no pathname was specified)
     occurs. */
  SOLIB_CREATE_CATCH_LOAD_HOOK (PIDGET (inferior_ptid), tempflag, 
				dll_pathname, cond_string);
}