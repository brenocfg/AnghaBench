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
 int /*<<< orphan*/  ADDR_EXPR ; 
 int /*<<< orphan*/  CALL_EXPR ; 
 scalar_t__ DOTSTAR_EXPR ; 
 scalar_t__ MEMBER_REF ; 
 int /*<<< orphan*/  NULL_TREE ; 
 scalar_t__ OFFSET_REF ; 
 scalar_t__ TREE_CODE (scalar_t__) ; 
 scalar_t__ TREE_OPERAND (scalar_t__,int) ; 
 scalar_t__ any_type_dependent_arguments_p (scalar_t__) ; 
 scalar_t__ build_function_call (scalar_t__,scalar_t__) ; 
 scalar_t__ build_min_non_dep (int /*<<< orphan*/ ,scalar_t__,scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ build_min_nt (int /*<<< orphan*/ ,scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ build_non_dependent_args (scalar_t__) ; 
 scalar_t__ build_non_dependent_expr (scalar_t__) ; 
 scalar_t__ build_unary_op (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ error_mark_node ; 
 int /*<<< orphan*/  gcc_assert (int) ; 
 scalar_t__ get_member_function_from_ptrfunc (scalar_t__*,scalar_t__) ; 
 scalar_t__ processing_template_decl ; 
 scalar_t__ tree_cons (int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 scalar_t__ type_dependent_expression_p (scalar_t__) ; 

tree
build_offset_ref_call_from_tree (tree fn, tree args)
{
  tree orig_fn;
  tree orig_args;
  tree expr;
  tree object;

  orig_fn = fn;
  orig_args = args;
  object = TREE_OPERAND (fn, 0);

  if (processing_template_decl)
    {
      gcc_assert (TREE_CODE (fn) == DOTSTAR_EXPR
		  || TREE_CODE (fn) == MEMBER_REF);
      if (type_dependent_expression_p (fn)
	  || any_type_dependent_arguments_p (args))
	return build_min_nt (CALL_EXPR, fn, args, NULL_TREE);

      /* Transform the arguments and add the implicit "this"
	 parameter.  That must be done before the FN is transformed
	 because we depend on the form of FN.  */
      args = build_non_dependent_args (args);
      if (TREE_CODE (fn) == DOTSTAR_EXPR)
	object = build_unary_op (ADDR_EXPR, object, 0);
      object = build_non_dependent_expr (object);
      args = tree_cons (NULL_TREE, object, args);
      /* Now that the arguments are done, transform FN.  */
      fn = build_non_dependent_expr (fn);
    }

  /* A qualified name corresponding to a bound pointer-to-member is
     represented as an OFFSET_REF:

	struct B { void g(); };
	void (B::*p)();
	void B::g() { (this->*p)(); }  */
  if (TREE_CODE (fn) == OFFSET_REF)
    {
      tree object_addr = build_unary_op (ADDR_EXPR, object, 0);
      fn = TREE_OPERAND (fn, 1);
      fn = get_member_function_from_ptrfunc (&object_addr, fn);
      args = tree_cons (NULL_TREE, object_addr, args);
    }

  expr = build_function_call (fn, args);
  if (processing_template_decl && expr != error_mark_node)
    return build_min_non_dep (CALL_EXPR, expr, orig_fn, orig_args, NULL_TREE);
  return expr;
}