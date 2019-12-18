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
typedef  scalar_t__ tree ;
typedef  enum tree_code_class { ____Placeholder_tree_code_class } tree_code_class ;
typedef  enum tree_code { ____Placeholder_tree_code } tree_code ;

/* Variables and functions */
 int COMPOUND_EXPR ; 
 int COND_EXPR ; 
 int SAVE_EXPR ; 
 int TREE_CODE (scalar_t__) ; 
 int TREE_CODE_CLASS (int) ; 
 scalar_t__ TREE_OPERAND (scalar_t__,int) ; 
 int /*<<< orphan*/  TREE_SIDE_EFFECTS (scalar_t__) ; 
 int TRUTH_ANDIF_EXPR ; 
 int TRUTH_NOT_EXPR ; 
 int TRUTH_ORIF_EXPR ; 
 int /*<<< orphan*/  operand_equal_p (scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
#define  tcc_binary 132 
#define  tcc_comparison 131 
#define  tcc_constant 130 
#define  tcc_expression 129 
#define  tcc_unary 128 

__attribute__((used)) static int
twoval_comparison_p (tree arg, tree *cval1, tree *cval2, int *save_p)
{
  enum tree_code code = TREE_CODE (arg);
  enum tree_code_class class = TREE_CODE_CLASS (code);

  /* We can handle some of the tcc_expression cases here.  */
  if (class == tcc_expression && code == TRUTH_NOT_EXPR)
    class = tcc_unary;
  else if (class == tcc_expression
	   && (code == TRUTH_ANDIF_EXPR || code == TRUTH_ORIF_EXPR
	       || code == COMPOUND_EXPR))
    class = tcc_binary;

  else if (class == tcc_expression && code == SAVE_EXPR
	   && ! TREE_SIDE_EFFECTS (TREE_OPERAND (arg, 0)))
    {
      /* If we've already found a CVAL1 or CVAL2, this expression is
	 two complex to handle.  */
      if (*cval1 || *cval2)
	return 0;

      class = tcc_unary;
      *save_p = 1;
    }

  switch (class)
    {
    case tcc_unary:
      return twoval_comparison_p (TREE_OPERAND (arg, 0), cval1, cval2, save_p);

    case tcc_binary:
      return (twoval_comparison_p (TREE_OPERAND (arg, 0), cval1, cval2, save_p)
	      && twoval_comparison_p (TREE_OPERAND (arg, 1),
				      cval1, cval2, save_p));

    case tcc_constant:
      return 1;

    case tcc_expression:
      if (code == COND_EXPR)
	return (twoval_comparison_p (TREE_OPERAND (arg, 0),
				     cval1, cval2, save_p)
		&& twoval_comparison_p (TREE_OPERAND (arg, 1),
					cval1, cval2, save_p)
		&& twoval_comparison_p (TREE_OPERAND (arg, 2),
					cval1, cval2, save_p));
      return 0;

    case tcc_comparison:
      /* First see if we can handle the first operand, then the second.  For
	 the second operand, we know *CVAL1 can't be zero.  It must be that
	 one side of the comparison is each of the values; test for the
	 case where this isn't true by failing if the two operands
	 are the same.  */

      if (operand_equal_p (TREE_OPERAND (arg, 0),
			   TREE_OPERAND (arg, 1), 0))
	return 0;

      if (*cval1 == 0)
	*cval1 = TREE_OPERAND (arg, 0);
      else if (operand_equal_p (*cval1, TREE_OPERAND (arg, 0), 0))
	;
      else if (*cval2 == 0)
	*cval2 = TREE_OPERAND (arg, 0);
      else if (operand_equal_p (*cval2, TREE_OPERAND (arg, 0), 0))
	;
      else
	return 0;

      if (operand_equal_p (*cval1, TREE_OPERAND (arg, 1), 0))
	;
      else if (*cval2 == 0)
	*cval2 = TREE_OPERAND (arg, 1);
      else if (operand_equal_p (*cval2, TREE_OPERAND (arg, 1), 0))
	;
      else
	return 0;

      return 1;

    default:
      return 0;
    }
}