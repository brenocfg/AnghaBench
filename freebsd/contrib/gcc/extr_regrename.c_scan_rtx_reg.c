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
struct du_chain {void** loc; int cl; int earlyclobber; struct du_chain* next_chain; struct du_chain* next_use; scalar_t__ need_caller_save_reg; void* insn; } ;
typedef  void* rtx ;
typedef  enum scan_actions { ____Placeholder_scan_actions } scan_actions ;
typedef  enum reg_class { ____Placeholder_reg_class } reg_class ;
typedef  enum op_type { ____Placeholder_op_type } op_type ;
typedef  enum machine_mode { ____Placeholder_machine_mode } machine_mode ;

/* Variables and functions */
 size_t GET_MODE (void*) ; 
 int INSN_UID (void*) ; 
 int NO_REGS ; 
 int OP_OUT ; 
 size_t REGNO (void*) ; 
 scalar_t__ cc0_rtx ; 
 struct du_chain* closed_chains ; 
 scalar_t__ dump_file ; 
 int /*<<< orphan*/  fprintf (scalar_t__,char*,char*,int,char*) ; 
 int /*<<< orphan*/  gcc_assert (int) ; 
 int** hard_regno_nregs ; 
 int mark_access ; 
 int mark_read ; 
 int mark_write ; 
 struct du_chain* obstack_alloc (int /*<<< orphan*/ *,int) ; 
 struct du_chain* open_chains ; 
 char** reg_names ; 
 int /*<<< orphan*/  rename_obstack ; 
 char** scan_actions_name ; 
 int terminate_dead ; 
 int terminate_overlapping_read ; 
 int terminate_write ; 

__attribute__((used)) static void
scan_rtx_reg (rtx insn, rtx *loc, enum reg_class cl,
	      enum scan_actions action, enum op_type type, int earlyclobber)
{
  struct du_chain **p;
  rtx x = *loc;
  enum machine_mode mode = GET_MODE (x);
  int this_regno = REGNO (x);
  int this_nregs = hard_regno_nregs[this_regno][mode];

  if (action == mark_write)
    {
      if (type == OP_OUT)
	{
	  struct du_chain *this
	    = obstack_alloc (&rename_obstack, sizeof (struct du_chain));
	  this->next_use = 0;
	  this->next_chain = open_chains;
	  this->loc = loc;
	  this->insn = insn;
	  this->cl = cl;
	  this->need_caller_save_reg = 0;
	  this->earlyclobber = earlyclobber;
	  open_chains = this;
	}
      return;
    }

  if ((type == OP_OUT) != (action == terminate_write || action == mark_access))
    return;

  for (p = &open_chains; *p;)
    {
      struct du_chain *this = *p;

      /* Check if the chain has been terminated if it has then skip to
	 the next chain.

	 This can happen when we've already appended the location to
	 the chain in Step 3, but are trying to hide in-out operands
	 from terminate_write in Step 5.  */

      if (*this->loc == cc0_rtx)
	p = &this->next_chain;
      else
	{
	  int regno = REGNO (*this->loc);
	  int nregs = hard_regno_nregs[regno][GET_MODE (*this->loc)];
	  int exact_match = (regno == this_regno && nregs == this_nregs);

	  if (regno + nregs <= this_regno
	      || this_regno + this_nregs <= regno)
	    {
	      p = &this->next_chain;
	      continue;
	    }

	  if (action == mark_read || action == mark_access)
	    {
	      gcc_assert (exact_match);

	      /* ??? Class NO_REGS can happen if the md file makes use of
		 EXTRA_CONSTRAINTS to match registers.  Which is arguably
		 wrong, but there we are.  Since we know not what this may
		 be replaced with, terminate the chain.  */
	      if (cl != NO_REGS)
		{
		  this = obstack_alloc (&rename_obstack, sizeof (struct du_chain));
		  this->next_use = 0;
		  this->next_chain = (*p)->next_chain;
		  this->loc = loc;
		  this->insn = insn;
		  this->cl = cl;
		  this->need_caller_save_reg = 0;
		  while (*p)
		    p = &(*p)->next_use;
		  *p = this;
		  return;
		}
	    }

	  if (action != terminate_overlapping_read || ! exact_match)
	    {
	      struct du_chain *next = this->next_chain;

	      /* Whether the terminated chain can be used for renaming
	         depends on the action and this being an exact match.
	         In either case, we remove this element from open_chains.  */

	      if ((action == terminate_dead || action == terminate_write)
		  && exact_match)
		{
		  this->next_chain = closed_chains;
		  closed_chains = this;
		  if (dump_file)
		    fprintf (dump_file,
			     "Closing chain %s at insn %d (%s)\n",
			     reg_names[REGNO (*this->loc)], INSN_UID (insn),
			     scan_actions_name[(int) action]);
		}
	      else
		{
		  if (dump_file)
		    fprintf (dump_file,
			     "Discarding chain %s at insn %d (%s)\n",
			     reg_names[REGNO (*this->loc)], INSN_UID (insn),
			     scan_actions_name[(int) action]);
		}
	      *p = next;
	    }
	  else
	    p = &this->next_chain;
	}
    }
}