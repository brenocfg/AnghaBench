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
typedef  scalar_t__ special_function_kind ;

/* Variables and functions */
 int /*<<< orphan*/  ADDR_EXPR ; 
 scalar_t__ ARRAY_TYPE ; 
 int /*<<< orphan*/  CLASSTYPE_DESTRUCTORS (scalar_t__) ; 
 scalar_t__ CLASSTYPE_LAZY_DESTRUCTOR (scalar_t__) ; 
 int /*<<< orphan*/  COMPLETE_TYPE_P (scalar_t__) ; 
 int /*<<< orphan*/  COMPOUND_EXPR ; 
 int /*<<< orphan*/  COND_EXPR ; 
 int /*<<< orphan*/  DECL_VIRTUAL_P (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DELETE_EXPR ; 
 int /*<<< orphan*/  IS_AGGR_TYPE (scalar_t__) ; 
 int LOOKUP_DESTRUCTOR ; 
 int /*<<< orphan*/  NE_EXPR ; 
 scalar_t__ NULL_TREE ; 
 scalar_t__ POINTER_TYPE ; 
 scalar_t__ TREE_CODE (scalar_t__) ; 
 scalar_t__ TREE_SIDE_EFFECTS (scalar_t__) ; 
 scalar_t__ TREE_TYPE (scalar_t__) ; 
 scalar_t__ TYPE_DOMAIN (scalar_t__) ; 
 scalar_t__ TYPE_GETS_REG_DELETE (scalar_t__) ; 
 scalar_t__ TYPE_HAS_TRIVIAL_DESTRUCTOR (scalar_t__) ; 
 scalar_t__ TYPE_MAIN_VARIANT (scalar_t__) ; 
 scalar_t__ VOID_TYPE_P (scalar_t__) ; 
 int /*<<< orphan*/  array_type_nelts (scalar_t__) ; 
 scalar_t__ build2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 scalar_t__ build3 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,scalar_t__,scalar_t__) ; 
 scalar_t__ build_builtin_delete_call (scalar_t__) ; 
 scalar_t__ build_dtor_call (int /*<<< orphan*/ ,scalar_t__,int) ; 
 int /*<<< orphan*/  build_indirect_ref (scalar_t__,int /*<<< orphan*/ *) ; 
 scalar_t__ build_op_delete_call (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  build_pointer_type (scalar_t__) ; 
 scalar_t__ build_unary_op (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ build_vec_delete (scalar_t__,int /*<<< orphan*/ ,scalar_t__,int) ; 
 int /*<<< orphan*/  complete_type (scalar_t__) ; 
 scalar_t__ convert_force (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cp_build_binary_op (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cxx_incomplete_type_diagnostic (scalar_t__,scalar_t__,int) ; 
 int /*<<< orphan*/  cxx_sizeof_nowarn (scalar_t__) ; 
 int /*<<< orphan*/  error (char*) ; 
 scalar_t__ error_mark_node ; 
 scalar_t__ fold (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gcc_assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  inform (char*) ; 
 scalar_t__ integer_one_node ; 
 int /*<<< orphan*/  integer_zero_node ; 
 int /*<<< orphan*/  lazily_declare_fn (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ save_expr (scalar_t__) ; 
 scalar_t__ sfk_complete_destructor ; 
 scalar_t__ sfk_deleting_destructor ; 
 int /*<<< orphan*/  sfk_destructor ; 
 int /*<<< orphan*/  void_type_node ; 
 scalar_t__ void_zero_node ; 
 int /*<<< orphan*/  warning (int /*<<< orphan*/ ,char*) ; 

tree
build_delete (tree type, tree addr, special_function_kind auto_delete,
    int flags, int use_global_delete)
{
  tree expr;

  if (addr == error_mark_node)
    return error_mark_node;

  /* Can happen when CURRENT_EXCEPTION_OBJECT gets its type
     set to `error_mark_node' before it gets properly cleaned up.  */
  if (type == error_mark_node)
    return error_mark_node;

  type = TYPE_MAIN_VARIANT (type);

  if (TREE_CODE (type) == POINTER_TYPE)
    {
      bool complete_p = true;

      type = TYPE_MAIN_VARIANT (TREE_TYPE (type));
      if (TREE_CODE (type) == ARRAY_TYPE)
	goto handle_array;

      /* We don't want to warn about delete of void*, only other
	  incomplete types.  Deleting other incomplete types
	  invokes undefined behavior, but it is not ill-formed, so
	  compile to something that would even do The Right Thing
	  (TM) should the type have a trivial dtor and no delete
	  operator.  */
      if (!VOID_TYPE_P (type))
	{
	  complete_type (type);
	  if (!COMPLETE_TYPE_P (type))
	    {
	      warning (0, "possible problem detected in invocation of "
		       "delete operator:");
	      cxx_incomplete_type_diagnostic (addr, type, 1);
	      inform ("neither the destructor nor the class-specific "
		      "operator delete will be called, even if they are "
		      "declared when the class is defined.");
	      complete_p = false;
	    }
	}
      if (VOID_TYPE_P (type) || !complete_p || !IS_AGGR_TYPE (type))
	/* Call the builtin operator delete.  */
	return build_builtin_delete_call (addr);
      if (TREE_SIDE_EFFECTS (addr))
	addr = save_expr (addr);

      /* Throw away const and volatile on target type of addr.  */
      addr = convert_force (build_pointer_type (type), addr, 0);
    }
  else if (TREE_CODE (type) == ARRAY_TYPE)
    {
    handle_array:

      if (TYPE_DOMAIN (type) == NULL_TREE)
	{
	  error ("unknown array size in delete");
	  return error_mark_node;
	}
      return build_vec_delete (addr, array_type_nelts (type),
			       auto_delete, use_global_delete);
    }
  else
    {
      /* Don't check PROTECT here; leave that decision to the
	 destructor.  If the destructor is accessible, call it,
	 else report error.  */
      addr = build_unary_op (ADDR_EXPR, addr, 0);
      if (TREE_SIDE_EFFECTS (addr))
	addr = save_expr (addr);

      addr = convert_force (build_pointer_type (type), addr, 0);
    }

  gcc_assert (IS_AGGR_TYPE (type));

  if (TYPE_HAS_TRIVIAL_DESTRUCTOR (type))
    {
      if (auto_delete != sfk_deleting_destructor)
	return void_zero_node;

      return build_op_delete_call (DELETE_EXPR, addr,
				   cxx_sizeof_nowarn (type),
				   use_global_delete,
				   /*placement=*/NULL_TREE,
				   /*alloc_fn=*/NULL_TREE);
    }
  else
    {
      tree do_delete = NULL_TREE;
      tree ifexp;

      if (CLASSTYPE_LAZY_DESTRUCTOR (type))
	lazily_declare_fn (sfk_destructor, type);

      /* For `::delete x', we must not use the deleting destructor
	 since then we would not be sure to get the global `operator
	 delete'.  */
      if (use_global_delete && auto_delete == sfk_deleting_destructor)
	{
	  /* We will use ADDR multiple times so we must save it.  */
	  addr = save_expr (addr);
	  /* Delete the object.  */
	  do_delete = build_builtin_delete_call (addr);
	  /* Otherwise, treat this like a complete object destructor
	     call.  */
	  auto_delete = sfk_complete_destructor;
	}
      /* If the destructor is non-virtual, there is no deleting
	 variant.  Instead, we must explicitly call the appropriate
	 `operator delete' here.  */
      else if (!DECL_VIRTUAL_P (CLASSTYPE_DESTRUCTORS (type))
	       && auto_delete == sfk_deleting_destructor)
	{
	  /* We will use ADDR multiple times so we must save it.  */
	  addr = save_expr (addr);
	  /* Build the call.  */
	  do_delete = build_op_delete_call (DELETE_EXPR,
					    addr,
					    cxx_sizeof_nowarn (type),
					    /*global_p=*/false,
					    /*placement=*/NULL_TREE,
					    /*alloc_fn=*/NULL_TREE);
	  /* Call the complete object destructor.  */
	  auto_delete = sfk_complete_destructor;
	}
      else if (auto_delete == sfk_deleting_destructor
	       && TYPE_GETS_REG_DELETE (type))
	{
	  /* Make sure we have access to the member op delete, even though
	     we'll actually be calling it from the destructor.  */
	  build_op_delete_call (DELETE_EXPR, addr, cxx_sizeof_nowarn (type),
				/*global_p=*/false,
				/*placement=*/NULL_TREE,
				/*alloc_fn=*/NULL_TREE);
	}

      expr = build_dtor_call (build_indirect_ref (addr, NULL),
			      auto_delete, flags);
      if (do_delete)
	expr = build2 (COMPOUND_EXPR, void_type_node, expr, do_delete);

      if (flags & LOOKUP_DESTRUCTOR)
	/* Explicit destructor call; don't check for null pointer.  */
	ifexp = integer_one_node;
      else
	/* Handle deleting a null pointer.  */
	ifexp = fold (cp_build_binary_op (NE_EXPR, addr, integer_zero_node));

      if (ifexp != integer_one_node)
	expr = build3 (COND_EXPR, void_type_node,
		       ifexp, expr, void_zero_node);

      return expr;
    }
}