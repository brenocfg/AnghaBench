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

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_REF ; 
 scalar_t__ ARRAY_TYPE ; 
 scalar_t__ IS_AGGR_TYPE (char*) ; 
 int /*<<< orphan*/  LOOKUP_NORMAL ; 
 int /*<<< orphan*/  NULL_TREE ; 
 scalar_t__ TREE_CODE (char*) ; 
 char* TREE_TYPE (scalar_t__) ; 
 int WANT_ENUM ; 
 int WANT_INT ; 
 int WANT_POINTER ; 
 scalar_t__ build_array_ref (scalar_t__,scalar_t__) ; 
 scalar_t__ build_expr_type_conversion (int,scalar_t__,int) ; 
 scalar_t__ build_min_non_dep (int /*<<< orphan*/ ,scalar_t__,scalar_t__,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ build_min_nt (int /*<<< orphan*/ ,scalar_t__,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ build_new_op (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ build_non_dependent_expr (scalar_t__) ; 
 int /*<<< orphan*/  error (char*,...) ; 
 scalar_t__ error_mark_node ; 
 scalar_t__ error_operand_p (scalar_t__) ; 
 int /*<<< orphan*/  gcc_assert (scalar_t__) ; 
 scalar_t__ non_reference (scalar_t__) ; 
 scalar_t__ processing_template_decl ; 
 scalar_t__ type_dependent_expression_p (scalar_t__) ; 

tree
grok_array_decl (tree array_expr, tree index_exp)
{
  tree type;
  tree expr;
  tree orig_array_expr = array_expr;
  tree orig_index_exp = index_exp;

  if (error_operand_p (array_expr) || error_operand_p (index_exp))
    return error_mark_node;

  if (processing_template_decl)
    {
      if (type_dependent_expression_p (array_expr)
	  || type_dependent_expression_p (index_exp))
	return build_min_nt (ARRAY_REF, array_expr, index_exp,
			     NULL_TREE, NULL_TREE);
      array_expr = build_non_dependent_expr (array_expr);
      index_exp = build_non_dependent_expr (index_exp);
    }

  type = TREE_TYPE (array_expr);
  gcc_assert (type);
  type = non_reference (type);

  /* If they have an `operator[]', use that.  */
  if (IS_AGGR_TYPE (type) || IS_AGGR_TYPE (TREE_TYPE (index_exp)))
    expr = build_new_op (ARRAY_REF, LOOKUP_NORMAL,
			 array_expr, index_exp, NULL_TREE,
			 /*overloaded_p=*/NULL);
  else
    {
      tree p1, p2, i1, i2;

      /* Otherwise, create an ARRAY_REF for a pointer or array type.
	 It is a little-known fact that, if `a' is an array and `i' is
	 an int, you can write `i[a]', which means the same thing as
	 `a[i]'.  */
      if (TREE_CODE (type) == ARRAY_TYPE)
	p1 = array_expr;
      else
	p1 = build_expr_type_conversion (WANT_POINTER, array_expr, false);

      if (TREE_CODE (TREE_TYPE (index_exp)) == ARRAY_TYPE)
	p2 = index_exp;
      else
	p2 = build_expr_type_conversion (WANT_POINTER, index_exp, false);

      i1 = build_expr_type_conversion (WANT_INT | WANT_ENUM, array_expr,
				       false);
      i2 = build_expr_type_conversion (WANT_INT | WANT_ENUM, index_exp,
				       false);

      if ((p1 && i2) && (i1 && p2))
	error ("ambiguous conversion for array subscript");

      if (p1 && i2)
	array_expr = p1, index_exp = i2;
      else if (i1 && p2)
	array_expr = p2, index_exp = i1;
      else
	{
	  error ("invalid types %<%T[%T]%> for array subscript",
		 type, TREE_TYPE (index_exp));
	  return error_mark_node;
	}

      if (array_expr == error_mark_node || index_exp == error_mark_node)
	error ("ambiguous conversion for array subscript");

      expr = build_array_ref (array_expr, index_exp);
    }
  if (processing_template_decl && expr != error_mark_node)
    return build_min_non_dep (ARRAY_REF, expr, orig_array_expr, orig_index_exp,
			      NULL_TREE, NULL_TREE);
  return expr;
}