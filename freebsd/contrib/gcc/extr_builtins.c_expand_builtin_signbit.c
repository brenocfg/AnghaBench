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
typedef  int /*<<< orphan*/  tree ;
struct real_format {int signbit_ro; scalar_t__ has_signed_zero; } ;
typedef  int /*<<< orphan*/  rtx ;
typedef  enum machine_mode { ____Placeholder_machine_mode } machine_mode ;
typedef  int HOST_WIDE_INT ;

/* Variables and functions */
 int BITS_PER_WORD ; 
 int BLKmode ; 
 int /*<<< orphan*/  EXPAND_NORMAL ; 
 scalar_t__ FLOAT_WORDS_BIG_ENDIAN ; 
 int GET_MODE_BITSIZE (int) ; 
 scalar_t__ GET_MODE_SIZE (int) ; 
 scalar_t__ HONOR_SIGNED_ZEROS (int) ; 
 int HOST_BITS_PER_WIDE_INT ; 
 int /*<<< orphan*/  LT_EXPR ; 
 int /*<<< orphan*/  NULL_RTX ; 
 int /*<<< orphan*/  NULL_TREE ; 
 int /*<<< orphan*/  OPTAB_LIB_WIDEN ; 
 struct real_format* REAL_MODE_FORMAT (int) ; 
 int /*<<< orphan*/  REAL_TYPE ; 
 int /*<<< orphan*/  RSHIFT_EXPR ; 
 int /*<<< orphan*/  TREE_OPERAND (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  TREE_TYPE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TREE_VALUE (int /*<<< orphan*/ ) ; 
 int TYPE_MODE (int /*<<< orphan*/ ) ; 
 scalar_t__ UNITS_PER_WORD ; 
 int /*<<< orphan*/  VOID_TYPE ; 
 int /*<<< orphan*/  VOIDmode ; 
 int /*<<< orphan*/  and_optab ; 
 int /*<<< orphan*/  build_int_cst (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  build_real (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  const1_rtx ; 
 int /*<<< orphan*/  dconst0 ; 
 int /*<<< orphan*/  expand_binop (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  expand_expr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  expand_normal (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  expand_shift (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  fold_build2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  force_reg (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_lowpart (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  immed_double_const (int,int,int) ; 
 int int_mode_for_mode (int) ; 
 int /*<<< orphan*/  operand_subword_force (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  validate_arglist (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int word_mode ; 

__attribute__((used)) static rtx
expand_builtin_signbit (tree exp, rtx target)
{
  const struct real_format *fmt;
  enum machine_mode fmode, imode, rmode;
  HOST_WIDE_INT hi, lo;
  tree arg, arglist;
  int word, bitpos;
  rtx temp;

  arglist = TREE_OPERAND (exp, 1);
  if (!validate_arglist (arglist, REAL_TYPE, VOID_TYPE))
    return 0;

  arg = TREE_VALUE (arglist);
  fmode = TYPE_MODE (TREE_TYPE (arg));
  rmode = TYPE_MODE (TREE_TYPE (exp));
  fmt = REAL_MODE_FORMAT (fmode);

  /* For floating point formats without a sign bit, implement signbit
     as "ARG < 0.0".  */
  bitpos = fmt->signbit_ro;
  if (bitpos < 0)
  {
    /* But we can't do this if the format supports signed zero.  */
    if (fmt->has_signed_zero && HONOR_SIGNED_ZEROS (fmode))
      return 0;

    arg = fold_build2 (LT_EXPR, TREE_TYPE (exp), arg,
		       build_real (TREE_TYPE (arg), dconst0));
    return expand_expr (arg, target, VOIDmode, EXPAND_NORMAL);
  }

  temp = expand_normal (arg);
  if (GET_MODE_SIZE (fmode) <= UNITS_PER_WORD)
    {
      imode = int_mode_for_mode (fmode);
      if (imode == BLKmode)
	return 0;
      temp = gen_lowpart (imode, temp);
    }
  else
    {
      imode = word_mode;
      /* Handle targets with different FP word orders.  */
      if (FLOAT_WORDS_BIG_ENDIAN)
	word = (GET_MODE_BITSIZE (fmode) - bitpos) / BITS_PER_WORD;
      else
	word = bitpos / BITS_PER_WORD;
      temp = operand_subword_force (temp, word, fmode);
      bitpos = bitpos % BITS_PER_WORD;
    }

  /* Force the intermediate word_mode (or narrower) result into a
     register.  This avoids attempting to create paradoxical SUBREGs
     of floating point modes below.  */
  temp = force_reg (imode, temp);

  /* If the bitpos is within the "result mode" lowpart, the operation
     can be implement with a single bitwise AND.  Otherwise, we need
     a right shift and an AND.  */

  if (bitpos < GET_MODE_BITSIZE (rmode))
    {
      if (bitpos < HOST_BITS_PER_WIDE_INT)
	{
	  hi = 0;
	  lo = (HOST_WIDE_INT) 1 << bitpos;
	}
      else
	{
	  hi = (HOST_WIDE_INT) 1 << (bitpos - HOST_BITS_PER_WIDE_INT);
	  lo = 0;
	}

      if (imode != rmode)
	temp = gen_lowpart (rmode, temp);
      temp = expand_binop (rmode, and_optab, temp,
			   immed_double_const (lo, hi, rmode),
			   NULL_RTX, 1, OPTAB_LIB_WIDEN);
    }
  else
    {
      /* Perform a logical right shift to place the signbit in the least
	 significant bit, then truncate the result to the desired mode
	 and mask just this bit.  */
      temp = expand_shift (RSHIFT_EXPR, imode, temp,
			   build_int_cst (NULL_TREE, bitpos), NULL_RTX, 1);
      temp = gen_lowpart (rmode, temp);
      temp = expand_binop (rmode, and_optab, temp, const1_rtx,
			   NULL_RTX, 1, OPTAB_LIB_WIDEN);
    }

  return temp;
}