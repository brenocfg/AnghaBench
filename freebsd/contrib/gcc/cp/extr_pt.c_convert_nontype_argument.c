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
typedef  char* tree ;

/* Variables and functions */
 scalar_t__ ADDR_EXPR ; 
 scalar_t__ ARRAY_TYPE ; 
 int /*<<< orphan*/  CONV_IMPLICIT ; 
 int /*<<< orphan*/  DECL_EXTERNAL_LINKAGE_P (char*) ; 
 scalar_t__ DECL_P (char*) ; 
 scalar_t__ DECL_TEMPLATE_PARM_P (char*) ; 
 scalar_t__ INTEGER_CST ; 
 scalar_t__ INTEGRAL_TYPE_P (char*) ; 
 int /*<<< orphan*/  LOOKUP_PROTECT ; 
 scalar_t__ NOP_EXPR ; 
 char* NULL_TREE ; 
 scalar_t__ POINTER_TYPE ; 
 scalar_t__ REFERENCE_TYPE ; 
 scalar_t__ STRING_CST ; 
 int /*<<< orphan*/  STRIP_NOPS (char*) ; 
 scalar_t__ TREE_CODE (char*) ; 
 char* TREE_OPERAND (char*,int /*<<< orphan*/ ) ; 
 char* TREE_TYPE (char*) ; 
 scalar_t__ TYPE_PTRFN_P (char*) ; 
 scalar_t__ TYPE_PTRMEMFUNC_P (char*) ; 
 scalar_t__ TYPE_PTRMEM_P (char*) ; 
 scalar_t__ TYPE_PTROBV_P (char*) ; 
 scalar_t__ TYPE_REFFN_P (char*) ; 
 scalar_t__ TYPE_REF_OBJ_P (char*) ; 
 scalar_t__ VAR_DECL ; 
 int /*<<< orphan*/  at_least_as_qualified_p (char*,char*) ; 
 int /*<<< orphan*/  build_address (char*) ; 
 char* build_nop (char*,int /*<<< orphan*/ ) ; 
 int can_convert (char*,char*) ; 
 char* convert_nontype_argument_function (char*,char*) ; 
 char* decay_conversion (char*) ; 
 int /*<<< orphan*/  error (char*,char*,char*,...) ; 
 char* error_mark_node ; 
 scalar_t__ error_operand_p (char*) ; 
 char* fold (char*) ; 
 char* fold_decl_constant_value (char*) ; 
 char* fold_non_dependent_expr (char*) ; 
 int /*<<< orphan*/  gcc_assert (int) ; 
 int /*<<< orphan*/  gcc_unreachable () ; 
 int /*<<< orphan*/  inform (char*,...) ; 
 char* instantiate_type (char*,char*,int /*<<< orphan*/ ) ; 
 char* ocp_convert (char*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* perform_qualification_conversions (char*,char*) ; 
 int /*<<< orphan*/  real_lvalue_p (char*) ; 
 int same_type_ignoring_top_level_qualifiers_p (char*,char*) ; 
 int same_type_p (char*,char*) ; 
 int /*<<< orphan*/  tf_none ; 
 int /*<<< orphan*/  type_unknown_p (char*) ; 

__attribute__((used)) static tree
convert_nontype_argument (tree type, tree expr)
{
  tree expr_type;

  /* Detect immediately string literals as invalid non-type argument.
     This special-case is not needed for correctness (we would easily
     catch this later), but only to provide better diagnostic for this
     common user mistake. As suggested by DR 100, we do not mention
     linkage issues in the diagnostic as this is not the point.  */
  if (TREE_CODE (expr) == STRING_CST)
    {
      error ("%qE is not a valid template argument for type %qT "
	     "because string literals can never be used in this context",
	     expr, type);
      return NULL_TREE;
    }

  /* If we are in a template, EXPR may be non-dependent, but still
     have a syntactic, rather than semantic, form.  For example, EXPR
     might be a SCOPE_REF, rather than the VAR_DECL to which the
     SCOPE_REF refers.  Preserving the qualifying scope is necessary
     so that access checking can be performed when the template is
     instantiated -- but here we need the resolved form so that we can
     convert the argument.  */
  expr = fold_non_dependent_expr (expr);
  if (error_operand_p (expr))
    return error_mark_node;
  expr_type = TREE_TYPE (expr);

  /* HACK: Due to double coercion, we can get a
     NOP_EXPR<REFERENCE_TYPE>(ADDR_EXPR<POINTER_TYPE> (arg)) here,
     which is the tree that we built on the first call (see
     below when coercing to reference to object or to reference to
     function). We just strip everything and get to the arg.
     See g++.old-deja/g++.oliva/template4.C and g++.dg/template/nontype9.C
     for examples.  */
  if (TREE_CODE (expr) == NOP_EXPR)
    {
      if (TYPE_REF_OBJ_P (type) || TYPE_REFFN_P (type))
	{
	  /* ??? Maybe we could use convert_from_reference here, but we
	     would need to relax its constraints because the NOP_EXPR
	     could actually change the type to something more cv-qualified,
	     and this is not folded by convert_from_reference.  */
	  tree addr = TREE_OPERAND (expr, 0);
	  gcc_assert (TREE_CODE (expr_type) == REFERENCE_TYPE);
	  gcc_assert (TREE_CODE (addr) == ADDR_EXPR);
	  gcc_assert (TREE_CODE (TREE_TYPE (addr)) == POINTER_TYPE);
	  gcc_assert (same_type_ignoring_top_level_qualifiers_p
		      (TREE_TYPE (expr_type),
		       TREE_TYPE (TREE_TYPE (addr))));

	  expr = TREE_OPERAND (addr, 0);
	  expr_type = TREE_TYPE (expr);
	}

      /* We could also generate a NOP_EXPR(ADDR_EXPR()) when the
	 parameter is a pointer to object, through decay and
	 qualification conversion. Let's strip everything.  */
      else if (TYPE_PTROBV_P (type))
	{
	  STRIP_NOPS (expr);
	  gcc_assert (TREE_CODE (expr) == ADDR_EXPR);
	  gcc_assert (TREE_CODE (TREE_TYPE (expr)) == POINTER_TYPE);
	  /* Skip the ADDR_EXPR only if it is part of the decay for
	     an array. Otherwise, it is part of the original argument
	     in the source code.  */
	  if (TREE_CODE (TREE_TYPE (TREE_OPERAND (expr, 0))) == ARRAY_TYPE)
	    expr = TREE_OPERAND (expr, 0);
	  expr_type = TREE_TYPE (expr);
	}
    }

  /* [temp.arg.nontype]/5, bullet 1

     For a non-type template-parameter of integral or enumeration type,
     integral promotions (_conv.prom_) and integral conversions
     (_conv.integral_) are applied.  */
  if (INTEGRAL_TYPE_P (type))
    {
      if (!INTEGRAL_TYPE_P (expr_type))
	return error_mark_node;

      expr = fold_decl_constant_value (expr);
      /* Notice that there are constant expressions like '4 % 0' which
	 do not fold into integer constants.  */
      if (TREE_CODE (expr) != INTEGER_CST)
	{
	  error ("%qE is not a valid template argument for type %qT "
		 "because it is a non-constant expression", expr, type);
	  return NULL_TREE;
	}

      /* At this point, an implicit conversion does what we want,
	 because we already know that the expression is of integral
	 type.  */
      expr = ocp_convert (type, expr, CONV_IMPLICIT, LOOKUP_PROTECT);
      if (expr == error_mark_node)
	return error_mark_node;

      /* Conversion was allowed: fold it to a bare integer constant.  */
      expr = fold (expr);
    }
  /* [temp.arg.nontype]/5, bullet 2

     For a non-type template-parameter of type pointer to object,
     qualification conversions (_conv.qual_) and the array-to-pointer
     conversion (_conv.array_) are applied.  */
  else if (TYPE_PTROBV_P (type))
    {
      /* [temp.arg.nontype]/1  (TC1 version, DR 49):

	 A template-argument for a non-type, non-template template-parameter
	 shall be one of: [...]

	 -- the name of a non-type template-parameter;
	 -- the address of an object or function with external linkage, [...]
	    expressed as "& id-expression" where the & is optional if the name
	    refers to a function or array, or if the corresponding
	    template-parameter is a reference.

	Here, we do not care about functions, as they are invalid anyway
	for a parameter of type pointer-to-object.  */

      if (DECL_P (expr) && DECL_TEMPLATE_PARM_P (expr))
	/* Non-type template parameters are OK.  */
	;
      else if (TREE_CODE (expr) != ADDR_EXPR
	       && TREE_CODE (expr_type) != ARRAY_TYPE)
	{
	  if (TREE_CODE (expr) == VAR_DECL)
	    {
	      error ("%qD is not a valid template argument "
		     "because %qD is a variable, not the address of "
		     "a variable",
		     expr, expr);
	      return NULL_TREE;
	    }
	  /* Other values, like integer constants, might be valid
	     non-type arguments of some other type.  */
	  return error_mark_node;
	}
      else
	{
	  tree decl;

	  decl = ((TREE_CODE (expr) == ADDR_EXPR)
		  ? TREE_OPERAND (expr, 0) : expr);
	  if (TREE_CODE (decl) != VAR_DECL)
	    {
	      error ("%qE is not a valid template argument of type %qT "
		     "because %qE is not a variable",
		     expr, type, decl);
	      return NULL_TREE;
	    }
	  else if (!DECL_EXTERNAL_LINKAGE_P (decl))
	    {
	      error ("%qE is not a valid template argument of type %qT "
		     "because %qD does not have external linkage",
		     expr, type, decl);
	      return NULL_TREE;
	    }
	}

      expr = decay_conversion (expr);
      if (expr == error_mark_node)
	return error_mark_node;

      expr = perform_qualification_conversions (type, expr);
      if (expr == error_mark_node)
	return error_mark_node;
    }
  /* [temp.arg.nontype]/5, bullet 3

     For a non-type template-parameter of type reference to object, no
     conversions apply. The type referred to by the reference may be more
     cv-qualified than the (otherwise identical) type of the
     template-argument. The template-parameter is bound directly to the
     template-argument, which must be an lvalue.  */
  else if (TYPE_REF_OBJ_P (type))
    {
      if (!same_type_ignoring_top_level_qualifiers_p (TREE_TYPE (type),
						      expr_type))
	return error_mark_node;

      if (!at_least_as_qualified_p (TREE_TYPE (type), expr_type))
	{
	  error ("%qE is not a valid template argument for type %qT "
		 "because of conflicts in cv-qualification", expr, type);
	  return NULL_TREE;
	}

      if (!real_lvalue_p (expr))
	{
	  error ("%qE is not a valid template argument for type %qT "
		 "because it is not an lvalue", expr, type);
	  return NULL_TREE;
	}

      /* [temp.arg.nontype]/1

	 A template-argument for a non-type, non-template template-parameter
	 shall be one of: [...]

	 -- the address of an object or function with external linkage.  */
      if (!DECL_EXTERNAL_LINKAGE_P (expr))
	{
	  error ("%qE is not a valid template argument for type %qT "
		 "because object %qD has not external linkage",
		 expr, type, expr);
	  return NULL_TREE;
	}

      expr = build_nop (type, build_address (expr));
    }
  /* [temp.arg.nontype]/5, bullet 4

     For a non-type template-parameter of type pointer to function, only
     the function-to-pointer conversion (_conv.func_) is applied. If the
     template-argument represents a set of overloaded functions (or a
     pointer to such), the matching function is selected from the set
     (_over.over_).  */
  else if (TYPE_PTRFN_P (type))
    {
      /* If the argument is a template-id, we might not have enough
	 context information to decay the pointer.  */
      if (!type_unknown_p (expr_type))
	{
	  expr = decay_conversion (expr);
	  if (expr == error_mark_node)
	    return error_mark_node;
	}

      expr = convert_nontype_argument_function (type, expr);
      if (!expr || expr == error_mark_node)
	return expr;
    }
  /* [temp.arg.nontype]/5, bullet 5

     For a non-type template-parameter of type reference to function, no
     conversions apply. If the template-argument represents a set of
     overloaded functions, the matching function is selected from the set
     (_over.over_).  */
  else if (TYPE_REFFN_P (type))
    {
      if (TREE_CODE (expr) == ADDR_EXPR)
	{
	  error ("%qE is not a valid template argument for type %qT "
		 "because it is a pointer", expr, type);
	  inform ("try using %qE instead", TREE_OPERAND (expr, 0));
	  return NULL_TREE;
	}

      expr = convert_nontype_argument_function (TREE_TYPE (type), expr);
      if (!expr || expr == error_mark_node)
	return expr;

      expr = build_nop (type, build_address (expr));
    }
  /* [temp.arg.nontype]/5, bullet 6

     For a non-type template-parameter of type pointer to member function,
     no conversions apply. If the template-argument represents a set of
     overloaded member functions, the matching member function is selected
     from the set (_over.over_).  */
  else if (TYPE_PTRMEMFUNC_P (type))
    {
      expr = instantiate_type (type, expr, tf_none);
      if (expr == error_mark_node)
	return error_mark_node;

      /* There is no way to disable standard conversions in
	 resolve_address_of_overloaded_function (called by
	 instantiate_type). It is possible that the call succeeded by
	 converting &B::I to &D::I (where B is a base of D), so we need
	 to reject this conversion here.

	 Actually, even if there was a way to disable standard conversions,
	 it would still be better to reject them here so that we can
	 provide a superior diagnostic.  */
      if (!same_type_p (TREE_TYPE (expr), type))
	{
	  /* Make sure we are just one standard conversion off.  */
	  gcc_assert (can_convert (type, TREE_TYPE (expr)));
	  error ("%qE is not a valid template argument for type %qT "
		 "because it is of type %qT", expr, type,
		 TREE_TYPE (expr));
	  inform ("standard conversions are not allowed in this context");
	  return NULL_TREE;
	}
    }
  /* [temp.arg.nontype]/5, bullet 7

     For a non-type template-parameter of type pointer to data member,
     qualification conversions (_conv.qual_) are applied.  */
  else if (TYPE_PTRMEM_P (type))
    {
      expr = perform_qualification_conversions (type, expr);
      if (expr == error_mark_node)
	return expr;
    }
  /* A template non-type parameter must be one of the above.  */
  else
    gcc_unreachable ();

  /* Sanity check: did we actually convert the argument to the
     right type?  */
  gcc_assert (same_type_p (type, TREE_TYPE (expr)));
  return expr;
}