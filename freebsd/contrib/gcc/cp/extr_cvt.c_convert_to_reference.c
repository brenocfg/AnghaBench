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
 int COMPARE_BASE ; 
 int COMPARE_DERIVED ; 
 int CONV_CONST ; 
 int CONV_IMPLICIT ; 
 int CONV_REINTERPRET ; 
 int CONV_STATIC ; 
 scalar_t__ FUNCTION_TYPE ; 
 scalar_t__ IS_AGGR_TYPE (scalar_t__) ; 
 int LOOKUP_COMPLAIN ; 
 int LOOKUP_NO_CONVERSION ; 
 int /*<<< orphan*/  NOP_EXPR ; 
 scalar_t__ NULL_TREE ; 
 scalar_t__ POINTER_TYPE ; 
 scalar_t__ REFERENCE_TYPE ; 
 scalar_t__ TREE_CODE (scalar_t__) ; 
 scalar_t__ TREE_TYPE (scalar_t__) ; 
 scalar_t__ TYPE_MAIN_VARIANT (scalar_t__) ; 
 int /*<<< orphan*/  at_least_as_qualified_p (scalar_t__,scalar_t__) ; 
 scalar_t__ build1 (int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  build_pointer_type (scalar_t__) ; 
 scalar_t__ build_type_conversion (scalar_t__,scalar_t__) ; 
 scalar_t__ build_unary_op (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ build_up_reference (scalar_t__,scalar_t__,int,scalar_t__) ; 
 int can_convert (scalar_t__,scalar_t__) ; 
 scalar_t__ comptypes (scalar_t__,scalar_t__,int) ; 
 scalar_t__ convert_for_initialization (scalar_t__,scalar_t__,scalar_t__,int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ convert_force (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  error (char*,scalar_t__,scalar_t__) ; 
 scalar_t__ error_mark_node ; 
 int /*<<< orphan*/  gcc_assert (int) ; 
 scalar_t__ instantiate_type (scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ lvalue_p (scalar_t__) ; 
 scalar_t__ lvalue_type (scalar_t__) ; 
 int /*<<< orphan*/  pedwarn (char*,scalar_t__,scalar_t__) ; 
 scalar_t__ real_lvalue_p (scalar_t__) ; 
 int /*<<< orphan*/  tf_none ; 
 int /*<<< orphan*/  tf_warning_or_error ; 
 scalar_t__ unknown_type_node ; 
 int /*<<< orphan*/  warn_ref_binding (scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  warning (int /*<<< orphan*/ ,char*,scalar_t__,scalar_t__) ; 

tree
convert_to_reference (tree reftype, tree expr, int convtype,
		      int flags, tree decl)
{
  tree type = TYPE_MAIN_VARIANT (TREE_TYPE (reftype));
  tree intype;
  tree rval = NULL_TREE;
  tree rval_as_conversion = NULL_TREE;
  bool can_convert_intype_to_type;

  if (TREE_CODE (type) == FUNCTION_TYPE
      && TREE_TYPE (expr) == unknown_type_node)
    expr = instantiate_type (type, expr,
			     (flags & LOOKUP_COMPLAIN)
			     ? tf_warning_or_error : tf_none);

  if (expr == error_mark_node)
    return error_mark_node;

  intype = TREE_TYPE (expr);

  gcc_assert (TREE_CODE (intype) != REFERENCE_TYPE);
  gcc_assert (TREE_CODE (reftype) == REFERENCE_TYPE);

  intype = TYPE_MAIN_VARIANT (intype);

  can_convert_intype_to_type = can_convert (type, intype);
  if (!can_convert_intype_to_type
      && (convtype & CONV_IMPLICIT) && IS_AGGR_TYPE (intype)
      && ! (flags & LOOKUP_NO_CONVERSION))
    {
      /* Look for a user-defined conversion to lvalue that we can use.  */

      rval_as_conversion
	= build_type_conversion (reftype, expr);

      if (rval_as_conversion && rval_as_conversion != error_mark_node
	  && real_lvalue_p (rval_as_conversion))
	{
	  expr = rval_as_conversion;
	  rval_as_conversion = NULL_TREE;
	  intype = type;
	  can_convert_intype_to_type = 1;
	}
    }

  if (((convtype & CONV_STATIC) && can_convert (intype, type))
      || ((convtype & CONV_IMPLICIT) && can_convert_intype_to_type))
    {
      if (flags & LOOKUP_COMPLAIN)
	{
	  tree ttl = TREE_TYPE (reftype);
	  tree ttr = lvalue_type (expr);

	  if (! real_lvalue_p (expr))
	    warn_ref_binding (reftype, intype, decl);

	  if (! (convtype & CONV_CONST)
		   && !at_least_as_qualified_p (ttl, ttr))
	    pedwarn ("conversion from %qT to %qT discards qualifiers",
		     ttr, reftype);
	}

      return build_up_reference (reftype, expr, flags, decl);
    }
  else if ((convtype & CONV_REINTERPRET) && lvalue_p (expr))
    {
      /* When casting an lvalue to a reference type, just convert into
	 a pointer to the new type and deference it.  This is allowed
	 by San Diego WP section 5.2.9 paragraph 12, though perhaps it
	 should be done directly (jason).  (int &)ri ---> *(int*)&ri */

      /* B* bp; A& ar = (A&)bp; is valid, but it's probably not what they
	 meant.  */
      if (TREE_CODE (intype) == POINTER_TYPE
	  && (comptypes (TREE_TYPE (intype), type,
			 COMPARE_BASE | COMPARE_DERIVED)))
	warning (0, "casting %qT to %qT does not dereference pointer",
		 intype, reftype);

      rval = build_unary_op (ADDR_EXPR, expr, 0);
      if (rval != error_mark_node)
	rval = convert_force (build_pointer_type (TREE_TYPE (reftype)),
			      rval, 0);
      if (rval != error_mark_node)
	rval = build1 (NOP_EXPR, reftype, rval);
    }
  else
    {
      rval = convert_for_initialization (NULL_TREE, type, expr, flags,
					 "converting", 0, 0);
      if (rval == NULL_TREE || rval == error_mark_node)
	return rval;
      warn_ref_binding (reftype, intype, decl);
      rval = build_up_reference (reftype, rval, flags, decl);
    }

  if (rval)
    {
      /* If we found a way to convert earlier, then use it.  */
      return rval;
    }

  if (flags & LOOKUP_COMPLAIN)
    error ("cannot convert type %qT to type %qT", intype, reftype);

  return error_mark_node;
}