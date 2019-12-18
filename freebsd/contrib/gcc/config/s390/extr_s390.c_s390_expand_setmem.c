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
 scalar_t__ GET_MODE (scalar_t__) ; 
 int INTVAL (scalar_t__) ; 
 scalar_t__ NULL_RTX ; 
 int Pmode ; 
 scalar_t__ QImode ; 
 scalar_t__ TARGET_MVCLE ; 
 int VOIDmode ; 
 int /*<<< orphan*/  XEXP (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  add_optab ; 
 scalar_t__ adjust_address (scalar_t__,scalar_t__,int) ; 
 scalar_t__ change_address (scalar_t__,int,scalar_t__) ; 
 scalar_t__ const0_rtx ; 
 scalar_t__ const1_rtx ; 
 int /*<<< orphan*/  constm1_rtx ; 
 int /*<<< orphan*/  convert_modes (int,scalar_t__,scalar_t__,int) ; 
 int /*<<< orphan*/  convert_move (scalar_t__,scalar_t__,int) ; 
 int /*<<< orphan*/  convert_to_mode (int,scalar_t__,int) ; 
 int /*<<< orphan*/  emit_cmp_and_jump_insns (scalar_t__,scalar_t__,int /*<<< orphan*/ ,scalar_t__,int,int,scalar_t__) ; 
 int /*<<< orphan*/  emit_insn (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emit_jump (scalar_t__) ; 
 int /*<<< orphan*/  emit_label (scalar_t__) ; 
 int /*<<< orphan*/  emit_move_insn (scalar_t__,scalar_t__) ; 
 scalar_t__ expand_binop (int,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,scalar_t__,int,int /*<<< orphan*/ ) ; 
 scalar_t__ force_not_mem (int /*<<< orphan*/ ) ; 
 scalar_t__ force_operand (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  gcc_assert (int) ; 
 int /*<<< orphan*/  gen_clrmem_short (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ gen_label_rtx () ; 
 int /*<<< orphan*/  gen_movmem_short (scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ gen_reg_rtx (int) ; 
 int /*<<< orphan*/  gen_rtx_PLUS (int,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_setmem_long (scalar_t__,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  lshr_optab ; 
 int /*<<< orphan*/  s390_load_address (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_mem_size (scalar_t__,scalar_t__) ; 

void
s390_expand_setmem (rtx dst, rtx len, rtx val)
{
  if (GET_CODE (len) == CONST_INT && INTVAL (len) == 0)
    return;

  gcc_assert (GET_CODE (val) == CONST_INT || GET_MODE (val) == QImode);
  
  if (GET_CODE (len) == CONST_INT && INTVAL (len) > 0 && INTVAL (len) <= 257)
    {
      if (val == const0_rtx && INTVAL (len) <= 256)
        emit_insn (gen_clrmem_short (dst, GEN_INT (INTVAL (len) - 1)));
      else
	{
	  /* Initialize memory by storing the first byte.  */
	  emit_move_insn (adjust_address (dst, QImode, 0), val);
	  
	  if (INTVAL (len) > 1)
	    {
	      /* Initiate 1 byte overlap move.
	         The first byte of DST is propagated through DSTP1.
		 Prepare a movmem for:  DST+1 = DST (length = LEN - 1).
		 DST is set to size 1 so the rest of the memory location
		 does not count as source operand.  */
	      rtx dstp1 = adjust_address (dst, VOIDmode, 1);
	      set_mem_size (dst, const1_rtx);

	      emit_insn (gen_movmem_short (dstp1, dst, 
					   GEN_INT (INTVAL (len) - 2)));
	    }
	}
    }

  else if (TARGET_MVCLE)
    {
      val = force_not_mem (convert_modes (Pmode, QImode, val, 1));
      emit_insn (gen_setmem_long (dst, convert_to_mode (Pmode, len, 1), val));
    }

  else
    {
      rtx dst_addr, src_addr, count, blocks, temp, dstp1 = NULL_RTX;
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
      dst = change_address (dst, VOIDmode, dst_addr);

      if (val == const0_rtx)
        temp = expand_binop (mode, add_optab, count, constm1_rtx, count, 1, 0);
      else
	{
	  dstp1 = adjust_address (dst, VOIDmode, 1);
	  set_mem_size (dst, const1_rtx);

	  /* Initialize memory by storing the first byte.  */
	  emit_move_insn (adjust_address (dst, QImode, 0), val);
	  
	  /* If count is 1 we are done.  */
	  emit_cmp_and_jump_insns (count, const1_rtx,
				   EQ, NULL_RTX, mode, 1, end_label);

	  temp = expand_binop (mode, add_optab, count, GEN_INT (-2), count, 1, 0);
	}
      if (temp != count)
        emit_move_insn (count, temp);

      temp = expand_binop (mode, lshr_optab, count, GEN_INT (8), blocks, 1, 0);
      if (temp != blocks)
        emit_move_insn (blocks, temp);

      emit_cmp_and_jump_insns (blocks, const0_rtx,
			       EQ, NULL_RTX, mode, 1, loop_end_label);

      emit_label (loop_start_label);

      if (val == const0_rtx)
	emit_insn (gen_clrmem_short (dst, GEN_INT (255)));
      else
	emit_insn (gen_movmem_short (dstp1, dst, GEN_INT (255)));
      s390_load_address (dst_addr,
			 gen_rtx_PLUS (Pmode, dst_addr, GEN_INT (256)));

      temp = expand_binop (mode, add_optab, blocks, constm1_rtx, blocks, 1, 0);
      if (temp != blocks)
        emit_move_insn (blocks, temp);

      emit_cmp_and_jump_insns (blocks, const0_rtx,
			       EQ, NULL_RTX, mode, 1, loop_end_label);

      emit_jump (loop_start_label);
      emit_label (loop_end_label);

      if (val == const0_rtx)
        emit_insn (gen_clrmem_short (dst, convert_to_mode (Pmode, count, 1)));
      else
        emit_insn (gen_movmem_short (dstp1, dst, convert_to_mode (Pmode, count, 1)));
      emit_label (end_label);
    }
}