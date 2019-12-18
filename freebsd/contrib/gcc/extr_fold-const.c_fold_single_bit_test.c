#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ tree ;
typedef  enum tree_code { ____Placeholder_tree_code } tree_code ;
typedef  enum machine_mode { ____Placeholder_machine_mode } machine_mode ;
struct TYPE_3__ {scalar_t__ (* type_for_mode ) (int,int) ;} ;
struct TYPE_4__ {TYPE_1__ types; } ;

/* Variables and functions */
 scalar_t__ BIT_AND_EXPR ; 
 int /*<<< orphan*/  BIT_XOR_EXPR ; 
 int EQ_EXPR ; 
 scalar_t__ INTEGER_CST ; 
 scalar_t__ LOAD_EXTEND_OP (int) ; 
 int NE_EXPR ; 
 scalar_t__ NULL_TREE ; 
 scalar_t__ RSHIFT_EXPR ; 
 scalar_t__ SIGN_EXTEND ; 
 scalar_t__ TREE_CODE (scalar_t__) ; 
 scalar_t__ TREE_INT_CST_HIGH (scalar_t__) ; 
 scalar_t__ TREE_INT_CST_LOW (scalar_t__) ; 
 scalar_t__ TREE_OPERAND (scalar_t__,int) ; 
 scalar_t__ TREE_TYPE (scalar_t__) ; 
 int TYPE_MODE (scalar_t__) ; 
 int TYPE_PRECISION (scalar_t__) ; 
 scalar_t__ build2 (scalar_t__,scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ compare_tree_int (scalar_t__,int) ; 
 int /*<<< orphan*/  flag_syntax_only ; 
 scalar_t__ fold_build2 (int /*<<< orphan*/ ,scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ fold_convert (scalar_t__,scalar_t__) ; 
 scalar_t__ fold_single_bit_test_into_sign_test (int,scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  integer_one_node ; 
 scalar_t__ integer_pow2p (scalar_t__) ; 
 scalar_t__ integer_zerop (scalar_t__) ; 
 TYPE_2__ lang_hooks ; 
 int /*<<< orphan*/  size_int (int) ; 
 scalar_t__ stub1 (int,int) ; 
 scalar_t__ stub2 (int,int) ; 
 int tree_log2 (scalar_t__) ; 

tree
fold_single_bit_test (enum tree_code code, tree arg0, tree arg1,
		      tree result_type)
{
  /* If this is testing a single bit, we can optimize the test.  */
  if ((code == NE_EXPR || code == EQ_EXPR)
      && TREE_CODE (arg0) == BIT_AND_EXPR && integer_zerop (arg1)
      && integer_pow2p (TREE_OPERAND (arg0, 1)))
    {
      tree inner = TREE_OPERAND (arg0, 0);
      tree type = TREE_TYPE (arg0);
      int bitnum = tree_log2 (TREE_OPERAND (arg0, 1));
      enum machine_mode operand_mode = TYPE_MODE (type);
      int ops_unsigned;
      tree signed_type, unsigned_type, intermediate_type;
      tree tem;

      /* First, see if we can fold the single bit test into a sign-bit
	 test.  */
      tem = fold_single_bit_test_into_sign_test (code, arg0, arg1,
						 result_type);
      if (tem)
	return tem;

      /* Otherwise we have (A & C) != 0 where C is a single bit,
	 convert that into ((A >> C2) & 1).  Where C2 = log2(C).
	 Similarly for (A & C) == 0.  */

      /* If INNER is a right shift of a constant and it plus BITNUM does
	 not overflow, adjust BITNUM and INNER.  */
      if (TREE_CODE (inner) == RSHIFT_EXPR
	  && TREE_CODE (TREE_OPERAND (inner, 1)) == INTEGER_CST
	  && TREE_INT_CST_HIGH (TREE_OPERAND (inner, 1)) == 0
	  && bitnum < TYPE_PRECISION (type)
	  && 0 > compare_tree_int (TREE_OPERAND (inner, 1),
				   bitnum - TYPE_PRECISION (type)))
	{
	  bitnum += TREE_INT_CST_LOW (TREE_OPERAND (inner, 1));
	  inner = TREE_OPERAND (inner, 0);
	}

      /* If we are going to be able to omit the AND below, we must do our
	 operations as unsigned.  If we must use the AND, we have a choice.
	 Normally unsigned is faster, but for some machines signed is.  */
#ifdef LOAD_EXTEND_OP
      ops_unsigned = (LOAD_EXTEND_OP (operand_mode) == SIGN_EXTEND 
		      && !flag_syntax_only) ? 0 : 1;
#else
      ops_unsigned = 1;
#endif

      signed_type = lang_hooks.types.type_for_mode (operand_mode, 0);
      unsigned_type = lang_hooks.types.type_for_mode (operand_mode, 1);
      intermediate_type = ops_unsigned ? unsigned_type : signed_type;
      inner = fold_convert (intermediate_type, inner);

      if (bitnum != 0)
	inner = build2 (RSHIFT_EXPR, intermediate_type,
			inner, size_int (bitnum));

      if (code == EQ_EXPR)
	inner = fold_build2 (BIT_XOR_EXPR, intermediate_type,
			     inner, integer_one_node);

      /* Put the AND last so it can combine with more things.  */
      inner = build2 (BIT_AND_EXPR, intermediate_type,
		      inner, integer_one_node);

      /* Make sure to return the proper type.  */
      inner = fold_convert (result_type, inner);

      return inner;
    }
  return NULL_TREE;
}