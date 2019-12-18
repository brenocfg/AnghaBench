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
typedef  void* tree ;

/* Variables and functions */
 scalar_t__ ADDR_EXPR ; 
 scalar_t__ COMPONENT_REF ; 
 scalar_t__ COMPOUND_EXPR ; 
 int /*<<< orphan*/  COMPOUND_EXPR_OVERLOADED (void*) ; 
 scalar_t__ COND_EXPR ; 
 scalar_t__ INTEGER_CST ; 
 int /*<<< orphan*/  NON_DEPENDENT_EXPR ; 
 scalar_t__ OFFSET_REF ; 
 scalar_t__ REAL_CST ; 
 scalar_t__ STRING_CST ; 
 scalar_t__ THROW_EXPR ; 
 scalar_t__ TREE_CODE (void*) ; 
 void* TREE_OPERAND (void*,int) ; 
 scalar_t__ TREE_TYPE (void*) ; 
 scalar_t__ VAR_DECL ; 
 void* build1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*) ; 
 void* build2 (scalar_t__,scalar_t__,void*,void*) ; 
 void* build3 (scalar_t__,scalar_t__,void*,void*,void*) ; 
 int /*<<< orphan*/  gcc_assert (int) ; 
 scalar_t__ is_overloaded_fn (void*) ; 
 int /*<<< orphan*/  non_reference (scalar_t__) ; 
 scalar_t__ null_ptr_cst_p (void*) ; 
 scalar_t__ unknown_type_node ; 

tree
build_non_dependent_expr (tree expr)
{
  tree inner_expr;

  /* Preserve null pointer constants so that the type of things like
     "p == 0" where "p" is a pointer can be determined.  */
  if (null_ptr_cst_p (expr))
    return expr;
  /* Preserve OVERLOADs; the functions must be available to resolve
     types.  */
  inner_expr = expr;
  if (TREE_CODE (inner_expr) == ADDR_EXPR)
    inner_expr = TREE_OPERAND (inner_expr, 0);
  if (TREE_CODE (inner_expr) == COMPONENT_REF)
    inner_expr = TREE_OPERAND (inner_expr, 1);
  if (is_overloaded_fn (inner_expr)
      || TREE_CODE (inner_expr) == OFFSET_REF)
    return expr;
  /* There is no need to return a proxy for a variable.  */
  if (TREE_CODE (expr) == VAR_DECL)
    return expr;
  /* Preserve string constants; conversions from string constants to
     "char *" are allowed, even though normally a "const char *"
     cannot be used to initialize a "char *".  */
  if (TREE_CODE (expr) == STRING_CST)
    return expr;
  /* Preserve arithmetic constants, as an optimization -- there is no
     reason to create a new node.  */
  if (TREE_CODE (expr) == INTEGER_CST || TREE_CODE (expr) == REAL_CST)
    return expr;
  /* Preserve THROW_EXPRs -- all throw-expressions have type "void".
     There is at least one place where we want to know that a
     particular expression is a throw-expression: when checking a ?:
     expression, there are special rules if the second or third
     argument is a throw-expression.  */
  if (TREE_CODE (expr) == THROW_EXPR)
    return expr;

  if (TREE_CODE (expr) == COND_EXPR)
    return build3 (COND_EXPR,
		   TREE_TYPE (expr),
		   TREE_OPERAND (expr, 0),
		   (TREE_OPERAND (expr, 1)
		    ? build_non_dependent_expr (TREE_OPERAND (expr, 1))
		    : build_non_dependent_expr (TREE_OPERAND (expr, 0))),
		   build_non_dependent_expr (TREE_OPERAND (expr, 2)));
  if (TREE_CODE (expr) == COMPOUND_EXPR
      && !COMPOUND_EXPR_OVERLOADED (expr))
    return build2 (COMPOUND_EXPR,
		   TREE_TYPE (expr),
		   TREE_OPERAND (expr, 0),
		   build_non_dependent_expr (TREE_OPERAND (expr, 1)));

  /* If the type is unknown, it can't really be non-dependent */
  gcc_assert (TREE_TYPE (expr) != unknown_type_node);

  /* Otherwise, build a NON_DEPENDENT_EXPR.

     REFERENCE_TYPEs are not stripped for expressions in templates
     because doing so would play havoc with mangling.  Consider, for
     example:

       template <typename T> void f<T& g>() { g(); }

     In the body of "f", the expression for "g" will have
     REFERENCE_TYPE, even though the standard says that it should
     not.  The reason is that we must preserve the syntactic form of
     the expression so that mangling (say) "f<g>" inside the body of
     "f" works out correctly.  Therefore, the REFERENCE_TYPE is
     stripped here.  */
  return build1 (NON_DEPENDENT_EXPR, non_reference (TREE_TYPE (expr)), expr);
}