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
typedef  enum tree_code { ____Placeholder_tree_code } tree_code ;
typedef  scalar_t__ base_kind ;

/* Variables and functions */
 scalar_t__ BINFO_OFFSET (scalar_t__) ; 
 int /*<<< orphan*/  COMPLETE_TYPE_P (scalar_t__) ; 
 int /*<<< orphan*/  CONVERT_EXPR ; 
 scalar_t__ FUNCTION_TYPE ; 
 scalar_t__ GET_MODE_SIZE (int /*<<< orphan*/ ) ; 
 scalar_t__ INTEGRAL_CODE_P (int) ; 
 scalar_t__ IS_AGGR_TYPE (scalar_t__) ; 
 scalar_t__ METHOD_TYPE ; 
 int MINUS_EXPR ; 
 int /*<<< orphan*/  NOP_EXPR ; 
 scalar_t__ NULL_TREE ; 
 scalar_t__ OFFSET_REF ; 
 int PLUS_EXPR ; 
 scalar_t__ POINTER_SIZE ; 
 scalar_t__ POINTER_TYPE ; 
 scalar_t__ POINTER_TYPE_P (scalar_t__) ; 
 scalar_t__ PTRMEM_CST ; 
 scalar_t__ PTRMEM_CST_MEMBER (scalar_t__) ; 
 scalar_t__ RECORD_TYPE ; 
 scalar_t__ TREE_CODE (scalar_t__) ; 
 scalar_t__ TREE_OPERAND (scalar_t__,int) ; 
 scalar_t__ TREE_TYPE (scalar_t__) ; 
 scalar_t__ TYPE_MAIN_VARIANT (scalar_t__) ; 
 int /*<<< orphan*/  TYPE_MODE (scalar_t__) ; 
 scalar_t__ TYPE_PRECISION (scalar_t__) ; 
 int /*<<< orphan*/  TYPE_PTRMEMFUNC_FN_TYPE (scalar_t__) ; 
 scalar_t__ TYPE_PTRMEMFUNC_P (scalar_t__) ; 
 scalar_t__ TYPE_PTRMEM_CLASS_TYPE (scalar_t__) ; 
 scalar_t__ TYPE_PTRMEM_P (scalar_t__) ; 
 scalar_t__ TYPE_PTR_TO_MEMBER_P (scalar_t__) ; 
 scalar_t__ VOID_TYPE_P (scalar_t__) ; 
 int /*<<< orphan*/  ba_check ; 
 scalar_t__ bk_via_virtual ; 
 scalar_t__ build1 (int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 scalar_t__ build_base_path (int,scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ build_int_cst (scalar_t__,int) ; 
 scalar_t__ build_nop (scalar_t__,scalar_t__) ; 
 scalar_t__ build_ptrmemfunc (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int) ; 
 scalar_t__ build_type_conversion (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  c_common_type_for_size (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ complete_type (scalar_t__) ; 
 scalar_t__ convert_member_func_to_ptr (scalar_t__,scalar_t__) ; 
 scalar_t__ convert_to_pointer (scalar_t__,scalar_t__) ; 
 scalar_t__ cp_convert (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ cplus_expand_constant (scalar_t__) ; 
 int /*<<< orphan*/  error (char*,scalar_t__,scalar_t__,...) ; 
 scalar_t__ error_mark_node ; 
 scalar_t__ force_fit_type (scalar_t__,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  gcc_assert (int) ; 
 scalar_t__ get_member_function_from_ptrfunc (scalar_t__*,scalar_t__) ; 
 scalar_t__ instantiate_type (scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ integer_zerop (scalar_t__) ; 
 scalar_t__ lookup_base (scalar_t__,scalar_t__,int /*<<< orphan*/ ,scalar_t__*) ; 
 int same_type_p (scalar_t__,scalar_t__) ; 
 scalar_t__ size_binop (int,scalar_t__,scalar_t__) ; 
 scalar_t__ sizetype ; 
 int /*<<< orphan*/  tf_warning_or_error ; 
 scalar_t__ type_unknown_p (scalar_t__) ; 
 int /*<<< orphan*/  warn_pmf2ptr ; 
 int /*<<< orphan*/  warning (int /*<<< orphan*/ ,char*,scalar_t__,scalar_t__) ; 

__attribute__((used)) static tree
cp_convert_to_pointer (tree type, tree expr, bool force)
{
  tree intype = TREE_TYPE (expr);
  enum tree_code form;
  tree rval;
  if (intype == error_mark_node)
    return error_mark_node;

  if (IS_AGGR_TYPE (intype))
    {
      intype = complete_type (intype);
      if (!COMPLETE_TYPE_P (intype))
	{
	  error ("can't convert from incomplete type %qT to %qT",
		 intype, type);
	  return error_mark_node;
	}

      rval = build_type_conversion (type, expr);
      if (rval)
	{
	  if (rval == error_mark_node)
	    error ("conversion of %qE from %qT to %qT is ambiguous",
		   expr, intype, type);
	  return rval;
	}
    }

  /* Handle anachronistic conversions from (::*)() to cv void* or (*)().  */
  if (TREE_CODE (type) == POINTER_TYPE
      && (TREE_CODE (TREE_TYPE (type)) == FUNCTION_TYPE
	  || VOID_TYPE_P (TREE_TYPE (type))))
    {
      if (TYPE_PTRMEMFUNC_P (intype)
	  || TREE_CODE (intype) == METHOD_TYPE)
	return convert_member_func_to_ptr (type, expr);
      if (TREE_CODE (TREE_TYPE (expr)) == POINTER_TYPE)
	return build_nop (type, expr);
      intype = TREE_TYPE (expr);
    }

  if (expr == error_mark_node)
    return error_mark_node;

  form = TREE_CODE (intype);

  if (POINTER_TYPE_P (intype))
    {
      intype = TYPE_MAIN_VARIANT (intype);

      if (TYPE_MAIN_VARIANT (type) != intype
	  && TREE_CODE (type) == POINTER_TYPE
	  && TREE_CODE (TREE_TYPE (type)) == RECORD_TYPE
	  && IS_AGGR_TYPE (TREE_TYPE (type))
	  && IS_AGGR_TYPE (TREE_TYPE (intype))
	  && TREE_CODE (TREE_TYPE (intype)) == RECORD_TYPE)
	{
	  enum tree_code code = PLUS_EXPR;
	  tree binfo;
	  tree intype_class;
	  tree type_class;
	  bool same_p;

	  intype_class = TREE_TYPE (intype);
	  type_class = TREE_TYPE (type);

	  same_p = same_type_p (TYPE_MAIN_VARIANT (intype_class),
				TYPE_MAIN_VARIANT (type_class));
	  binfo = NULL_TREE;
	  /* Try derived to base conversion.  */
	  if (!same_p)
	    binfo = lookup_base (intype_class, type_class, ba_check, NULL);
	  if (!same_p && !binfo)
	    {
	      /* Try base to derived conversion.  */
	      binfo = lookup_base (type_class, intype_class, ba_check, NULL);
	      code = MINUS_EXPR;
	    }
	  if (binfo == error_mark_node)
	    return error_mark_node;
	  if (binfo || same_p)
	    {
	      if (binfo)
		expr = build_base_path (code, expr, binfo, 0);
	      /* Add any qualifier conversions.  */
	      return build_nop (type, expr);
	    }
	}

      if (TYPE_PTRMEMFUNC_P (type))
	{
	  error ("cannot convert %qE from type %qT to type %qT",
		 expr, intype, type);
	  return error_mark_node;
	}

      return build_nop (type, expr);
    }
  else if (TYPE_PTRMEM_P (type) && TYPE_PTRMEM_P (intype))
    {
      tree b1;
      tree b2;
      tree binfo;
      enum tree_code code = PLUS_EXPR;
      base_kind bk;

      b1 = TYPE_PTRMEM_CLASS_TYPE (type);
      b2 = TYPE_PTRMEM_CLASS_TYPE (intype);
      binfo = lookup_base (b1, b2, ba_check, &bk);
      if (!binfo)
	{
	  binfo = lookup_base (b2, b1, ba_check, &bk);
	  code = MINUS_EXPR;
	}
      if (binfo == error_mark_node)
	return error_mark_node;

      if (bk == bk_via_virtual)
	{
	  if (force)
	    warning (0, "pointer to member cast from %qT to %qT is via"
		     " virtual base", intype, type);
	  else
	    {
	      error ("pointer to member cast from %qT to %qT is"
		     " via virtual base", intype, type);
	      return error_mark_node;
	    }
	  /* This is a reinterpret cast, whose result is unspecified.
	     We choose to do nothing.  */
	  return build1 (NOP_EXPR, type, expr);
	}

      if (TREE_CODE (expr) == PTRMEM_CST)
	expr = cplus_expand_constant (expr);

      if (binfo && !integer_zerop (BINFO_OFFSET (binfo)))
	expr = size_binop (code,
			   build_nop (sizetype, expr),
			   BINFO_OFFSET (binfo));
      return build_nop (type, expr);
    }
  else if (TYPE_PTRMEMFUNC_P (type) && TYPE_PTRMEMFUNC_P (intype))
    return build_ptrmemfunc (TYPE_PTRMEMFUNC_FN_TYPE (type), expr, 0,
			     /*c_cast_p=*/false);
  else if (TYPE_PTRMEMFUNC_P (intype))
    {
      if (!warn_pmf2ptr)
	{
	  if (TREE_CODE (expr) == PTRMEM_CST)
	    return cp_convert_to_pointer (type,
					  PTRMEM_CST_MEMBER (expr),
					  force);
	  else if (TREE_CODE (expr) == OFFSET_REF)
	    {
	      tree object = TREE_OPERAND (expr, 0);
	      return get_member_function_from_ptrfunc (&object,
						       TREE_OPERAND (expr, 1));
	    }
	}
      error ("cannot convert %qE from type %qT to type %qT",
	     expr, intype, type);
      return error_mark_node;
    }

  if (integer_zerop (expr))
    {
      if (TYPE_PTRMEMFUNC_P (type))
	return build_ptrmemfunc (TYPE_PTRMEMFUNC_FN_TYPE (type), expr, 0,
				 /*c_cast_p=*/false);

      if (TYPE_PTRMEM_P (type))
	{
	  /* A NULL pointer-to-member is represented by -1, not by
	     zero.  */
	  expr = build_int_cst (type, -1);
	  /* Fix up the representation of -1 if appropriate.  */
	  expr = force_fit_type (expr, 0, false, false);
	}
      else
	expr = build_int_cst (type, 0);

      return expr;
    }
  else if (TYPE_PTR_TO_MEMBER_P (type) && INTEGRAL_CODE_P (form))
    {
      error ("invalid conversion from %qT to %qT", intype, type);
      return error_mark_node;
    }

  if (INTEGRAL_CODE_P (form))
    {
      if (TYPE_PRECISION (intype) == POINTER_SIZE)
	return build1 (CONVERT_EXPR, type, expr);
      expr = cp_convert (c_common_type_for_size (POINTER_SIZE, 0), expr);
      /* Modes may be different but sizes should be the same.  There
	 is supposed to be some integral type that is the same width
	 as a pointer.  */
      gcc_assert (GET_MODE_SIZE (TYPE_MODE (TREE_TYPE (expr)))
		  == GET_MODE_SIZE (TYPE_MODE (type)));

      return convert_to_pointer (type, expr);
    }

  if (type_unknown_p (expr))
    return instantiate_type (type, expr, tf_warning_or_error);

  error ("cannot convert %qE from type %qT to type %qT",
	 expr, intype, type);
  return error_mark_node;
}