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
 scalar_t__ FUNCTION_TYPE ; 
 scalar_t__ NOP_EXPR ; 
 scalar_t__ NULL_TREE ; 
 int /*<<< orphan*/  POINTER_TYPE_P (scalar_t__) ; 
 scalar_t__ REFERENCE_TYPE ; 
 scalar_t__ TREE_CODE (scalar_t__) ; 
 scalar_t__ TREE_OPERAND (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ TREE_TYPE (scalar_t__) ; 
 scalar_t__ TYPE_PTRMEM_P (scalar_t__) ; 
 scalar_t__ TYPE_PTR_P (scalar_t__) ; 
 scalar_t__ build_nop (scalar_t__,scalar_t__) ; 
 scalar_t__ build_pointer_type (scalar_t__) ; 
 scalar_t__ build_unary_op (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  check_for_casting_away_constness (scalar_t__,scalar_t__,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ comp_ptr_ttypes_const (scalar_t__,scalar_t__) ; 
 scalar_t__ convert_from_reference (scalar_t__) ; 
 scalar_t__ decay_conversion (scalar_t__) ; 
 int /*<<< orphan*/  error (char*,scalar_t__,...) ; 
 scalar_t__ error_mark_node ; 
 int /*<<< orphan*/  gcc_assert (int) ; 
 int /*<<< orphan*/  processing_template_decl ; 
 int /*<<< orphan*/  real_lvalue_p (scalar_t__) ; 
 scalar_t__ type_decays_to (scalar_t__) ; 
 int /*<<< orphan*/  used_types_insert (scalar_t__) ; 
 scalar_t__ warn_cast_qual ; 
 int /*<<< orphan*/  warning0 ; 

__attribute__((used)) static tree
build_const_cast_1 (tree dst_type, tree expr, bool complain,
		    bool *valid_p)
{
  tree src_type;
  tree reference_type;

  /* Callers are responsible for handling error_mark_node as a
     destination type.  */
  gcc_assert (dst_type != error_mark_node);
  /* In a template, callers should be building syntactic
     representations of casts, not using this machinery.  */
  gcc_assert (!processing_template_decl);

  /* Assume the conversion is invalid.  */
  if (valid_p)
    *valid_p = false;

  if (!POINTER_TYPE_P (dst_type) && !TYPE_PTRMEM_P (dst_type))
    {
      if (complain)
	error ("invalid use of const_cast with type %qT, "
	       "which is not a pointer, "
	       "reference, nor a pointer-to-data-member type", dst_type);
      return error_mark_node;
    }

  if (TREE_CODE (TREE_TYPE (dst_type)) == FUNCTION_TYPE)
    {
      if (complain)
	error ("invalid use of const_cast with type %qT, which is a pointer "
	       "or reference to a function type", dst_type);
      return error_mark_node;
    }

  /* Save casted types in the function's used types hash table.  */
  used_types_insert (dst_type);

  src_type = TREE_TYPE (expr);
  /* Expressions do not really have reference types.  */
  if (TREE_CODE (src_type) == REFERENCE_TYPE)
    src_type = TREE_TYPE (src_type);

  /* [expr.const.cast]

     An lvalue of type T1 can be explicitly converted to an lvalue of
     type T2 using the cast const_cast<T2&> (where T1 and T2 are object
     types) if a pointer to T1 can be explicitly converted to the type
     pointer to T2 using a const_cast.  */
  if (TREE_CODE (dst_type) == REFERENCE_TYPE)
    {
      reference_type = dst_type;
      if (! real_lvalue_p (expr))
	{
	  if (complain)
	    error ("invalid const_cast of an rvalue of type %qT to type %qT",
		   src_type, dst_type);
	  return error_mark_node;
	}
      dst_type = build_pointer_type (TREE_TYPE (dst_type));
      src_type = build_pointer_type (src_type);
    }
  else
    {
      reference_type = NULL_TREE;
      /* If the destination type is not a reference type, the
	 lvalue-to-rvalue, array-to-pointer, and function-to-pointer
	 conversions are performed.  */
      src_type = type_decays_to (src_type);
      if (src_type == error_mark_node)
	return error_mark_node;
    }

  if ((TYPE_PTR_P (src_type) || TYPE_PTRMEM_P (src_type))
      && comp_ptr_ttypes_const (dst_type, src_type))
    {
      if (valid_p)
	{
	  *valid_p = true;
	  /* This cast is actually a C-style cast.  Issue a warning if
	     the user is making a potentially unsafe cast.  */
	  if (warn_cast_qual)
	    check_for_casting_away_constness (src_type, dst_type,
					      warning0,
					      "cast");
	}
      if (reference_type)
	{
	  expr = build_unary_op (ADDR_EXPR, expr, 0);
	  expr = build_nop (reference_type, expr);
	  return convert_from_reference (expr);
	}
      else
	{
	  expr = decay_conversion (expr);
	  /* build_c_cast puts on a NOP_EXPR to make the result not an
	     lvalue.  Strip such NOP_EXPRs if VALUE is being used in
	     non-lvalue context.  */
	  if (TREE_CODE (expr) == NOP_EXPR
	      && TREE_TYPE (expr) == TREE_TYPE (TREE_OPERAND (expr, 0)))
	    expr = TREE_OPERAND (expr, 0);
	  return build_nop (dst_type, expr);
	}
    }

  if (complain)
    error ("invalid const_cast from type %qT to type %qT",
	   src_type, dst_type);
  return error_mark_node;
}