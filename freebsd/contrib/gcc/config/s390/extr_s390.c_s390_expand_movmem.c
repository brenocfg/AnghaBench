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
typedef  enum machine_mode { ____Placeholder_machine_mode } machine_mode ;

/* Variables and functions */
 scalar_t__ CONST_INT ; 
 int /*<<< orphan*/  EQ ; 
 int /*<<< orphan*/  GEN_INT (int) ; 
 scalar_t__ GET_CODE (scalar_t__) ; 
 int GET_MODE (scalar_t__) ; 
 int INTVAL (scalar_t__) ; 
 int /*<<< orphan*/  NULL_RTX ; 
 int Pmode ; 
 scalar_t__ TARGET_MVCLE ; 
 int VOIDmode ; 
 int /*<<< orphan*/  XEXP (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  add_optab ; 
 scalar_t__ change_address (scalar_t__,int,scalar_t__) ; 
 int /*<<< orphan*/  const0_rtx ; 
 int /*<<< orphan*/  constm1_rtx ; 
 int /*<<< orphan*/  convert_move (scalar_t__,scalar_t__,int) ; 
 int /*<<< orphan*/  convert_to_mode (int,scalar_t__,int) ; 
 int /*<<< orphan*/  emit_cmp_and_jump_insns (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,scalar_t__) ; 
 int /*<<< orphan*/  emit_insn (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emit_jump (scalar_t__) ; 
 int /*<<< orphan*/  emit_label (scalar_t__) ; 
 int /*<<< orphan*/  emit_move_insn (scalar_t__,scalar_t__) ; 
 scalar_t__ expand_binop (int,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,scalar_t__,int,int /*<<< orphan*/ ) ; 
 scalar_t__ force_operand (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ gen_label_rtx () ; 
 int /*<<< orphan*/  gen_movmem_long (scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_movmem_short (scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ gen_reg_rtx (int) ; 
 int /*<<< orphan*/  gen_rtx_PLUS (int,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lshr_optab ; 
 int /*<<< orphan*/  s390_load_address (scalar_t__,int /*<<< orphan*/ ) ; 

void
s390_expand_movmem (rtx dst, rtx src, rtx len)
{
  if (GET_CODE (len) == CONST_INT && INTVAL (len) >= 0 && INTVAL (len) <= 256)
    {
      if (INTVAL (len) > 0)
        emit_insn (gen_movmem_short (dst, src, GEN_INT (INTVAL (len) - 1)));
    }

  else if (TARGET_MVCLE)
    {
      emit_insn (gen_movmem_long (dst, src, convert_to_mode (Pmode, len, 1)));
    }

  else
    {
      rtx dst_addr, src_addr, count, blocks, temp;
      rtx loop_start_label = gen_label_rtx ();
      rtx loop_end_label = gen_label_rtx ();
      rtx end_label = gen_label_rtx ();
      enum machine_mode mode;

      mode = GET_MODE (len);
      if (mode == VOIDmode)
        mode = Pmode;

      dst_addr = gen_reg_rtx (Pmode);
      src_addr = gen_reg_rtx (Pmode);
      count = gen_reg_rtx (mode);
      blocks = gen_reg_rtx (mode);

      convert_move (count, len, 1);
      emit_cmp_and_jump_insns (count, const0_rtx,
			       EQ, NULL_RTX, mode, 1, end_label);

      emit_move_insn (dst_addr, force_operand (XEXP (dst, 0), NULL_RTX));
      emit_move_insn (src_addr, force_operand (XEXP (src, 0), NULL_RTX));
      dst = change_address (dst, VOIDmode, dst_addr);
      src = change_address (src, VOIDmode, src_addr);

      temp = expand_binop (mode, add_optab, count, constm1_rtx, count, 1, 0);
      if (temp != count)
        emit_move_insn (count, temp);

      temp = expand_binop (mode, lshr_optab, count, GEN_INT (8), blocks, 1, 0);
      if (temp != blocks)
        emit_move_insn (blocks, temp);

      emit_cmp_and_jump_insns (blocks, const0_rtx,
			       EQ, NULL_RTX, mode, 1, loop_end_label);

      emit_label (loop_start_label);

      emit_insn (gen_movmem_short (dst, src, GEN_INT (255)));
      s390_load_address (dst_addr,
			 gen_rtx_PLUS (Pmode, dst_addr, GEN_INT (256)));
      s390_load_address (src_addr,
			 gen_rtx_PLUS (Pmode, src_addr, GEN_INT (256)));

      temp = expand_binop (mode, add_optab, blocks, constm1_rtx, blocks, 1, 0);
      if (temp != blocks)
        emit_move_insn (blocks, temp);

      emit_cmp_and_jump_insns (blocks, const0_rtx,
			       EQ, NULL_RTX, mode, 1, loop_end_label);

      emit_jump (loop_start_label);
      emit_label (loop_end_label);

      emit_insn (gen_movmem_short (dst, src,
				   convert_to_mode (Pmode, count, 1)));
      emit_label (end_label);
    }
}