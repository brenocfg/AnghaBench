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
typedef  scalar_t__ DECL_INITIAL ;

/* Variables and functions */
 int /*<<< orphan*/  ADDR_EXPR ; 
 int DIRECT_BIND ; 
 scalar_t__ IS_AGGR_TYPE (scalar_t__) ; 
 int LOOKUP_ONLYCONVERTING ; 
 int LOOKUP_PROTECT ; 
 scalar_t__ NULL_TREE ; 
 int /*<<< orphan*/  PLUS_EXPR ; 
 scalar_t__ REFERENCE_TYPE ; 
 scalar_t__ TREE_CODE (scalar_t__) ; 
 scalar_t__ TREE_TYPE (scalar_t__) ; 
 scalar_t__ TYPE_MAIN_VARIANT (scalar_t__) ; 
 int /*<<< orphan*/  ba_check ; 
 scalar_t__ build_base_path (int /*<<< orphan*/ ,scalar_t__,scalar_t__,int) ; 
 scalar_t__ build_nop (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  build_pointer_type (scalar_t__) ; 
 scalar_t__ build_unary_op (int /*<<< orphan*/ ,scalar_t__,int) ; 
 scalar_t__ convert_to_pointer_force (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  cp_finish_decl (scalar_t__,scalar_t__,int,scalar_t__,int) ; 
 scalar_t__ error_mark_node ; 
 scalar_t__ error_not_base_type (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  gcc_assert (int) ; 
 scalar_t__ get_target_expr (scalar_t__) ; 
 scalar_t__ lookup_base (scalar_t__,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lvalue_p (scalar_t__) ; 
 scalar_t__ make_temporary_var_for_ref_to_temp (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  real_lvalue_p (scalar_t__) ; 

__attribute__((used)) static tree
build_up_reference (tree type, tree arg, int flags, tree decl)
{
  tree rval;
  tree argtype = TREE_TYPE (arg);
  tree target_type = TREE_TYPE (type);

  gcc_assert (TREE_CODE (type) == REFERENCE_TYPE);

  if ((flags & DIRECT_BIND) && ! real_lvalue_p (arg))
    {
      /* Create a new temporary variable.  We can't just use a TARGET_EXPR
	 here because it needs to live as long as DECL.  */
      tree targ = arg;

      arg = make_temporary_var_for_ref_to_temp (decl, TREE_TYPE (arg));

      /* Process the initializer for the declaration.  */
      DECL_INITIAL (arg) = targ;
      cp_finish_decl (arg, targ, /*init_const_expr_p=*/false, NULL_TREE,
		      LOOKUP_ONLYCONVERTING|DIRECT_BIND);
    }
  else if (!(flags & DIRECT_BIND) && ! lvalue_p (arg))
    return get_target_expr (arg);

  /* If we had a way to wrap this up, and say, if we ever needed its
     address, transform all occurrences of the register, into a memory
     reference we could win better.  */
  rval = build_unary_op (ADDR_EXPR, arg, 1);
  if (rval == error_mark_node)
    return error_mark_node;

  if ((flags & LOOKUP_PROTECT)
      && TYPE_MAIN_VARIANT (argtype) != TYPE_MAIN_VARIANT (target_type)
      && IS_AGGR_TYPE (argtype)
      && IS_AGGR_TYPE (target_type))
    {
      /* We go through lookup_base for the access control.  */
      tree binfo = lookup_base (argtype, target_type, ba_check, NULL);
      if (binfo == error_mark_node)
	return error_mark_node;
      if (binfo == NULL_TREE)
	return error_not_base_type (target_type, argtype);
      rval = build_base_path (PLUS_EXPR, rval, binfo, 1);
    }
  else
    rval
      = convert_to_pointer_force (build_pointer_type (target_type), rval);
  return build_nop (type, rval);
}