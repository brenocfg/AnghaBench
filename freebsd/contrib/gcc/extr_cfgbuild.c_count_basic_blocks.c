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
typedef  scalar_t__ rtx ;

/* Variables and functions */
 scalar_t__ BARRIER_P (scalar_t__) ; 
 scalar_t__ LABEL_P (scalar_t__) ; 
 scalar_t__ NEXT_INSN (scalar_t__) ; 
 int NUM_FIXED_BLOCKS ; 
 int /*<<< orphan*/  VOIDmode ; 
 int /*<<< orphan*/  const0_rtx ; 
 scalar_t__ control_flow_insn_p (scalar_t__) ; 
 int /*<<< orphan*/  emit_insn (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_rtx_USE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ inside_basic_block_p (scalar_t__) ; 

__attribute__((used)) static int
count_basic_blocks (rtx f)
{
  int count = NUM_FIXED_BLOCKS;
  bool saw_insn = false;
  rtx insn;

  for (insn = f; insn; insn = NEXT_INSN (insn))
    {
      /* Code labels and barriers causes current basic block to be
	 terminated at previous real insn.  */
      if ((LABEL_P (insn) || BARRIER_P (insn))
	  && saw_insn)
	count++, saw_insn = false;

      /* Start basic block if needed.  */
      if (!saw_insn && inside_basic_block_p (insn))
	saw_insn = true;

      /* Control flow insn causes current basic block to be terminated.  */
      if (saw_insn && control_flow_insn_p (insn))
	count++, saw_insn = false;
    }

  if (saw_insn)
    count++;

  /* The rest of the compiler works a bit smoother when we don't have to
     check for the edge case of do-nothing functions with no basic blocks.  */
  if (count == NUM_FIXED_BLOCKS)
    {
      emit_insn (gen_rtx_USE (VOIDmode, const0_rtx));
      count = NUM_FIXED_BLOCKS + 1;
    }

  return count;
}