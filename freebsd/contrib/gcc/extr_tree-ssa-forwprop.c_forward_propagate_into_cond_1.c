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
typedef  enum tree_code { ____Placeholder_tree_code } tree_code ;

/* Variables and functions */
 scalar_t__ BOOLEAN_TYPE ; 
 scalar_t__ COMPARISON_CLASS_P (int /*<<< orphan*/ ) ; 
 scalar_t__ CONSTANT_CLASS_P (int /*<<< orphan*/ ) ; 
 scalar_t__ CONVERT_EXPR ; 
 int EQ_EXPR ; 
 scalar_t__ INTEGRAL_TYPE_P (int /*<<< orphan*/ ) ; 
 scalar_t__ MINUS_EXPR ; 
 scalar_t__ MODIFY_EXPR ; 
 int NE_EXPR ; 
 scalar_t__ NOP_EXPR ; 
 int /*<<< orphan*/  NULL_TREE ; 
 scalar_t__ PLUS_EXPR ; 
 int SSA_NAME ; 
 int /*<<< orphan*/  SSA_NAME_DEF_STMT (int /*<<< orphan*/ ) ; 
 scalar_t__ SSA_NAME_OCCURS_IN_ABNORMAL_PHI (int /*<<< orphan*/ ) ; 
 int TREE_CODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TREE_OPERAND (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  TREE_TYPE (int /*<<< orphan*/ ) ; 
 scalar_t__ TRUTH_NOT_EXPR ; 
 int /*<<< orphan*/  boolean_type_node ; 
 int /*<<< orphan*/  build2 (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fold_convert (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ has_single_use (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  int_const_binop (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ integer_onep (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  integer_zero_node ; 
 scalar_t__ integer_zerop (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  invert_truthvalue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  is_gimple_min_invariant (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  is_gimple_val (int /*<<< orphan*/ ) ; 
 scalar_t__ ssa_name_defined_by_comparison_p (int /*<<< orphan*/ ) ; 

__attribute__((used)) static tree
forward_propagate_into_cond_1 (tree cond, tree *test_var_p)
{
  tree new_cond = NULL_TREE;
  enum tree_code cond_code = TREE_CODE (cond);
  tree test_var = NULL_TREE;
  tree def;
  tree def_rhs;

  /* If the condition is not a lone variable or an equality test of an
     SSA_NAME against an integral constant, then we do not have an
     optimizable case.

     Note these conditions also ensure the COND_EXPR has no
     virtual operands or other side effects.  */
  if (cond_code != SSA_NAME
      && !((cond_code == EQ_EXPR || cond_code == NE_EXPR)
	   && TREE_CODE (TREE_OPERAND (cond, 0)) == SSA_NAME
	   && CONSTANT_CLASS_P (TREE_OPERAND (cond, 1))
	   && INTEGRAL_TYPE_P (TREE_TYPE (TREE_OPERAND (cond, 1)))))
    return NULL_TREE;

  /* Extract the single variable used in the test into TEST_VAR.  */
  if (cond_code == SSA_NAME)
    test_var = cond;
  else
    test_var = TREE_OPERAND (cond, 0);

  /* Now get the defining statement for TEST_VAR.  Skip this case if
     it's not defined by some MODIFY_EXPR.  */
  def = SSA_NAME_DEF_STMT (test_var);
  if (TREE_CODE (def) != MODIFY_EXPR)
    return NULL_TREE;

  def_rhs = TREE_OPERAND (def, 1);

  /* If TEST_VAR is set by adding or subtracting a constant
     from an SSA_NAME, then it is interesting to us as we
     can adjust the constant in the conditional and thus
     eliminate the arithmetic operation.  */
  if (TREE_CODE (def_rhs) == PLUS_EXPR
      || TREE_CODE (def_rhs) == MINUS_EXPR)
    {
      tree op0 = TREE_OPERAND (def_rhs, 0);
      tree op1 = TREE_OPERAND (def_rhs, 1);

      /* The first operand must be an SSA_NAME and the second
	 operand must be a constant.  */
      if (TREE_CODE (op0) != SSA_NAME
	  || !CONSTANT_CLASS_P (op1)
	  || !INTEGRAL_TYPE_P (TREE_TYPE (op1)))
	return NULL_TREE;

      /* Don't propagate if the first operand occurs in
	 an abnormal PHI.  */
      if (SSA_NAME_OCCURS_IN_ABNORMAL_PHI (op0))
	return NULL_TREE;

      if (has_single_use (test_var))
	{
	  enum tree_code new_code;
	  tree t;

	  /* If the variable was defined via X + C, then we must
	     subtract C from the constant in the conditional.
	     Otherwise we add C to the constant in the
	     conditional.  The result must fold into a valid
	     gimple operand to be optimizable.  */
	  new_code = (TREE_CODE (def_rhs) == PLUS_EXPR
		      ? MINUS_EXPR : PLUS_EXPR);
	  t = int_const_binop (new_code, TREE_OPERAND (cond, 1), op1, 0);
	  if (!is_gimple_val (t))
	    return NULL_TREE;

	  new_cond = build2 (cond_code, boolean_type_node, op0, t);
	}
    }

  /* These cases require comparisons of a naked SSA_NAME or
     comparison of an SSA_NAME against zero or one.  */
  else if (TREE_CODE (cond) == SSA_NAME
	   || integer_zerop (TREE_OPERAND (cond, 1))
	   || integer_onep (TREE_OPERAND (cond, 1)))
    {
      /* If TEST_VAR is set from a relational operation
	 between two SSA_NAMEs or a combination of an SSA_NAME
	 and a constant, then it is interesting.  */
      if (COMPARISON_CLASS_P (def_rhs))
	{
	  tree op0 = TREE_OPERAND (def_rhs, 0);
	  tree op1 = TREE_OPERAND (def_rhs, 1);

	  /* Both operands of DEF_RHS must be SSA_NAMEs or
	     constants.  */
	  if ((TREE_CODE (op0) != SSA_NAME
	       && !is_gimple_min_invariant (op0))
	      || (TREE_CODE (op1) != SSA_NAME
		  && !is_gimple_min_invariant (op1)))
	    return NULL_TREE;

	  /* Don't propagate if the first operand occurs in
	     an abnormal PHI.  */
	  if (TREE_CODE (op0) == SSA_NAME
	      && SSA_NAME_OCCURS_IN_ABNORMAL_PHI (op0))
	    return NULL_TREE;

	  /* Don't propagate if the second operand occurs in
	     an abnormal PHI.  */
	  if (TREE_CODE (op1) == SSA_NAME
	      && SSA_NAME_OCCURS_IN_ABNORMAL_PHI (op1))
	    return NULL_TREE;

	  if (has_single_use (test_var))
	    {
	      /* TEST_VAR was set from a relational operator.  */
	      new_cond = build2 (TREE_CODE (def_rhs),
				 boolean_type_node, op0, op1);

	      /* Invert the conditional if necessary.  */
	      if ((cond_code == EQ_EXPR
		   && integer_zerop (TREE_OPERAND (cond, 1)))
		  || (cond_code == NE_EXPR
		      && integer_onep (TREE_OPERAND (cond, 1))))
		{
		  new_cond = invert_truthvalue (new_cond);

		  /* If we did not get a simple relational
		     expression or bare SSA_NAME, then we can
		     not optimize this case.  */
		  if (!COMPARISON_CLASS_P (new_cond)
		      && TREE_CODE (new_cond) != SSA_NAME)
		    new_cond = NULL_TREE;
		}
	    }
	}

      /* If TEST_VAR is set from a TRUTH_NOT_EXPR, then it
	 is interesting.  */
      else if (TREE_CODE (def_rhs) == TRUTH_NOT_EXPR)
	{
	  enum tree_code new_code;

	  def_rhs = TREE_OPERAND (def_rhs, 0);

	  /* DEF_RHS must be an SSA_NAME or constant.  */
	  if (TREE_CODE (def_rhs) != SSA_NAME
	      && !is_gimple_min_invariant (def_rhs))
	    return NULL_TREE;

	  /* Don't propagate if the operand occurs in
	     an abnormal PHI.  */
	  if (TREE_CODE (def_rhs) == SSA_NAME
	      && SSA_NAME_OCCURS_IN_ABNORMAL_PHI (def_rhs))
	    return NULL_TREE;

	  if (cond_code == SSA_NAME
	      || (cond_code == NE_EXPR
		  && integer_zerop (TREE_OPERAND (cond, 1)))
	      || (cond_code == EQ_EXPR
		  && integer_onep (TREE_OPERAND (cond, 1))))
	    new_code = EQ_EXPR;
	  else
	    new_code = NE_EXPR;

	  new_cond = build2 (new_code, boolean_type_node, def_rhs,
			     fold_convert (TREE_TYPE (def_rhs),
					   integer_zero_node));
	}

      /* If TEST_VAR was set from a cast of an integer type
	 to a boolean type or a cast of a boolean to an
	 integral, then it is interesting.  */
      else if (TREE_CODE (def_rhs) == NOP_EXPR
	       || TREE_CODE (def_rhs) == CONVERT_EXPR)
	{
	  tree outer_type;
	  tree inner_type;

	  outer_type = TREE_TYPE (def_rhs);
	  inner_type = TREE_TYPE (TREE_OPERAND (def_rhs, 0));

	  if ((TREE_CODE (outer_type) == BOOLEAN_TYPE
	       && INTEGRAL_TYPE_P (inner_type))
	      || (TREE_CODE (inner_type) == BOOLEAN_TYPE
		  && INTEGRAL_TYPE_P (outer_type)))
	    ;
	  else if (INTEGRAL_TYPE_P (outer_type)
		   && INTEGRAL_TYPE_P (inner_type)
		   && TREE_CODE (TREE_OPERAND (def_rhs, 0)) == SSA_NAME
		   && ssa_name_defined_by_comparison_p (TREE_OPERAND (def_rhs,
								      0)))
	    ;
	  else
	    return NULL_TREE;

	  /* Don't propagate if the operand occurs in
	     an abnormal PHI.  */
	  if (TREE_CODE (TREE_OPERAND (def_rhs, 0)) == SSA_NAME
	      && SSA_NAME_OCCURS_IN_ABNORMAL_PHI (TREE_OPERAND
						  (def_rhs, 0)))
	    return NULL_TREE;

	  if (has_single_use (test_var))
	    {
	      enum tree_code new_code;
	      tree new_arg;

	      if (cond_code == SSA_NAME
		  || (cond_code == NE_EXPR
		      && integer_zerop (TREE_OPERAND (cond, 1)))
		  || (cond_code == EQ_EXPR
		      && integer_onep (TREE_OPERAND (cond, 1))))
		new_code = NE_EXPR;
	      else
		new_code = EQ_EXPR;

	      new_arg = TREE_OPERAND (def_rhs, 0);
	      new_cond = build2 (new_code, boolean_type_node, new_arg,
				 fold_convert (TREE_TYPE (new_arg),
					       integer_zero_node));
	    }
	}
    }

  *test_var_p = test_var;
  return new_cond;
}