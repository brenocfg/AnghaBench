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
struct mips_sim {int dummy; } ;
typedef  int /*<<< orphan*/  rtx ;

/* Variables and functions */
#define  CALL_INSN 130 
#define  CODE_LABEL 129 
 int GET_CODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INSN_ANNULLED_BRANCH_P (int /*<<< orphan*/ ) ; 
#define  JUMP_INSN 128 
 scalar_t__ JUMP_P (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SEQ_BEGIN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mips_sim_issue_nop (struct mips_sim*) ; 
 int /*<<< orphan*/  mips_sim_reset (struct mips_sim*) ; 

__attribute__((used)) static void
mips_sim_finish_insn (struct mips_sim *state, rtx insn)
{
  /* If INSN is a jump with an implicit delay slot, simulate a nop.  */
  if (JUMP_P (insn))
    mips_sim_issue_nop (state);

  switch (GET_CODE (SEQ_BEGIN (insn)))
    {
    case CODE_LABEL:
    case CALL_INSN:
      /* We can't predict the processor state after a call or label.  */
      mips_sim_reset (state);
      break;

    case JUMP_INSN:
      /* The delay slots of branch likely instructions are only executed
	 when the branch is taken.  Therefore, if the caller has simulated
	 the delay slot instruction, STATE does not really reflect the state
	 of the pipeline for the instruction after the delay slot.  Also,
	 branch likely instructions tend to incur a penalty when not taken,
	 so there will probably be an extra delay between the branch and
	 the instruction after the delay slot.  */
      if (INSN_ANNULLED_BRANCH_P (SEQ_BEGIN (insn)))
	mips_sim_reset (state);
      break;

    default:
      break;
    }
}