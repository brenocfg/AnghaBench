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
struct frame_info {int dummy; } ;
typedef  scalar_t__ CORE_ADDR ;

/* Variables and functions */
 int /*<<< orphan*/  break_command_1 (char*,int,int,int /*<<< orphan*/ *) ; 
 scalar_t__ default_breakpoint_valid ; 
 struct frame_info* deprecated_selected_frame ; 
 int /*<<< orphan*/  error (char*) ; 
 scalar_t__ find_pc_partial_function (scalar_t__,char**,scalar_t__*,scalar_t__*) ; 
 scalar_t__ get_frame_pc (struct frame_info*) ; 
 int /*<<< orphan*/  paddr_nz (scalar_t__) ; 
 struct frame_info* parse_frame_specification (char*) ; 
 char* strchr (char*,char) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 int strlen (char*) ; 
 int /*<<< orphan*/  strncpy (char*,char*,int) ; 
 int /*<<< orphan*/  xfree (char*) ; 
 scalar_t__ xmalloc (int) ; 
 char* xstrprintf (char*,int /*<<< orphan*/ ,...) ; 

__attribute__((used)) static void
break_at_finish_at_depth_command_1 (char *arg, int flag, int from_tty)
{
  struct frame_info *frame;
  CORE_ADDR low, high, selected_pc = 0;
  char *extra_args = NULL;
  char *level_arg;
  int extra_args_len = 0, if_arg = 0;

  if (!arg ||
      (arg[0] == 'i' && arg[1] == 'f' && (arg[2] == ' ' || arg[2] == '\t')))
    {

      if (default_breakpoint_valid)
	{
	  if (deprecated_selected_frame)
	    {
	      selected_pc = get_frame_pc (deprecated_selected_frame);
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
      extra_args = strchr (arg, ' ');
      if (extra_args)
	{
	  extra_args++;
	  extra_args_len = strlen (extra_args);
	  level_arg = (char *) xmalloc (extra_args - arg);
	  strncpy (level_arg, arg, extra_args - arg - 1);
	  level_arg[extra_args - arg - 1] = '\0';
	}
      else
	{
	  level_arg = (char *) xmalloc (strlen (arg) + 1);
	  strcpy (level_arg, arg);
	}

      frame = parse_frame_specification (level_arg);
      if (frame)
	selected_pc = get_frame_pc (frame);
      else
	selected_pc = 0;
    }
  if (if_arg)
    {
      extra_args = arg;
      extra_args_len = strlen (arg);
    }

  if (selected_pc)
    {
      if (find_pc_partial_function (selected_pc, (char **) NULL, &low, &high))
	{
	  char *addr_string;
	  if (extra_args_len)
	    addr_string = xstrprintf ("*0x%s %s", paddr_nz (high), extra_args);
	  else
	    addr_string = xstrprintf ("*0x%s", paddr_nz (high));
	  break_command_1 (addr_string, flag, from_tty, NULL);
	  xfree (addr_string);
	}
      else
	error ("No function contains the specified address");
    }
  else
    error ("Unable to set breakpoint at procedure exit");
}