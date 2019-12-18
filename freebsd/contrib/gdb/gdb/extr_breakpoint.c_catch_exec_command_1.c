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
 int /*<<< orphan*/  create_exec_event_catchpoint (int,char*) ; 
 char* ep_parse_optional_if_clause (char**) ; 
 int /*<<< orphan*/  ep_skip_leading_whitespace (char**) ; 
 int /*<<< orphan*/  error (char*) ; 
 int /*<<< orphan*/  isspace (char) ; 

__attribute__((used)) static void
catch_exec_command_1 (char *arg, int tempflag, int from_tty)
{
  char *cond_string = NULL;

  ep_skip_leading_whitespace (&arg);

  /* The allowed syntax is:
     catch exec
     catch exec if <cond>

     First, check if there's an if clause. */
  cond_string = ep_parse_optional_if_clause (&arg);

  if ((*arg != '\0') && !isspace (*arg))
    error ("Junk at end of arguments.");

  /* If this target supports it, create an exec catchpoint
     and enable reporting of such events. */
  create_exec_event_catchpoint (tempflag, cond_string);
}