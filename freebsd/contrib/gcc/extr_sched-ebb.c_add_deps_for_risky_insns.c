#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ rtx ;
typedef  enum DEPS_ADJUST_RESULT { ____Placeholder_DEPS_ADJUST_RESULT } DEPS_ADJUST_RESULT ;
typedef  TYPE_1__* basic_block ;
struct TYPE_8__ {int flags; } ;
struct TYPE_7__ {struct TYPE_7__* aux; } ;

/* Variables and functions */
 scalar_t__ BB_END (TYPE_1__*) ; 
 int /*<<< orphan*/  BEGIN_CONTROL ; 
 TYPE_1__* BLOCK_FOR_INSN (scalar_t__) ; 
 int /*<<< orphan*/  DEP_ANTI ; 
 int DEP_CHANGED ; 
 int DEP_CREATED ; 
 int DO_SPECULATION ; 
 scalar_t__ INSN_P (scalar_t__) ; 
#define  IRISKY 131 
 int /*<<< orphan*/  LOG_LINKS (scalar_t__) ; 
 int /*<<< orphan*/  MAX_DEP_WEAK ; 
 scalar_t__ NEXT_INSN (scalar_t__) ; 
 scalar_t__ NULL_RTX ; 
#define  PFREE_CANDIDATE 130 
#define  PRISKY_CANDIDATE 129 
 int /*<<< orphan*/  REG_DEP_ANTI ; 
#define  TRAP_RISKY 128 
 int /*<<< orphan*/  add_forw_dep (scalar_t__,int /*<<< orphan*/ ) ; 
 int add_or_update_back_dep (scalar_t__,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  add_or_update_back_forw_dep (scalar_t__,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ control_flow_insn_p (scalar_t__) ; 
 TYPE_4__* current_sched_info ; 
 TYPE_1__* earliest_block_with_similiar_load (TYPE_1__*,scalar_t__) ; 
 int /*<<< orphan*/  flag_schedule_speculative_load ; 
 int /*<<< orphan*/  gcc_assert (int) ; 
 int haifa_classify_insn (scalar_t__) ; 
 int /*<<< orphan*/  sched_insns_conditions_mutex_p (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  set_dep_weak (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
add_deps_for_risky_insns (rtx head, rtx tail)
{
  rtx insn, prev;
  int class;
  rtx last_jump = NULL_RTX;
  rtx next_tail = NEXT_INSN (tail);
  basic_block last_block = NULL, bb;

  for (insn = head; insn != next_tail; insn = NEXT_INSN (insn))
    if (control_flow_insn_p (insn))
      {
	bb = BLOCK_FOR_INSN (insn);
	bb->aux = last_block;
	last_block = bb;
	last_jump = insn;
      }
    else if (INSN_P (insn) && last_jump != NULL_RTX)
      {
	class = haifa_classify_insn (insn);
	prev = last_jump;
	switch (class)
	  {
	  case PFREE_CANDIDATE:
	    if (flag_schedule_speculative_load)
	      {
		bb = earliest_block_with_similiar_load (last_block, insn);
		if (bb)
		  {
		    bb = bb->aux;
		    if (!bb)
		      break;
		    prev = BB_END (bb);
		  }
	      }
	    /* Fall through.  */
	  case TRAP_RISKY:
	  case IRISKY:
	  case PRISKY_CANDIDATE:
	    /* ??? We could implement better checking PRISKY_CANDIDATEs
	       analogous to sched-rgn.c.  */
	    /* We can not change the mode of the backward
	       dependency because REG_DEP_ANTI has the lowest
	       rank.  */
	    if (! sched_insns_conditions_mutex_p (insn, prev))
	      {
		if (!(current_sched_info->flags & DO_SPECULATION))
		  {
		    enum DEPS_ADJUST_RESULT res;
		    
		    res = add_or_update_back_dep (insn, prev,
						  REG_DEP_ANTI, DEP_ANTI);

		    if (res == DEP_CREATED)
		      add_forw_dep (insn, LOG_LINKS (insn));
		    else
		      gcc_assert (res != DEP_CHANGED);
		  }
		else
		  add_or_update_back_forw_dep (insn, prev, REG_DEP_ANTI,
					       set_dep_weak (DEP_ANTI,
							     BEGIN_CONTROL,
							     MAX_DEP_WEAK));
	      }

            break;

          default:
            break;
	  }
      }
  /* Maintain the invariant that bb->aux is clear after use.  */
  while (last_block)
    {
      bb = last_block->aux;
      last_block->aux = NULL;
      last_block = bb;
    }
}