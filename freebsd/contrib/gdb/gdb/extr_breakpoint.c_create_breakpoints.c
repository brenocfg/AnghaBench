#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct symtabs_and_lines {int nelts; struct symtab_and_line* sals; } ;
struct symtab_and_line {int /*<<< orphan*/  section; int /*<<< orphan*/  pc; } ;
struct expression {int dummy; } ;
struct breakpoint {int thread; char* addr_string; char* cond_string; int ignore_count; int disposition; scalar_t__ commands; TYPE_1__* loc; struct expression* cond; int /*<<< orphan*/  enable_state; scalar_t__ number; } ;
typedef  enum bptype { ____Placeholder_bptype } bptype ;
typedef  enum bpdisp { ____Placeholder_bpdisp } bpdisp ;
struct TYPE_2__ {int /*<<< orphan*/  address; } ;

/* Variables and functions */
 int TARGET_CAN_USE_HARDWARE_WATCHPOINT (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  block_for_pc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bp_enabled ; 
 int bp_hardware_breakpoint ; 
 scalar_t__ breakpoint_count ; 
 scalar_t__ copy_command_lines (scalar_t__) ; 
 int /*<<< orphan*/  describe_other_breakpoints (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  error (char*) ; 
 int hw_breakpoint_used_count () ; 
 int /*<<< orphan*/  mention (struct breakpoint*) ; 
 int /*<<< orphan*/  paddr (int /*<<< orphan*/ ) ; 
 struct expression* parse_exp_1 (char**,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* savestring (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_breakpoint_count (scalar_t__) ; 
 struct breakpoint* set_raw_breakpoint (struct symtab_and_line,int) ; 
 int /*<<< orphan*/  strlen (char*) ; 
 int /*<<< orphan*/  xasprintf (char**,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
create_breakpoints (struct symtabs_and_lines sals, char **addr_string,
		    struct expression **cond, char **cond_string,
		    enum bptype type, enum bpdisp disposition,
		    int thread, int ignore_count, int from_tty,
		    struct breakpoint *pending_bp)
{
  if (type == bp_hardware_breakpoint)
    {
      int i = hw_breakpoint_used_count ();
      int target_resources_ok = 
	TARGET_CAN_USE_HARDWARE_WATCHPOINT (bp_hardware_breakpoint, 
					    i + sals.nelts, 0);
      if (target_resources_ok == 0)
	error ("No hardware breakpoint support in the target.");
      else if (target_resources_ok < 0)
	error ("Hardware breakpoints used exceeds limit.");
    }

  /* Now set all the breakpoints.  */
  {
    int i;
    for (i = 0; i < sals.nelts; i++)
      {
	struct breakpoint *b;
	struct symtab_and_line sal = sals.sals[i];

	if (from_tty)
	  describe_other_breakpoints (sal.pc, sal.section);
	
	b = set_raw_breakpoint (sal, type);
	set_breakpoint_count (breakpoint_count + 1);
	b->number = breakpoint_count;
	b->cond = cond[i];
	b->thread = thread;
	if (addr_string[i])
	  b->addr_string = addr_string[i];
	else
	  /* addr_string has to be used or breakpoint_re_set will delete
	     me.  */
	  xasprintf (&b->addr_string, "*0x%s", paddr (b->loc->address));
	b->cond_string = cond_string[i];
	b->ignore_count = ignore_count;
	b->enable_state = bp_enabled;
	b->disposition = disposition;
	/* If resolving a pending breakpoint, a check must be made to see if
	   the user has specified a new condition or commands for the 
	   breakpoint.  A new condition will override any condition that was 
	   initially specified with the initial breakpoint command.  */
	if (pending_bp)
	  {
	    char *arg;
	    if (pending_bp->cond_string)
	      {
		arg = pending_bp->cond_string;
		b->cond_string = savestring (arg, strlen (arg));
		b->cond = parse_exp_1 (&arg, block_for_pc (b->loc->address), 0);
		if (*arg)
		  error ("Junk at end of pending breakpoint condition expression");
	      }
	    /* If there are commands associated with the breakpoint, they should 
	       be copied too.  */
	    if (pending_bp->commands)
	      b->commands = copy_command_lines (pending_bp->commands);
	    
	    /* We have to copy over the ignore_count and thread as well.  */
	    b->ignore_count = pending_bp->ignore_count;
	    b->thread = pending_bp->thread;
	  }
	mention (b);
      }
  }    
}