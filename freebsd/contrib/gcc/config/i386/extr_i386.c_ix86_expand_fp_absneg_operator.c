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
typedef  enum rtx_code { ____Placeholder_rtx_code } rtx_code ;
typedef  enum machine_mode { ____Placeholder_machine_mode } machine_mode ;

/* Variables and functions */
 int ABS ; 
 int /*<<< orphan*/  AND ; 
 int /*<<< orphan*/  CCmode ; 
 int /*<<< orphan*/  FLAGS_REG ; 
 int GET_MODE_INNER (int) ; 
 scalar_t__ MEM_P (scalar_t__) ; 
 int NEG ; 
 scalar_t__ NULL_RTX ; 
 int SSE_FLOAT_MODE_P (int) ; 
 scalar_t__ TARGET_SSE_MATH ; 
 int VECTOR_MODE_P (int) ; 
 int /*<<< orphan*/  VOIDmode ; 
 int /*<<< orphan*/  XOR ; 
 int /*<<< orphan*/  emit_insn (scalar_t__) ; 
 int /*<<< orphan*/  emit_move_insn (scalar_t__,scalar_t__) ; 
 scalar_t__ force_reg (int,scalar_t__) ; 
 scalar_t__ gen_reg_rtx (int) ; 
 int /*<<< orphan*/  gen_rtvec (int,scalar_t__,scalar_t__,scalar_t__) ; 
 scalar_t__ gen_rtx_CLOBBER (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ gen_rtx_PARALLEL (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_rtx_REG (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ gen_rtx_SET (int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 scalar_t__ gen_rtx_USE (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ gen_rtx_fmt_e (int,int,scalar_t__) ; 
 scalar_t__ gen_rtx_fmt_ee (int /*<<< orphan*/ ,int,scalar_t__,scalar_t__) ; 
 scalar_t__ ix86_build_signbit_mask (int,int,int) ; 
 scalar_t__ rtx_equal_p (scalar_t__,scalar_t__) ; 

void
ix86_expand_fp_absneg_operator (enum rtx_code code, enum machine_mode mode,
				rtx operands[])
{
  rtx mask, set, use, clob, dst, src;
  bool matching_memory;
  bool use_sse = false;
  bool vector_mode = VECTOR_MODE_P (mode);
  enum machine_mode elt_mode = mode;

  if (vector_mode)
    {
      elt_mode = GET_MODE_INNER (mode);
      use_sse = true;
    }
  else if (TARGET_SSE_MATH)
    use_sse = SSE_FLOAT_MODE_P (mode);

  /* NEG and ABS performed with SSE use bitwise mask operations.
     Create the appropriate mask now.  */
  if (use_sse)
    mask = ix86_build_signbit_mask (elt_mode, vector_mode, code == ABS);
  else
    mask = NULL_RTX;

  dst = operands[0];
  src = operands[1];

  /* If the destination is memory, and we don't have matching source
     operands or we're using the x87, do things in registers.  */
  matching_memory = false;
  if (MEM_P (dst))
    {
      if (use_sse && rtx_equal_p (dst, src))
	matching_memory = true;
      else
	dst = gen_reg_rtx (mode);
    }
  if (MEM_P (src) && !matching_memory)
    src = force_reg (mode, src);

  if (vector_mode)
    {
      set = gen_rtx_fmt_ee (code == NEG ? XOR : AND, mode, src, mask);
      set = gen_rtx_SET (VOIDmode, dst, set);
      emit_insn (set);
    }
  else
    {
      set = gen_rtx_fmt_e (code, mode, src);
      set = gen_rtx_SET (VOIDmode, dst, set);
      if (mask)
        {
          use = gen_rtx_USE (VOIDmode, mask);
          clob = gen_rtx_CLOBBER (VOIDmode, gen_rtx_REG (CCmode, FLAGS_REG));
          emit_insn (gen_rtx_PARALLEL (VOIDmode,
				       gen_rtvec (3, set, use, clob)));
        }
      else
	emit_insn (set);
    }

  if (dst != operands[0])
    emit_move_insn (operands[0], dst);
}