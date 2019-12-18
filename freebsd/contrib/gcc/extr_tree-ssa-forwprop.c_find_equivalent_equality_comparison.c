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
typedef  int /*<<< orphan*/ * tree ;

/* Variables and functions */
 scalar_t__ CONVERT_EXPR ; 
 scalar_t__ FUNCTION_TYPE ; 
 scalar_t__ MODIFY_EXPR ; 
 scalar_t__ NOP_EXPR ; 
 scalar_t__ POINTER_TYPE_P (int /*<<< orphan*/ *) ; 
 scalar_t__ SSA_NAME ; 
 int /*<<< orphan*/ * SSA_NAME_DEF_STMT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  STRIP_USELESS_TYPE_CONVERSION (int /*<<< orphan*/ *) ; 
 scalar_t__ TREE_CODE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * TREE_OPERAND (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * TREE_TYPE (int /*<<< orphan*/ *) ; 
 scalar_t__ TYPE_PRECISION (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * build2 (scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fold_build1 (scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ is_gimple_val (int /*<<< orphan*/ *) ; 
 scalar_t__ tree_int_cst_equal (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static tree
find_equivalent_equality_comparison (tree cond)
{
  tree op0 = TREE_OPERAND (cond, 0);
  tree op1 = TREE_OPERAND (cond, 1);
  tree def_stmt = SSA_NAME_DEF_STMT (op0);

  while (def_stmt
	 && TREE_CODE (def_stmt) == MODIFY_EXPR
	 && TREE_CODE (TREE_OPERAND (def_stmt, 1)) == SSA_NAME)
    def_stmt = SSA_NAME_DEF_STMT (TREE_OPERAND (def_stmt, 1));

  /* OP0 might have been a parameter, so first make sure it
     was defined by a MODIFY_EXPR.  */
  if (def_stmt && TREE_CODE (def_stmt) == MODIFY_EXPR)
    {
      tree def_rhs = TREE_OPERAND (def_stmt, 1);

      /* If either operand to the comparison is a pointer to
	 a function, then we can not apply this optimization
	 as some targets require function pointers to be
	 canonicalized and in this case this optimization would
	 eliminate a necessary canonicalization.  */
      if ((POINTER_TYPE_P (TREE_TYPE (op0))
	   && TREE_CODE (TREE_TYPE (TREE_TYPE (op0))) == FUNCTION_TYPE)
	  || (POINTER_TYPE_P (TREE_TYPE (op1))
	      && TREE_CODE (TREE_TYPE (TREE_TYPE (op1))) == FUNCTION_TYPE))
	return NULL;
	      
      /* Now make sure the RHS of the MODIFY_EXPR is a typecast.  */
      if ((TREE_CODE (def_rhs) == NOP_EXPR
	   || TREE_CODE (def_rhs) == CONVERT_EXPR)
	  && TREE_CODE (TREE_OPERAND (def_rhs, 0)) == SSA_NAME)
	{
	  tree def_rhs_inner = TREE_OPERAND (def_rhs, 0);
	  tree def_rhs_inner_type = TREE_TYPE (def_rhs_inner);
	  tree new;

	  if (TYPE_PRECISION (def_rhs_inner_type)
	      > TYPE_PRECISION (TREE_TYPE (def_rhs)))
	    return NULL;

	  /* If the inner type of the conversion is a pointer to
	     a function, then we can not apply this optimization
	     as some targets require function pointers to be
	     canonicalized.  This optimization would result in
	     canonicalization of the pointer when it was not originally
	     needed/intended.  */
	  if (POINTER_TYPE_P (def_rhs_inner_type)
	      && TREE_CODE (TREE_TYPE (def_rhs_inner_type)) == FUNCTION_TYPE)
	    return NULL;

	  /* What we want to prove is that if we convert OP1 to
	     the type of the object inside the NOP_EXPR that the
	     result is still equivalent to SRC. 

	     If that is true, the build and return new equivalent
	     condition which uses the source of the typecast and the
	     new constant (which has only changed its type).  */
	  new = fold_build1 (TREE_CODE (def_rhs), def_rhs_inner_type, op1);
	  STRIP_USELESS_TYPE_CONVERSION (new);
	  if (is_gimple_val (new) && tree_int_cst_equal (new, op1))
	    return build2 (TREE_CODE (cond), TREE_TYPE (cond),
			   def_rhs_inner, new);
	}
    }
  return NULL;
}