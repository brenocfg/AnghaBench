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
struct symtab_and_line {int dummy; } ;
typedef  enum exception_event_kind { ____Placeholder_exception_event_kind } exception_event_kind ;

/* Variables and functions */
 int EX_EVENT_CATCH ; 
 int EX_EVENT_THROW ; 
 int /*<<< orphan*/  create_exception_catchpoint (int,char*,int,struct symtab_and_line*) ; 
 char* ep_parse_optional_if_clause (char**) ; 
 int /*<<< orphan*/  ep_skip_leading_whitespace (char**) ; 
 int /*<<< orphan*/  error (char*) ; 
 scalar_t__ handle_gnu_v3_exceptions (int,char*,int,int) ; 
 int /*<<< orphan*/  isspace (char) ; 
 struct symtab_and_line* target_enable_exception_callback (int,int) ; 
 int /*<<< orphan*/  warning (char*) ; 

__attribute__((used)) static void
catch_exception_command_1 (enum exception_event_kind ex_event, char *arg,
			   int tempflag, int from_tty)
{
  char *cond_string = NULL;
  struct symtab_and_line *sal = NULL;

  ep_skip_leading_whitespace (&arg);

  cond_string = ep_parse_optional_if_clause (&arg);

  if ((*arg != '\0') && !isspace (*arg))
    error ("Junk at end of arguments.");

  if ((ex_event != EX_EVENT_THROW) &&
      (ex_event != EX_EVENT_CATCH))
    error ("Unsupported or unknown exception event; cannot catch it");

  if (handle_gnu_v3_exceptions (tempflag, cond_string, ex_event, from_tty))
    return;

  /* See if we can find a callback routine */
  sal = target_enable_exception_callback (ex_event, 1);

  if (sal)
    {
      /* We have callbacks from the runtime system for exceptions.
         Set a breakpoint on the sal found, if no errors */
      if (sal != (struct symtab_and_line *) -1)
	create_exception_catchpoint (tempflag, cond_string, ex_event, sal);
      else
	return;		/* something went wrong with setting up callbacks */
    }

  warning ("Unsupported with this platform/compiler combination.");
}