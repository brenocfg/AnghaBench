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
typedef  enum optab_methods { ____Placeholder_optab_methods } optab_methods ;
typedef  enum machine_mode { ____Placeholder_machine_mode } machine_mode ;

/* Variables and functions */
 scalar_t__ BITS_PER_WORD ; 
 scalar_t__ GEN_INT (scalar_t__) ; 
 scalar_t__ NULL_RTX ; 
 int OPTAB_DIRECT ; 
 scalar_t__ REG_P (scalar_t__) ; 
 scalar_t__ WORDS_BIG_ENDIAN ; 
 int /*<<< orphan*/  add_optab ; 
 int /*<<< orphan*/  ashr_optab ; 
 int /*<<< orphan*/  emit_move_insn (scalar_t__,scalar_t__) ; 
 scalar_t__ expand_binop (int,int /*<<< orphan*/ ,scalar_t__,scalar_t__,scalar_t__,int,int) ; 
 int /*<<< orphan*/  lshr_optab ; 
 scalar_t__ operand_subword (scalar_t__,int,int,int) ; 
 scalar_t__ operand_subword_force (scalar_t__,int,int) ; 
 int /*<<< orphan*/  smul_optab ; 
 int /*<<< orphan*/  smul_widen_optab ; 
 int /*<<< orphan*/  sub_optab ; 
 int /*<<< orphan*/  umul_widen_optab ; 
 int word_mode ; 

__attribute__((used)) static rtx
expand_doubleword_mult (enum machine_mode mode, rtx op0, rtx op1, rtx target,
		       bool umulp, enum optab_methods methods)
{
  int low = (WORDS_BIG_ENDIAN ? 1 : 0);
  int high = (WORDS_BIG_ENDIAN ? 0 : 1);
  rtx wordm1 = umulp ? NULL_RTX : GEN_INT (BITS_PER_WORD - 1);
  rtx product, adjust, product_high, temp;

  rtx op0_high = operand_subword_force (op0, high, mode);
  rtx op0_low = operand_subword_force (op0, low, mode);
  rtx op1_high = operand_subword_force (op1, high, mode);
  rtx op1_low = operand_subword_force (op1, low, mode);

  /* If we're using an unsigned multiply to directly compute the product
     of the low-order words of the operands and perform any required
     adjustments of the operands, we begin by trying two more multiplications
     and then computing the appropriate sum.

     We have checked above that the required addition is provided.
     Full-word addition will normally always succeed, especially if
     it is provided at all, so we don't worry about its failure.  The
     multiplication may well fail, however, so we do handle that.  */

  if (!umulp)
    {
      /* ??? This could be done with emit_store_flag where available.  */
      temp = expand_binop (word_mode, lshr_optab, op0_low, wordm1,
			   NULL_RTX, 1, methods);
      if (temp)
	op0_high = expand_binop (word_mode, add_optab, op0_high, temp,
				 NULL_RTX, 0, OPTAB_DIRECT);
      else
	{
	  temp = expand_binop (word_mode, ashr_optab, op0_low, wordm1,
			       NULL_RTX, 0, methods);
	  if (!temp)
	    return NULL_RTX;
	  op0_high = expand_binop (word_mode, sub_optab, op0_high, temp,
				   NULL_RTX, 0, OPTAB_DIRECT);
	}

      if (!op0_high)
	return NULL_RTX;
    }

  adjust = expand_binop (word_mode, smul_optab, op0_high, op1_low,
			 NULL_RTX, 0, OPTAB_DIRECT);
  if (!adjust)
    return NULL_RTX;

  /* OP0_HIGH should now be dead.  */

  if (!umulp)
    {
      /* ??? This could be done with emit_store_flag where available.  */
      temp = expand_binop (word_mode, lshr_optab, op1_low, wordm1,
			   NULL_RTX, 1, methods);
      if (temp)
	op1_high = expand_binop (word_mode, add_optab, op1_high, temp,
				 NULL_RTX, 0, OPTAB_DIRECT);
      else
	{
	  temp = expand_binop (word_mode, ashr_optab, op1_low, wordm1,
			       NULL_RTX, 0, methods);
	  if (!temp)
	    return NULL_RTX;
	  op1_high = expand_binop (word_mode, sub_optab, op1_high, temp,
				   NULL_RTX, 0, OPTAB_DIRECT);
	}

      if (!op1_high)
	return NULL_RTX;
    }

  temp = expand_binop (word_mode, smul_optab, op1_high, op0_low,
		       NULL_RTX, 0, OPTAB_DIRECT);
  if (!temp)
    return NULL_RTX;

  /* OP1_HIGH should now be dead.  */

  adjust = expand_binop (word_mode, add_optab, adjust, temp,
			 adjust, 0, OPTAB_DIRECT);

  if (target && !REG_P (target))
    target = NULL_RTX;

  if (umulp)
    product = expand_binop (mode, umul_widen_optab, op0_low, op1_low,
			    target, 1, OPTAB_DIRECT);
  else
    product = expand_binop (mode, smul_widen_optab, op0_low, op1_low,
			    target, 1, OPTAB_DIRECT);

  if (!product)
    return NULL_RTX;

  product_high = operand_subword (product, high, 1, mode);
  adjust = expand_binop (word_mode, add_optab, product_high, adjust,
			 REG_P (product_high) ? product_high : adjust,
			 0, OPTAB_DIRECT);
  emit_move_insn (product_high, adjust);
  return product;
}