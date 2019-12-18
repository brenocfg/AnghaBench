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
 scalar_t__ COMPOUND_EXPR ; 
 scalar_t__ CONVERT_EXPR ; 
 scalar_t__ NOP_EXPR ; 
 scalar_t__ TREE_CODE (scalar_t__) ; 
 scalar_t__ TREE_OPERAND (scalar_t__,int) ; 
 int /*<<< orphan*/  TREE_SIDE_EFFECTS (scalar_t__) ; 
 int /*<<< orphan*/  TREE_TYPE (scalar_t__) ; 
 scalar_t__ VOID_TYPE_P (int /*<<< orphan*/ ) ; 
 scalar_t__ build2 (scalar_t__,int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 scalar_t__ error_mark_node ; 
 int /*<<< orphan*/  input_location ; 
 int /*<<< orphan*/  warn_if_unused_value (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ warn_unused_value ; 
 int /*<<< orphan*/  warning (int /*<<< orphan*/ ,char*) ; 

tree
build_compound_expr (tree expr1, tree expr2)
{
  if (!TREE_SIDE_EFFECTS (expr1))
    {
      /* The left-hand operand of a comma expression is like an expression
	 statement: with -Wextra or -Wunused, we should warn if it doesn't have
	 any side-effects, unless it was explicitly cast to (void).  */
      if (warn_unused_value)
	{
	  if (VOID_TYPE_P (TREE_TYPE (expr1))
	      && (TREE_CODE (expr1) == NOP_EXPR
		  || TREE_CODE (expr1) == CONVERT_EXPR))
	    ; /* (void) a, b */
	  else if (VOID_TYPE_P (TREE_TYPE (expr1))
		   && TREE_CODE (expr1) == COMPOUND_EXPR
		   && (TREE_CODE (TREE_OPERAND (expr1, 1)) == CONVERT_EXPR
		       || TREE_CODE (TREE_OPERAND (expr1, 1)) == NOP_EXPR))
	    ; /* (void) a, (void) b, c */
	  else
	    warning (0, "left-hand operand of comma expression has no effect");
	}
    }

  /* With -Wunused, we should also warn if the left-hand operand does have
     side-effects, but computes a value which is not used.  For example, in
     `foo() + bar(), baz()' the result of the `+' operator is not used,
     so we should issue a warning.  */
  else if (warn_unused_value)
    warn_if_unused_value (expr1, input_location);

  if (expr2 == error_mark_node)
    return error_mark_node;

  return build2 (COMPOUND_EXPR, TREE_TYPE (expr2), expr1, expr2);
}