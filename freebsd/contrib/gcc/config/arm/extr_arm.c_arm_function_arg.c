#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tree ;
typedef  int /*<<< orphan*/  rtx ;
typedef  enum machine_mode { ____Placeholder_machine_mode } machine_mode ;
struct TYPE_3__ {scalar_t__ named_count; scalar_t__ nargs; int iwmmxt_nregs; int can_split; int nregs; int /*<<< orphan*/  call_cookie; } ;
typedef  TYPE_1__ CUMULATIVE_ARGS ;

/* Variables and functions */
 scalar_t__ ARM_DOUBLEWORD_ALIGN ; 
 int ARM_NUM_REGS2 (int,int /*<<< orphan*/ ) ; 
 int FIRST_IWMMXT_REGNUM ; 
 int /*<<< orphan*/  GEN_INT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NULL_RTX ; 
 int NUM_ARG_REGS ; 
 scalar_t__ TARGET_IWMMXT_ABI ; 
 int VOIDmode ; 
 scalar_t__ arm_needs_doubleword_align (int,int /*<<< orphan*/ ) ; 
 scalar_t__ arm_vector_mode_supported_p (int) ; 
 int /*<<< orphan*/  gen_rtx_REG (int,int) ; 

rtx
arm_function_arg (CUMULATIVE_ARGS *pcum, enum machine_mode mode,
		  tree type, int named)
{
  int nregs;

  /* Varargs vectors are treated the same as long long.
     named_count avoids having to change the way arm handles 'named' */
  if (TARGET_IWMMXT_ABI
      && arm_vector_mode_supported_p (mode)
      && pcum->named_count > pcum->nargs + 1)
    {
      if (pcum->iwmmxt_nregs <= 9)
	return gen_rtx_REG (mode, pcum->iwmmxt_nregs + FIRST_IWMMXT_REGNUM);
      else
	{
	  pcum->can_split = false;
	  return NULL_RTX;
	}
    }

  /* Put doubleword aligned quantities in even register pairs.  */
  if (pcum->nregs & 1
      && ARM_DOUBLEWORD_ALIGN
      && arm_needs_doubleword_align (mode, type))
    pcum->nregs++;

  if (mode == VOIDmode)
    /* Compute operand 2 of the call insn.  */
    return GEN_INT (pcum->call_cookie);

  /* Only allow splitting an arg between regs and memory if all preceding
     args were allocated to regs.  For args passed by reference we only count
     the reference pointer.  */
  if (pcum->can_split)
    nregs = 1;
  else
    nregs = ARM_NUM_REGS2 (mode, type);

  if (!named || pcum->nregs + nregs > NUM_ARG_REGS)
    return NULL_RTX;

  return gen_rtx_REG (mode, pcum->nregs);
}