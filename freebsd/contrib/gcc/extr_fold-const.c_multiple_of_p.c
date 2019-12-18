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

/* Variables and functions */
#define  BIT_AND_EXPR 135 
#define  INTEGER_CST 134 
 int const INTEGER_TYPE ; 
#define  LSHIFT_EXPR 133 
#define  MINUS_EXPR 132 
#define  MULT_EXPR 131 
#define  NOP_EXPR 130 
#define  PLUS_EXPR 129 
#define  SAVE_EXPR 128 
 int const TREE_CODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TREE_INT_CST_HIGH (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TREE_INT_CST_LOW (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TREE_OPERAND (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  TREE_OVERFLOW (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TREE_TYPE (int /*<<< orphan*/ ) ; 
 int const TRUNC_MOD_EXPR ; 
 int /*<<< orphan*/  TYPE_PRECISION (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TYPE_UNSIGNED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  const_binop (int const,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fold_convert (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  integer_pow2p (int /*<<< orphan*/ ) ; 
 int integer_zerop (int /*<<< orphan*/ ) ; 
 scalar_t__ operand_equal_p (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  size_one_node ; 
 int /*<<< orphan*/  tree_int_cst_sgn (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
multiple_of_p (tree type, tree top, tree bottom)
{
  if (operand_equal_p (top, bottom, 0))
    return 1;

  if (TREE_CODE (type) != INTEGER_TYPE)
    return 0;

  switch (TREE_CODE (top))
    {
    case BIT_AND_EXPR:
      /* Bitwise and provides a power of two multiple.  If the mask is
	 a multiple of BOTTOM then TOP is a multiple of BOTTOM.  */
      if (!integer_pow2p (bottom))
	return 0;
      /* FALLTHRU */

    case MULT_EXPR:
      return (multiple_of_p (type, TREE_OPERAND (top, 0), bottom)
	      || multiple_of_p (type, TREE_OPERAND (top, 1), bottom));

    case PLUS_EXPR:
    case MINUS_EXPR:
      return (multiple_of_p (type, TREE_OPERAND (top, 0), bottom)
	      && multiple_of_p (type, TREE_OPERAND (top, 1), bottom));

    case LSHIFT_EXPR:
      if (TREE_CODE (TREE_OPERAND (top, 1)) == INTEGER_CST)
	{
	  tree op1, t1;

	  op1 = TREE_OPERAND (top, 1);
	  /* const_binop may not detect overflow correctly,
	     so check for it explicitly here.  */
	  if (TYPE_PRECISION (TREE_TYPE (size_one_node))
	      > TREE_INT_CST_LOW (op1)
	      && TREE_INT_CST_HIGH (op1) == 0
	      && 0 != (t1 = fold_convert (type,
					  const_binop (LSHIFT_EXPR,
						       size_one_node,
						       op1, 0)))
	      && ! TREE_OVERFLOW (t1))
	    return multiple_of_p (type, t1, bottom);
	}
      return 0;

    case NOP_EXPR:
      /* Can't handle conversions from non-integral or wider integral type.  */
      if ((TREE_CODE (TREE_TYPE (TREE_OPERAND (top, 0))) != INTEGER_TYPE)
	  || (TYPE_PRECISION (type)
	      < TYPE_PRECISION (TREE_TYPE (TREE_OPERAND (top, 0)))))
	return 0;

      /* .. fall through ...  */

    case SAVE_EXPR:
      return multiple_of_p (type, TREE_OPERAND (top, 0), bottom);

    case INTEGER_CST:
      if (TREE_CODE (bottom) != INTEGER_CST
	  || (TYPE_UNSIGNED (type)
	      && (tree_int_cst_sgn (top) < 0
		  || tree_int_cst_sgn (bottom) < 0)))
	return 0;
      return integer_zerop (const_binop (TRUNC_MOD_EXPR,
					 top, bottom, 0));

    default:
      return 0;
    }
}