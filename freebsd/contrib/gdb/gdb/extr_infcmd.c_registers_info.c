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
struct reggroup {int dummy; } ;

/* Variables and functions */
 int NUM_PSEUDO_REGS ; 
 int NUM_REGS ; 
 int /*<<< orphan*/  current_gdbarch ; 
 int /*<<< orphan*/ * deprecated_selected_frame ; 
 int /*<<< orphan*/  error (char*,...) ; 
 int frame_map_name_to_regnum (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  gdb_stdout ; 
 int /*<<< orphan*/  gdbarch_print_registers_info (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int) ; 
 scalar_t__ gdbarch_register_reggroup_p (int /*<<< orphan*/ ,int,struct reggroup*) ; 
 scalar_t__ isspace (char) ; 
 int /*<<< orphan*/  reggroup_name (struct reggroup*) ; 
 struct reggroup* reggroup_next (int /*<<< orphan*/ ,struct reggroup*) ; 
 scalar_t__ strncmp (char*,int /*<<< orphan*/ ,int) ; 
 int strtol (char*,char**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  target_has_registers ; 

void
registers_info (char *addr_exp, int fpregs)
{
  int regnum, numregs;
  char *end;

  if (!target_has_registers)
    error ("The program has no registers now.");
  if (deprecated_selected_frame == NULL)
    error ("No selected frame.");

  if (!addr_exp)
    {
      gdbarch_print_registers_info (current_gdbarch, gdb_stdout,
				    deprecated_selected_frame, -1, fpregs);
      return;
    }

  while (*addr_exp != '\0')
    {
      char *start;
      const char *end;

      /* Keep skipping leading white space.  */
      if (isspace ((*addr_exp)))
	{
	  addr_exp++;
	  continue;
	}

      /* Discard any leading ``$''.  Check that there is something
         resembling a register following it.  */
      if (addr_exp[0] == '$')
	addr_exp++;
      if (isspace ((*addr_exp)) || (*addr_exp) == '\0')
	error ("Missing register name");

      /* Find the start/end of this register name/num/group.  */
      start = addr_exp;
      while ((*addr_exp) != '\0' && !isspace ((*addr_exp)))
	addr_exp++;
      end = addr_exp;
      
      /* Figure out what we've found and display it.  */

      /* A register name?  */
      {
	int regnum = frame_map_name_to_regnum (deprecated_selected_frame,
					       start, end - start);
	if (regnum >= 0)
	  {
	    gdbarch_print_registers_info (current_gdbarch, gdb_stdout,
					  deprecated_selected_frame, regnum, fpregs);
	    continue;
	  }
      }
	
      /* A register number?  (how portable is this one?).  */
      {
	char *endptr;
	int regnum = strtol (start, &endptr, 0);
	if (endptr == end
	    && regnum >= 0
	    && regnum < NUM_REGS + NUM_PSEUDO_REGS)
	  {
	    gdbarch_print_registers_info (current_gdbarch, gdb_stdout,
					  deprecated_selected_frame, regnum, fpregs);
	    continue;
	  }
      }

      /* A register group?  */
      {
	struct reggroup *group;
	for (group = reggroup_next (current_gdbarch, NULL);
	     group != NULL;
	     group = reggroup_next (current_gdbarch, group))
	  {
	    /* Don't bother with a length check.  Should the user
	       enter a short register group name, go with the first
	       group that matches.  */
	    if (strncmp (start, reggroup_name (group), end - start) == 0)
	      break;
	  }
	if (group != NULL)
	  {
	    int regnum;
	    for (regnum = 0; regnum < NUM_REGS + NUM_PSEUDO_REGS; regnum++)
	      {
		if (gdbarch_register_reggroup_p (current_gdbarch, regnum,
						 group))
		  gdbarch_print_registers_info (current_gdbarch,
						gdb_stdout, deprecated_selected_frame,
						regnum, fpregs);
	      }
	    continue;
	  }
      }

      /* Nothing matched.  */
      error ("Invalid register `%.*s'", (int) (end - start), start);
    }
}