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
typedef  enum tree_code { ____Placeholder_tree_code } tree_code ;

/* Variables and functions */
 int /*<<< orphan*/  FLOAT_TYPE_P (int /*<<< orphan*/ ) ; 
 scalar_t__ INTEGER_CST ; 
 scalar_t__ MINUS_EXPR ; 
 int PLUS_EXPR ; 
 scalar_t__ REAL_CST ; 
 int /*<<< orphan*/  STRIP_SIGN_NOPS (scalar_t__) ; 
 scalar_t__ TREE_CODE (scalar_t__) ; 
 scalar_t__ TREE_CONSTANT (scalar_t__) ; 
 scalar_t__ TREE_OPERAND (scalar_t__,int) ; 
 int /*<<< orphan*/  TREE_TYPE (scalar_t__) ; 
 scalar_t__ negate_expr (scalar_t__) ; 

__attribute__((used)) static tree
split_tree (tree in, enum tree_code code, tree *conp, tree *litp,
	    tree *minus_litp, int negate_p)
{
  tree var = 0;

  *conp = 0;
  *litp = 0;
  *minus_litp = 0;

  /* Strip any conversions that don't change the machine mode or signedness.  */
  STRIP_SIGN_NOPS (in);

  if (TREE_CODE (in) == INTEGER_CST || TREE_CODE (in) == REAL_CST)
    *litp = in;
  else if (TREE_CODE (in) == code
	   || (! FLOAT_TYPE_P (TREE_TYPE (in))
	       /* We can associate addition and subtraction together (even
		  though the C standard doesn't say so) for integers because
		  the value is not affected.  For reals, the value might be
		  affected, so we can't.  */
	       && ((code == PLUS_EXPR && TREE_CODE (in) == MINUS_EXPR)
		   || (code == MINUS_EXPR && TREE_CODE (in) == PLUS_EXPR))))
    {
      tree op0 = TREE_OPERAND (in, 0);
      tree op1 = TREE_OPERAND (in, 1);
      int neg1_p = TREE_CODE (in) == MINUS_EXPR;
      int neg_litp_p = 0, neg_conp_p = 0, neg_var_p = 0;

      /* First see if either of the operands is a literal, then a constant.  */
      if (TREE_CODE (op0) == INTEGER_CST || TREE_CODE (op0) == REAL_CST)
	*litp = op0, op0 = 0;
      else if (TREE_CODE (op1) == INTEGER_CST || TREE_CODE (op1) == REAL_CST)
	*litp = op1, neg_litp_p = neg1_p, op1 = 0;

      if (op0 != 0 && TREE_CONSTANT (op0))
	*conp = op0, op0 = 0;
      else if (op1 != 0 && TREE_CONSTANT (op1))
	*conp = op1, neg_conp_p = neg1_p, op1 = 0;

      /* If we haven't dealt with either operand, this is not a case we can
	 decompose.  Otherwise, VAR is either of the ones remaining, if any.  */
      if (op0 != 0 && op1 != 0)
	var = in;
      else if (op0 != 0)
	var = op0;
      else
	var = op1, neg_var_p = neg1_p;

      /* Now do any needed negations.  */
      if (neg_litp_p)
	*minus_litp = *litp, *litp = 0;
      if (neg_conp_p)
	*conp = negate_expr (*conp);
      if (neg_var_p)
	var = negate_expr (var);
    }
  else if (TREE_CONSTANT (in))
    *conp = in;
  else
    var = in;

  if (negate_p)
    {
      if (*litp)
	*minus_litp = *litp, *litp = 0;
      else if (*minus_litp)
	*litp = *minus_litp, *minus_litp = 0;
      *conp = negate_expr (*conp);
      var = negate_expr (var);
    }

  return var;
}