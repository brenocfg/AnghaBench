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
typedef  int /*<<< orphan*/  rtx ;
typedef  enum machine_mode { ____Placeholder_machine_mode } machine_mode ;

/* Variables and functions */
 int /*<<< orphan*/  CONST0_RTX (int) ; 
 int /*<<< orphan*/  DFmode ; 
 scalar_t__ GET_MODE_CLASS (int) ; 
 scalar_t__ MEM_P (int /*<<< orphan*/ ) ; 
 scalar_t__ MODE_VECTOR_INT ; 
 scalar_t__ TARGET_SSE2 ; 
 scalar_t__ TARGET_SSE_PARTIAL_REG_DEPENDENCY ; 
 scalar_t__ TARGET_SSE_SPLIT_REGS ; 
 int /*<<< orphan*/  TARGET_SSE_TYPELESS_STORES ; 
 scalar_t__ TARGET_SSE_UNALIGNED_MOVE_OPTIMAL ; 
 int V16QImode ; 
 int V2DFmode ; 
 int /*<<< orphan*/  V2SFmode ; 
 int V4SFmode ; 
 int /*<<< orphan*/  VOIDmode ; 
 int /*<<< orphan*/  adjust_address (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  emit_insn (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emit_move_insn (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gcc_unreachable () ; 
 int /*<<< orphan*/  gen_lowpart (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_rtx_CLOBBER (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_sse2_loadhpd (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_sse2_loadlpd (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_sse2_movdqu (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_sse2_movupd (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_sse2_storehpd (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_sse2_storelpd (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_sse_loadhps (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_sse_loadlps (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_sse_movups (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_sse_storehps (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_sse_storelps (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ optimize_size ; 

void
ix86_expand_vector_move_misalign (enum machine_mode mode, rtx operands[])
{
  rtx op0, op1, m;

  op0 = operands[0];
  op1 = operands[1];

  if (MEM_P (op1))
    {
      /* If we're optimizing for size, movups is the smallest.  */
      if (optimize_size)
	{
	  op0 = gen_lowpart (V4SFmode, op0);
	  op1 = gen_lowpart (V4SFmode, op1);
	  emit_insn (gen_sse_movups (op0, op1));
	  return;
	}

      /* ??? If we have typed data, then it would appear that using
	 movdqu is the only way to get unaligned data loaded with
	 integer type.  */
      if (TARGET_SSE2 && GET_MODE_CLASS (mode) == MODE_VECTOR_INT)
	{
	  op0 = gen_lowpart (V16QImode, op0);
	  op1 = gen_lowpart (V16QImode, op1);
	  emit_insn (gen_sse2_movdqu (op0, op1));
	  return;
	}

      if (TARGET_SSE2 && mode == V2DFmode)
        {
          rtx zero;

          if (TARGET_SSE_UNALIGNED_MOVE_OPTIMAL)
            {
              op0 = gen_lowpart (V2DFmode, op0);
              op1 = gen_lowpart (V2DFmode, op1);
              emit_insn (gen_sse2_movupd (op0, op1));
              return;
            }

	  /* When SSE registers are split into halves, we can avoid
	     writing to the top half twice.  */
	  if (TARGET_SSE_SPLIT_REGS)
	    {
	      emit_insn (gen_rtx_CLOBBER (VOIDmode, op0));
	      zero = op0;
	    }
	  else
	    {
	      /* ??? Not sure about the best option for the Intel chips.
		 The following would seem to satisfy; the register is
		 entirely cleared, breaking the dependency chain.  We
		 then store to the upper half, with a dependency depth
		 of one.  A rumor has it that Intel recommends two movsd
		 followed by an unpacklpd, but this is unconfirmed.  And
		 given that the dependency depth of the unpacklpd would
		 still be one, I'm not sure why this would be better.  */
	      zero = CONST0_RTX (V2DFmode);
	    }

	  m = adjust_address (op1, DFmode, 0);
	  emit_insn (gen_sse2_loadlpd (op0, zero, m));
	  m = adjust_address (op1, DFmode, 8);
	  emit_insn (gen_sse2_loadhpd (op0, op0, m));
	}
      else
        {
          if (TARGET_SSE_UNALIGNED_MOVE_OPTIMAL)
            {
              op0 = gen_lowpart (V4SFmode, op0);
              op1 = gen_lowpart (V4SFmode, op1);
              emit_insn (gen_sse_movups (op0, op1));
              return;
            }

	  if (TARGET_SSE_PARTIAL_REG_DEPENDENCY)
	    emit_move_insn (op0, CONST0_RTX (mode));
	  else
	    emit_insn (gen_rtx_CLOBBER (VOIDmode, op0));

	  if (mode != V4SFmode)
	    op0 = gen_lowpart (V4SFmode, op0);
	  m = adjust_address (op1, V2SFmode, 0);
	  emit_insn (gen_sse_loadlps (op0, op0, m));
	  m = adjust_address (op1, V2SFmode, 8);
	  emit_insn (gen_sse_loadhps (op0, op0, m));
	}
    }
  else if (MEM_P (op0))
    {
      /* If we're optimizing for size, movups is the smallest.  */
      if (optimize_size)
	{
	  op0 = gen_lowpart (V4SFmode, op0);
	  op1 = gen_lowpart (V4SFmode, op1);
	  emit_insn (gen_sse_movups (op0, op1));
	  return;
	}

      /* ??? Similar to above, only less clear because of quote
	 typeless stores unquote.  */
      if (TARGET_SSE2 && !TARGET_SSE_TYPELESS_STORES
	  && GET_MODE_CLASS (mode) == MODE_VECTOR_INT)
        {
	  op0 = gen_lowpart (V16QImode, op0);
	  op1 = gen_lowpart (V16QImode, op1);
	  emit_insn (gen_sse2_movdqu (op0, op1));
	  return;
	}

      if (TARGET_SSE2 && mode == V2DFmode)
	{
	  m = adjust_address (op0, DFmode, 0);
	  emit_insn (gen_sse2_storelpd (m, op1));
	  m = adjust_address (op0, DFmode, 8);
	  emit_insn (gen_sse2_storehpd (m, op1));
	}
      else
	{
	  if (mode != V4SFmode)
	    op1 = gen_lowpart (V4SFmode, op1);
	  m = adjust_address (op0, V2SFmode, 0);
	  emit_insn (gen_sse_storelps (m, op1));
	  m = adjust_address (op0, V2SFmode, 8);
	  emit_insn (gen_sse_storehps (m, op1));
	}
    }
  else
    gcc_unreachable ();
}