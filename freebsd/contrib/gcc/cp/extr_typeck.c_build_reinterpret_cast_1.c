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
 scalar_t__ BLOCK_POINTER_TYPE ; 
 int COMPARE_BASE ; 
 int COMPARE_DERIVED ; 
 scalar_t__ COMPLETE_TYPE_P (scalar_t__) ; 
 scalar_t__ CP_INTEGRAL_TYPE_P (scalar_t__) ; 
 scalar_t__ FUNCTION_TYPE ; 
 scalar_t__ INTEGER_TYPE ; 
 scalar_t__ INTEGRAL_OR_ENUMERATION_TYPE_P (scalar_t__) ; 
 scalar_t__ INTEGRAL_TYPE_P (scalar_t__) ; 
 scalar_t__ METHOD_TYPE ; 
 scalar_t__ NOP_EXPR ; 
 int /*<<< orphan*/  POINTER_SIZE ; 
 scalar_t__ POINTER_TYPE ; 
 scalar_t__ REFERENCE_TYPE ; 
 scalar_t__ STRICT_ALIGNMENT ; 
 int /*<<< orphan*/  STRIP_NOPS (scalar_t__) ; 
 scalar_t__ TREE_CODE (scalar_t__) ; 
 scalar_t__ TREE_OPERAND (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ TREE_TYPE (scalar_t__) ; 
 scalar_t__ TYPE_ALIGN (scalar_t__) ; 
 scalar_t__ TYPE_PRECISION (scalar_t__) ; 
 scalar_t__ TYPE_PTRFN_P (scalar_t__) ; 
 scalar_t__ TYPE_PTRMEMFUNC_P (scalar_t__) ; 
 scalar_t__ TYPE_PTRMEM_P (scalar_t__) ; 
 scalar_t__ TYPE_PTROBV_P (scalar_t__) ; 
 scalar_t__ TYPE_PTR_P (scalar_t__) ; 
 scalar_t__ TYPE_UNSIGNED (scalar_t__) ; 
 scalar_t__ VECTOR_TYPE ; 
 scalar_t__ VOID_TYPE_P (scalar_t__) ; 
 scalar_t__ build_indirect_ref (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  build_nop (scalar_t__,scalar_t__) ; 
 scalar_t__ build_pointer_type (scalar_t__) ; 
 scalar_t__ build_unary_op (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ c_common_type_for_size (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  check_for_casting_away_constness (scalar_t__,scalar_t__,int /*<<< orphan*/  (*) (char*,scalar_t__,scalar_t__),char*) ; 
 scalar_t__ comptypes (scalar_t__,scalar_t__,int) ; 
 scalar_t__ convert_member_func_to_ptr (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  convert_to_integer (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  convert_to_vector (scalar_t__,scalar_t__) ; 
 scalar_t__ cp_convert (scalar_t__,scalar_t__) ; 
 scalar_t__ decay_conversion (scalar_t__) ; 
 int /*<<< orphan*/  error (char*,scalar_t__,scalar_t__) ; 
 scalar_t__ error_mark_node ; 
 scalar_t__ error_operand_p (scalar_t__) ; 
 scalar_t__ fold_if_not_in_template (int /*<<< orphan*/ ) ; 
 scalar_t__ objc_is_id (scalar_t__) ; 
 scalar_t__ pedantic ; 
 int /*<<< orphan*/  pedwarn (char*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  real_lvalue_p (scalar_t__) ; 
 int /*<<< orphan*/  strict_aliasing_warning (scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  used_types_insert (scalar_t__) ; 
 scalar_t__ warn_cast_align ; 
 int warn_strict_aliasing ; 
 int /*<<< orphan*/  warning (int /*<<< orphan*/ ,char*,...) ; 

__attribute__((used)) static tree
build_reinterpret_cast_1 (tree type, tree expr, bool c_cast_p,
			  bool *valid_p)
{
  tree intype;

  /* Assume the cast is invalid.  */
  if (valid_p)
    *valid_p = true;

  if (type == error_mark_node || error_operand_p (expr))
    return error_mark_node;

  intype = TREE_TYPE (expr);

  /* Save casted types in the function's used types hash table.  */
  used_types_insert (type);

  /* [expr.reinterpret.cast]
     An lvalue expression of type T1 can be cast to the type
     "reference to T2" if an expression of type "pointer to T1" can be
     explicitly converted to the type "pointer to T2" using a
     reinterpret_cast.  */
  if (TREE_CODE (type) == REFERENCE_TYPE)
    {
      if (! real_lvalue_p (expr))
	{
	  error ("invalid cast of an rvalue expression of type "
		 "%qT to type %qT",
		 intype, type);
	  return error_mark_node;
	}

      /* Warn about a reinterpret_cast from "A*" to "B&" if "A" and
	 "B" are related class types; the reinterpret_cast does not
	 adjust the pointer.  */
      if (TYPE_PTR_P (intype)
	  && (comptypes (TREE_TYPE (intype), TREE_TYPE (type),
			 COMPARE_BASE | COMPARE_DERIVED)))
	warning (0, "casting %qT to %qT does not dereference pointer",
		 intype, type);

      expr = build_unary_op (ADDR_EXPR, expr, 0);
      if (expr != error_mark_node)
	expr = build_reinterpret_cast_1
	  (build_pointer_type (TREE_TYPE (type)), expr, c_cast_p,
	   valid_p);
      if (expr != error_mark_node)
	expr = build_indirect_ref (expr, 0);
      return expr;
    }

  /* As a G++ extension, we consider conversions from member
     functions, and pointers to member functions to
     pointer-to-function and pointer-to-void types.  If
     -Wno-pmf-conversions has not been specified,
     convert_member_func_to_ptr will issue an error message.  */
  if ((TYPE_PTRMEMFUNC_P (intype)
       || TREE_CODE (intype) == METHOD_TYPE)
      && TYPE_PTR_P (type)
      && (TREE_CODE (TREE_TYPE (type)) == FUNCTION_TYPE
	  || VOID_TYPE_P (TREE_TYPE (type))))
    return convert_member_func_to_ptr (type, expr);

  /* If the cast is not to a reference type, the lvalue-to-rvalue,
     array-to-pointer, and function-to-pointer conversions are
     performed.  */
  expr = decay_conversion (expr);

  /* build_c_cast puts on a NOP_EXPR to make the result not an lvalue.
     Strip such NOP_EXPRs if VALUE is being used in non-lvalue context.  */
  if (TREE_CODE (expr) == NOP_EXPR
      && TREE_TYPE (expr) == TREE_TYPE (TREE_OPERAND (expr, 0)))
    expr = TREE_OPERAND (expr, 0);

  if (error_operand_p (expr))
    return error_mark_node;

  intype = TREE_TYPE (expr);

  /* [expr.reinterpret.cast]
     A pointer can be converted to any integral type large enough to
     hold it.  */
  if (CP_INTEGRAL_TYPE_P (type) && TYPE_PTR_P (intype))
    {
      if (TYPE_PRECISION (type) < TYPE_PRECISION (intype))
	pedwarn ("cast from %qT to %qT loses precision",
		 intype, type);
    }
  /* [expr.reinterpret.cast]
     A value of integral or enumeration type can be explicitly
     converted to a pointer.  */
  else if (TYPE_PTR_P (type) && INTEGRAL_OR_ENUMERATION_TYPE_P (intype))
    /* OK */
    ;
  /* APPLE LOCAL begin blocks 6040305 (ck) */
  else if (TREE_CODE (type) == INTEGER_TYPE && TREE_CODE (intype) == BLOCK_POINTER_TYPE)
    {
      if (TYPE_PRECISION (type) < TYPE_PRECISION (intype))
	pedwarn ("cast from %qT to %qT loses precision",
		 intype, type);
    }
  else if (TREE_CODE (type) == BLOCK_POINTER_TYPE && TREE_CODE (intype) == INTEGER_TYPE)
    /* OK */
    ;
  else if (TREE_CODE (type) == BLOCK_POINTER_TYPE && TREE_CODE (intype) == BLOCK_POINTER_TYPE)
    /* OK */
    ;
  else if (TREE_CODE (intype) == BLOCK_POINTER_TYPE
	   && (objc_is_id (type)
	       || (TREE_CODE (type) == POINTER_TYPE && VOID_TYPE_P (TREE_TYPE (type)))))
    /* OK */
    ;
  else if (TREE_CODE (type) == BLOCK_POINTER_TYPE
	   && TREE_CODE (intype) == POINTER_TYPE
	   && (objc_is_id (intype) || VOID_TYPE_P (TREE_TYPE (intype))))
    /* OK */
    ;
  /* APPLE LOCAL end blocks 6040305 (ck) */
  else if ((TYPE_PTRFN_P (type) && TYPE_PTRFN_P (intype))
	   || (TYPE_PTRMEMFUNC_P (type) && TYPE_PTRMEMFUNC_P (intype)))
    return fold_if_not_in_template (build_nop (type, expr));
  else if ((TYPE_PTRMEM_P (type) && TYPE_PTRMEM_P (intype))
	   || (TYPE_PTROBV_P (type) && TYPE_PTROBV_P (intype)))
    {
      tree sexpr = expr;

      if (!c_cast_p)
	check_for_casting_away_constness (intype, type, error,
					  "reinterpret_cast");
      /* Warn about possible alignment problems.  */
      if (STRICT_ALIGNMENT && warn_cast_align
	  && !VOID_TYPE_P (type)
	  && TREE_CODE (TREE_TYPE (intype)) != FUNCTION_TYPE
	  && COMPLETE_TYPE_P (TREE_TYPE (type))
	  && COMPLETE_TYPE_P (TREE_TYPE (intype))
	  && TYPE_ALIGN (TREE_TYPE (type)) > TYPE_ALIGN (TREE_TYPE (intype)))
	warning (0, "cast from %qT to %qT increases required alignment of "
		 "target type",
		 intype, type);

      /* We need to strip nops here, because the frontend likes to
	 create (int *)&a for array-to-pointer decay, instead of &a[0].  */
      STRIP_NOPS (sexpr);
      if (warn_strict_aliasing <= 2)
	strict_aliasing_warning (intype, type, sexpr);

      return fold_if_not_in_template (build_nop (type, expr));
    }
  else if ((TYPE_PTRFN_P (type) && TYPE_PTROBV_P (intype))
	   || (TYPE_PTRFN_P (intype) && TYPE_PTROBV_P (type)))
    {
      if (pedantic)
	/* Only issue a warning, as we have always supported this
	   where possible, and it is necessary in some cases.  DR 195
	   addresses this issue, but as of 2004/10/26 is still in
	   drafting.  */
	warning (0, "ISO C++ forbids casting between pointer-to-function and pointer-to-object");
      return fold_if_not_in_template (build_nop (type, expr));
    }
  else if (TREE_CODE (type) == VECTOR_TYPE)
    return fold_if_not_in_template (convert_to_vector (type, expr));
  else if (TREE_CODE (intype) == VECTOR_TYPE && INTEGRAL_TYPE_P (type))
    return fold_if_not_in_template (convert_to_integer (type, expr));
  else
    {
      if (valid_p)
	*valid_p = false;
      error ("invalid cast from type %qT to type %qT", intype, type);
      return error_mark_node;
    }

  /* APPLE LOCAL begin don't sign-extend pointers cast to integers */
  if (TREE_CODE (type) == INTEGER_TYPE
      && TREE_CODE (intype) == POINTER_TYPE
      && TYPE_PRECISION (type) > TYPE_PRECISION (intype)
      && TYPE_UNSIGNED (type))
    expr = cp_convert (c_common_type_for_size (POINTER_SIZE, 1), expr);
  /* APPLE LOCAL end don't sign-extend pointers cast to integers */

  return cp_convert (type, expr);
}