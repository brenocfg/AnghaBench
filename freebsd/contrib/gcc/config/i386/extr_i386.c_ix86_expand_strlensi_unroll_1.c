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
typedef  int /*<<< orphan*/  JUMP_LABEL ;

/* Variables and functions */
 int /*<<< orphan*/  CCNOmode ; 
 int /*<<< orphan*/  CCmode ; 
 scalar_t__ CONST_INT ; 
 int /*<<< orphan*/  EQ ; 
 int FLAGS_REG ; 
 int /*<<< orphan*/  GEN_INT (int) ; 
 scalar_t__ GET_CODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GTU ; 
 int INTVAL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NULL_RTX ; 
 int /*<<< orphan*/  OPTAB_WIDEN ; 
 int /*<<< orphan*/  Pmode ; 
 int /*<<< orphan*/  QImode ; 
 int /*<<< orphan*/  SImode ; 
 scalar_t__ TARGET_64BIT ; 
 scalar_t__ TARGET_CMOVE ; 
 int /*<<< orphan*/  VOIDmode ; 
 int /*<<< orphan*/  and_optab ; 
 int /*<<< orphan*/  change_address (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  const0_rtx ; 
 int /*<<< orphan*/  const1_rtx ; 
 int /*<<< orphan*/  const2_rtx ; 
 int /*<<< orphan*/  emit_cmp_and_jump_insns (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emit_insn (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emit_jump_insn (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emit_label (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emit_move_insn (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  expand_binop (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_adddi3 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_addqi3_cc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_addsi3 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_andsi3 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_int_mode (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_label_rtx () ; 
 int /*<<< orphan*/  gen_lowpart (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_lshrsi3 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_one_cmplsi2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_reg_rtx (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_rtx_EQ (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_rtx_IF_THEN_ELSE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_rtx_LABEL_REF (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_rtx_LTU (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_rtx_NE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_rtx_PLUS (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_rtx_REG (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  gen_rtx_SET (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_subdi3_carry_rex64 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_subsi3_carry (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_testsi_ccno_1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pc_rtx ; 

__attribute__((used)) static void
ix86_expand_strlensi_unroll_1 (rtx out, rtx src, rtx align_rtx)
{
  int align;
  rtx tmp;
  rtx align_2_label = NULL_RTX;
  rtx align_3_label = NULL_RTX;
  rtx align_4_label = gen_label_rtx ();
  rtx end_0_label = gen_label_rtx ();
  rtx mem;
  rtx tmpreg = gen_reg_rtx (SImode);
  rtx scratch = gen_reg_rtx (SImode);
  rtx cmp;

  align = 0;
  if (GET_CODE (align_rtx) == CONST_INT)
    align = INTVAL (align_rtx);

  /* Loop to check 1..3 bytes for null to get an aligned pointer.  */

  /* Is there a known alignment and is it less than 4?  */
  if (align < 4)
    {
      rtx scratch1 = gen_reg_rtx (Pmode);
      emit_move_insn (scratch1, out);
      /* Is there a known alignment and is it not 2? */
      if (align != 2)
	{
	  align_3_label = gen_label_rtx (); /* Label when aligned to 3-byte */
	  align_2_label = gen_label_rtx (); /* Label when aligned to 2-byte */

	  /* Leave just the 3 lower bits.  */
	  align_rtx = expand_binop (Pmode, and_optab, scratch1, GEN_INT (3),
				    NULL_RTX, 0, OPTAB_WIDEN);

	  emit_cmp_and_jump_insns (align_rtx, const0_rtx, EQ, NULL,
				   Pmode, 1, align_4_label);
	  emit_cmp_and_jump_insns (align_rtx, const2_rtx, EQ, NULL,
				   Pmode, 1, align_2_label);
	  emit_cmp_and_jump_insns (align_rtx, const2_rtx, GTU, NULL,
				   Pmode, 1, align_3_label);
	}
      else
        {
	  /* Since the alignment is 2, we have to check 2 or 0 bytes;
	     check if is aligned to 4 - byte.  */

	  align_rtx = expand_binop (Pmode, and_optab, scratch1, const2_rtx,
				    NULL_RTX, 0, OPTAB_WIDEN);

	  emit_cmp_and_jump_insns (align_rtx, const0_rtx, EQ, NULL,
				   Pmode, 1, align_4_label);
        }

      mem = change_address (src, QImode, out);

      /* Now compare the bytes.  */

      /* Compare the first n unaligned byte on a byte per byte basis.  */
      emit_cmp_and_jump_insns (mem, const0_rtx, EQ, NULL,
			       QImode, 1, end_0_label);

      /* Increment the address.  */
      if (TARGET_64BIT)
	emit_insn (gen_adddi3 (out, out, const1_rtx));
      else
	emit_insn (gen_addsi3 (out, out, const1_rtx));

      /* Not needed with an alignment of 2 */
      if (align != 2)
	{
	  emit_label (align_2_label);

	  emit_cmp_and_jump_insns (mem, const0_rtx, EQ, NULL, QImode, 1,
				   end_0_label);

	  if (TARGET_64BIT)
	    emit_insn (gen_adddi3 (out, out, const1_rtx));
	  else
	    emit_insn (gen_addsi3 (out, out, const1_rtx));

	  emit_label (align_3_label);
	}

      emit_cmp_and_jump_insns (mem, const0_rtx, EQ, NULL, QImode, 1,
			       end_0_label);

      if (TARGET_64BIT)
	emit_insn (gen_adddi3 (out, out, const1_rtx));
      else
	emit_insn (gen_addsi3 (out, out, const1_rtx));
    }

  /* Generate loop to check 4 bytes at a time.  It is not a good idea to
     align this loop.  It gives only huge programs, but does not help to
     speed up.  */
  emit_label (align_4_label);

  mem = change_address (src, SImode, out);
  emit_move_insn (scratch, mem);
  if (TARGET_64BIT)
    emit_insn (gen_adddi3 (out, out, GEN_INT (4)));
  else
    emit_insn (gen_addsi3 (out, out, GEN_INT (4)));

  /* This formula yields a nonzero result iff one of the bytes is zero.
     This saves three branches inside loop and many cycles.  */

  emit_insn (gen_addsi3 (tmpreg, scratch, GEN_INT (-0x01010101)));
  emit_insn (gen_one_cmplsi2 (scratch, scratch));
  emit_insn (gen_andsi3 (tmpreg, tmpreg, scratch));
  emit_insn (gen_andsi3 (tmpreg, tmpreg,
			 gen_int_mode (0x80808080, SImode)));
  emit_cmp_and_jump_insns (tmpreg, const0_rtx, EQ, 0, SImode, 1,
			   align_4_label);

  if (TARGET_CMOVE)
    {
       rtx reg = gen_reg_rtx (SImode);
       rtx reg2 = gen_reg_rtx (Pmode);
       emit_move_insn (reg, tmpreg);
       emit_insn (gen_lshrsi3 (reg, reg, GEN_INT (16)));

       /* If zero is not in the first two bytes, move two bytes forward.  */
       emit_insn (gen_testsi_ccno_1 (tmpreg, GEN_INT (0x8080)));
       tmp = gen_rtx_REG (CCNOmode, FLAGS_REG);
       tmp = gen_rtx_EQ (VOIDmode, tmp, const0_rtx);
       emit_insn (gen_rtx_SET (VOIDmode, tmpreg,
			       gen_rtx_IF_THEN_ELSE (SImode, tmp,
						     reg,
						     tmpreg)));
       /* Emit lea manually to avoid clobbering of flags.  */
       emit_insn (gen_rtx_SET (SImode, reg2,
			       gen_rtx_PLUS (Pmode, out, const2_rtx)));

       tmp = gen_rtx_REG (CCNOmode, FLAGS_REG);
       tmp = gen_rtx_EQ (VOIDmode, tmp, const0_rtx);
       emit_insn (gen_rtx_SET (VOIDmode, out,
			       gen_rtx_IF_THEN_ELSE (Pmode, tmp,
						     reg2,
						     out)));

    }
  else
    {
       rtx end_2_label = gen_label_rtx ();
       /* Is zero in the first two bytes? */

       emit_insn (gen_testsi_ccno_1 (tmpreg, GEN_INT (0x8080)));
       tmp = gen_rtx_REG (CCNOmode, FLAGS_REG);
       tmp = gen_rtx_NE (VOIDmode, tmp, const0_rtx);
       tmp = gen_rtx_IF_THEN_ELSE (VOIDmode, tmp,
                            gen_rtx_LABEL_REF (VOIDmode, end_2_label),
                            pc_rtx);
       tmp = emit_jump_insn (gen_rtx_SET (VOIDmode, pc_rtx, tmp));
       JUMP_LABEL (tmp) = end_2_label;

       /* Not in the first two.  Move two bytes forward.  */
       emit_insn (gen_lshrsi3 (tmpreg, tmpreg, GEN_INT (16)));
       if (TARGET_64BIT)
	 emit_insn (gen_adddi3 (out, out, const2_rtx));
       else
	 emit_insn (gen_addsi3 (out, out, const2_rtx));

       emit_label (end_2_label);

    }

  /* Avoid branch in fixing the byte.  */
  tmpreg = gen_lowpart (QImode, tmpreg);
  emit_insn (gen_addqi3_cc (tmpreg, tmpreg, tmpreg));
  cmp = gen_rtx_LTU (Pmode, gen_rtx_REG (CCmode, 17), const0_rtx);
  if (TARGET_64BIT)
    emit_insn (gen_subdi3_carry_rex64 (out, out, GEN_INT (3), cmp));
  else
    emit_insn (gen_subsi3_carry (out, out, GEN_INT (3), cmp));

  emit_label (end_0_label);
}