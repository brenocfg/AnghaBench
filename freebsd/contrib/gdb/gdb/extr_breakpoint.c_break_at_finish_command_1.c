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
struct symtabs_and_lines {int nelts; struct symtab_and_line* sals; } ;
struct symtab_and_line {int /*<<< orphan*/  pc; } ;
struct symtab {int dummy; } ;
struct cleanup {int dummy; } ;
typedef  int /*<<< orphan*/  CORE_ADDR ;

/* Variables and functions */
 int /*<<< orphan*/  break_command_1 (char*,int,int,int /*<<< orphan*/ *) ; 
 struct symtabs_and_lines decode_line_1 (char**,int,struct symtab*,int /*<<< orphan*/ ,char***,int /*<<< orphan*/ *) ; 
 scalar_t__ default_breakpoint_valid ; 
 scalar_t__ deprecated_selected_frame ; 
 int /*<<< orphan*/  do_cleanups (struct cleanup*) ; 
 int /*<<< orphan*/  error (char*) ; 
 scalar_t__ find_pc_partial_function (int /*<<< orphan*/ ,char**,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  get_frame_pc (scalar_t__) ; 
 struct cleanup* make_cleanup (int /*<<< orphan*/  (*) (char*),struct symtab_and_line*) ; 
 int /*<<< orphan*/  paddr_nz (int /*<<< orphan*/ ) ; 
 char* strchr (char*,char) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 int strlen (char*) ; 
 int /*<<< orphan*/  warning (char*) ; 
 int /*<<< orphan*/  xfree (char*) ; 
 scalar_t__ xmalloc (int) ; 
 char* xstrprintf (char*,int /*<<< orphan*/ ,...) ; 

__attribute__((used)) static void
break_at_finish_command_1 (char *arg, int flag, int from_tty)
{
  char *addr_string, *break_string, *beg_addr_string;
  CORE_ADDR low, high;
  struct symtabs_and_lines sals;
  struct symtab_and_line sal;
  struct cleanup *old_chain;
  char *extra_args = NULL;
  int extra_args_len = 0;
  int i, if_arg = 0;

  if (!arg ||
      (arg[0] == 'i' && arg[1] == 'f' && (arg[2] == ' ' || arg[2] == '\t')))
    {
      if (default_breakpoint_valid)
	{
	  if (deprecated_selected_frame)
	    {
	      addr_string = xstrprintf ("*0x%s",
					paddr_nz (get_frame_pc (deprecated_selected_frame)));
	      if (arg)
		if_arg = 1;
	    }
	  else
	    error ("No selected frame.");
	}
      else
	error ("No default breakpoint address now.");
    }
  else
    {
      addr_string = (char *) xmalloc (strlen (arg) + 1);
      strcpy (addr_string, arg);
    }

  if (if_arg)
    {
      extra_args = arg;
      extra_args_len = strlen (arg);
    }
  else if (arg)
    {
      /* get the stuff after the function name or address */
      extra_args = strchr (arg, ' ');
      if (extra_args)
	{
	  extra_args++;
	  extra_args_len = strlen (extra_args);
	}
    }

  sals.sals = NULL;
  sals.nelts = 0;

  beg_addr_string = addr_string;
  sals = decode_line_1 (&addr_string, 1, (struct symtab *) NULL, 0,
			(char ***) NULL, NULL);

  xfree (beg_addr_string);
  old_chain = make_cleanup (xfree, sals.sals);
  for (i = 0; (i < sals.nelts); i++)
    {
      sal = sals.sals[i];
      if (find_pc_partial_function (sal.pc, (char **) NULL, &low, &high))
	{
	  break_string;
	  if (extra_args_len)
	    break_string = xstrprintf ("*0x%s %s", paddr_nz (high),
				       extra_args);
	  else
	    break_string = xstrprintf ("*0x%s", paddr_nz (high));
	  break_command_1 (break_string, flag, from_tty, NULL);
	  xfree (break_string);
	}
      else
	error ("No function contains the specified address");
    }
  if (sals.nelts > 1)
    {
      warning ("Multiple breakpoints were set.\n");
      warning ("Use the \"delete\" command to delete unwanted breakpoints.");
    }
  do_cleanups (old_chain);
}