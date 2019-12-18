#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ tree ;
typedef  enum tree_code { ____Placeholder_tree_code } tree_code ;
struct TYPE_7__ {TYPE_2__* next; } ;
struct TYPE_8__ {scalar_t__ kind; scalar_t__ rank; int bad_p; int base_p; int need_temporary_p; TYPE_1__ u; } ;
typedef  TYPE_2__ conversion ;

/* Variables and functions */
 scalar_t__ ARITHMETIC_TYPE_P (scalar_t__) ; 
 int ARRAY_TYPE ; 
 int BLOCK_POINTER_TYPE ; 
 int BOOLEAN_TYPE ; 
 scalar_t__ COMPLETE_TYPE_P (scalar_t__) ; 
 int COMPLEX_TYPE ; 
 scalar_t__ DERIVED_FROM_P (scalar_t__,scalar_t__) ; 
 int ENUMERAL_TYPE ; 
 int FUNCTION_TYPE ; 
 int INTEGER_TYPE ; 
 scalar_t__ INTEGRAL_CODE_P (int) ; 
 scalar_t__ IS_AGGR_TYPE (scalar_t__) ; 
 int LOOKUP_CONSTRUCTOR_CALLABLE ; 
 scalar_t__ NULL_TREE ; 
 int POINTER_TYPE ; 
 int REAL_TYPE ; 
 scalar_t__ REFERENCE_TYPE ; 
 int /*<<< orphan*/  TREE_CHAIN (int /*<<< orphan*/ ) ; 
 int TREE_CODE (scalar_t__) ; 
 scalar_t__ TREE_TYPE (scalar_t__) ; 
 scalar_t__ TREE_VALUE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TYPE_ARG_TYPES (scalar_t__) ; 
 scalar_t__ TYPE_PTRFN_P (scalar_t__) ; 
 scalar_t__ TYPE_PTRMEMFUNC_FN_TYPE (scalar_t__) ; 
 scalar_t__ TYPE_PTRMEMFUNC_P (scalar_t__) ; 
 scalar_t__ TYPE_PTRMEM_CLASS_TYPE (scalar_t__) ; 
 scalar_t__ TYPE_PTRMEM_P (scalar_t__) ; 
 scalar_t__ TYPE_PTRMEM_POINTED_TO_TYPE (scalar_t__) ; 
 scalar_t__ TYPE_PTR_TO_MEMBER_P (scalar_t__) ; 
 int VECTOR_TYPE ; 
 scalar_t__ VOID_TYPE_P (scalar_t__) ; 
 TYPE_2__* build_conv (scalar_t__,scalar_t__,TYPE_2__*) ; 
 TYPE_2__* build_identity_conv (scalar_t__,scalar_t__) ; 
 scalar_t__ build_method_type_directly (scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ build_pointer_type (scalar_t__) ; 
 scalar_t__ build_ptrmem_type (scalar_t__,scalar_t__) ; 
 scalar_t__ build_ptrmemfunc_type (scalar_t__) ; 
 scalar_t__ ck_base ; 
 scalar_t__ ck_lvalue ; 
 scalar_t__ ck_pmem ; 
 scalar_t__ ck_ptr ; 
 scalar_t__ ck_qual ; 
 scalar_t__ ck_rvalue ; 
 scalar_t__ ck_std ; 
 scalar_t__ comp_ptr_ttypes (scalar_t__,scalar_t__) ; 
 scalar_t__ comp_ptr_ttypes_const (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  compparms (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ cp_build_qualified_type (scalar_t__,scalar_t__) ; 
 scalar_t__ cp_type_quals (scalar_t__) ; 
 scalar_t__ cr_pbool ; 
 scalar_t__ cr_promotion ; 
 scalar_t__ error_mark_node ; 
 scalar_t__ instantiate_type (scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ is_bitfield_expr_with_lowered_type (scalar_t__) ; 
 scalar_t__ is_properly_derived_from (scalar_t__,scalar_t__) ; 
 scalar_t__ lvalue_p (scalar_t__) ; 
 scalar_t__ non_reference (scalar_t__) ; 
 scalar_t__ null_ptr_cst_p (scalar_t__) ; 
 scalar_t__ ptr_reasonably_similar (scalar_t__,scalar_t__) ; 
 scalar_t__ same_type_ignoring_top_level_qualifiers_p (scalar_t__,scalar_t__) ; 
 scalar_t__ same_type_p (scalar_t__,scalar_t__) ; 
 scalar_t__ string_conv_p (scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ strip_top_quals (scalar_t__) ; 
 int /*<<< orphan*/  tf_conv ; 
 scalar_t__ type_decays_to (scalar_t__) ; 
 scalar_t__ type_promotes_to (scalar_t__) ; 
 scalar_t__ type_unknown_p (scalar_t__) ; 
 scalar_t__ vector_types_convertible_p (scalar_t__,scalar_t__,int) ; 
 scalar_t__ void_type_node ; 

__attribute__((used)) static conversion *
standard_conversion (tree to, tree from, tree expr, bool c_cast_p,
		     int flags)
{
  enum tree_code fcode, tcode;
  conversion *conv;
  bool fromref = false;

  to = non_reference (to);
  if (TREE_CODE (from) == REFERENCE_TYPE)
    {
      fromref = true;
      from = TREE_TYPE (from);
    }
  to = strip_top_quals (to);
  from = strip_top_quals (from);

  if ((TYPE_PTRFN_P (to) || TYPE_PTRMEMFUNC_P (to))
      && expr && type_unknown_p (expr))
    {
      expr = instantiate_type (to, expr, tf_conv);
      if (expr == error_mark_node)
	return NULL;
      from = TREE_TYPE (expr);
    }

  fcode = TREE_CODE (from);
  tcode = TREE_CODE (to);

  conv = build_identity_conv (from, expr);
  if (fcode == FUNCTION_TYPE || fcode == ARRAY_TYPE)
    {
      from = type_decays_to (from);
      fcode = TREE_CODE (from);
      conv = build_conv (ck_lvalue, from, conv);
    }
  else if (fromref || (expr && lvalue_p (expr)))
    {
      if (expr)
	{
	  tree bitfield_type;
	  bitfield_type = is_bitfield_expr_with_lowered_type (expr);
	  if (bitfield_type)
	    {
	      from = strip_top_quals (bitfield_type);
	      fcode = TREE_CODE (from);
	    }
	}
      conv = build_conv (ck_rvalue, from, conv);
    }

   /* Allow conversion between `__complex__' data types.  */
  if (tcode == COMPLEX_TYPE && fcode == COMPLEX_TYPE)
    {
      /* The standard conversion sequence to convert FROM to TO is
	 the standard conversion sequence to perform componentwise
	 conversion.  */
      conversion *part_conv = standard_conversion
	(TREE_TYPE (to), TREE_TYPE (from), NULL_TREE, c_cast_p, flags);

      if (part_conv)
	{
	  conv = build_conv (part_conv->kind, to, conv);
	  conv->rank = part_conv->rank;
	}
      else
	conv = NULL;

      return conv;
    }

  if (same_type_p (from, to))
    return conv;

  /* APPLE LOCAL blocks 6040305 (ck) */
  if ((tcode == POINTER_TYPE || tcode == BLOCK_POINTER_TYPE || TYPE_PTR_TO_MEMBER_P (to))
      && expr && null_ptr_cst_p (expr))
    conv = build_conv (ck_std, to, conv);
  else if ((tcode == INTEGER_TYPE && fcode == POINTER_TYPE)
	   || (tcode == POINTER_TYPE && fcode == INTEGER_TYPE))
    {
      /* For backwards brain damage compatibility, allow interconversion of
	 pointers and integers with a pedwarn.  */
      conv = build_conv (ck_std, to, conv);
      conv->bad_p = true;
    }
  else if (tcode == ENUMERAL_TYPE && fcode == INTEGER_TYPE)
    {
      /* For backwards brain damage compatibility, allow interconversion of
	 enums and integers with a pedwarn.  */
      conv = build_conv (ck_std, to, conv);
      conv->bad_p = true;
    }
  else if ((tcode == POINTER_TYPE && fcode == POINTER_TYPE)
	   || (TYPE_PTRMEM_P (to) && TYPE_PTRMEM_P (from)))
    {
      tree to_pointee;
      tree from_pointee;

      if (tcode == POINTER_TYPE
	  && same_type_ignoring_top_level_qualifiers_p (TREE_TYPE (from),
							TREE_TYPE (to)))
	;
      else if (VOID_TYPE_P (TREE_TYPE (to))
	       && !TYPE_PTRMEM_P (from)
	       && TREE_CODE (TREE_TYPE (from)) != FUNCTION_TYPE)
	{
	  from = build_pointer_type
	    (cp_build_qualified_type (void_type_node,
				      cp_type_quals (TREE_TYPE (from))));
	  conv = build_conv (ck_ptr, from, conv);
	}
      else if (TYPE_PTRMEM_P (from))
	{
	  tree fbase = TYPE_PTRMEM_CLASS_TYPE (from);
	  tree tbase = TYPE_PTRMEM_CLASS_TYPE (to);

	  if (DERIVED_FROM_P (fbase, tbase)
	      && (same_type_ignoring_top_level_qualifiers_p
		  (TYPE_PTRMEM_POINTED_TO_TYPE (from),
		   TYPE_PTRMEM_POINTED_TO_TYPE (to))))
	    {
	      from = build_ptrmem_type (tbase,
					TYPE_PTRMEM_POINTED_TO_TYPE (from));
	      conv = build_conv (ck_pmem, from, conv);
	    }
	  else if (!same_type_p (fbase, tbase))
	    return NULL;
	}
      else if (IS_AGGR_TYPE (TREE_TYPE (from))
	       && IS_AGGR_TYPE (TREE_TYPE (to))
	       /* [conv.ptr]

		  An rvalue of type "pointer to cv D," where D is a
		  class type, can be converted to an rvalue of type
		  "pointer to cv B," where B is a base class (clause
		  _class.derived_) of D.  If B is an inaccessible
		  (clause _class.access_) or ambiguous
		  (_class.member.lookup_) base class of D, a program
		  that necessitates this conversion is ill-formed.
		  Therefore, we use DERIVED_FROM_P, and do not check
		  access or uniqueness.  */
	       && DERIVED_FROM_P (TREE_TYPE (to), TREE_TYPE (from))
	       /* If FROM is not yet complete, then we must be parsing
		  the body of a class.  We know what's derived from
		  what, but we can't actually perform a
		  derived-to-base conversion.  For example, in:

		     struct D : public B { 
                       static const int i = sizeof((B*)(D*)0);
                     };

                  the D*-to-B* conversion is a reinterpret_cast, not a
		  static_cast.  */
	       && COMPLETE_TYPE_P (TREE_TYPE (from)))
	{
	  from =
	    cp_build_qualified_type (TREE_TYPE (to),
				     cp_type_quals (TREE_TYPE (from)));
	  from = build_pointer_type (from);
	  conv = build_conv (ck_ptr, from, conv);
	  conv->base_p = true;
	}

      if (tcode == POINTER_TYPE)
	{
	  to_pointee = TREE_TYPE (to);
	  from_pointee = TREE_TYPE (from);
	}
      else
	{
	  to_pointee = TYPE_PTRMEM_POINTED_TO_TYPE (to);
	  from_pointee = TYPE_PTRMEM_POINTED_TO_TYPE (from);
	}

      if (same_type_p (from, to))
	/* OK */;
      else if (c_cast_p && comp_ptr_ttypes_const (to, from))
	/* In a C-style cast, we ignore CV-qualification because we
	   are allowed to perform a static_cast followed by a
	   const_cast.  */
	conv = build_conv (ck_qual, to, conv);
      else if (!c_cast_p && comp_ptr_ttypes (to_pointee, from_pointee))
	conv = build_conv (ck_qual, to, conv);
      else if (expr && string_conv_p (to, expr, 0))
	/* converting from string constant to char *.  */
	conv = build_conv (ck_qual, to, conv);
      else if (ptr_reasonably_similar (to_pointee, from_pointee))
	{
	  conv = build_conv (ck_ptr, to, conv);
	  conv->bad_p = true;
	}
      else
	return NULL;

      from = to;
    }
  else if (TYPE_PTRMEMFUNC_P (to) && TYPE_PTRMEMFUNC_P (from))
    {
      tree fromfn = TREE_TYPE (TYPE_PTRMEMFUNC_FN_TYPE (from));
      tree tofn = TREE_TYPE (TYPE_PTRMEMFUNC_FN_TYPE (to));
      tree fbase = TREE_TYPE (TREE_VALUE (TYPE_ARG_TYPES (fromfn)));
      tree tbase = TREE_TYPE (TREE_VALUE (TYPE_ARG_TYPES (tofn)));

      if (!DERIVED_FROM_P (fbase, tbase)
	  || !same_type_p (TREE_TYPE (fromfn), TREE_TYPE (tofn))
	  || !compparms (TREE_CHAIN (TYPE_ARG_TYPES (fromfn)),
			 TREE_CHAIN (TYPE_ARG_TYPES (tofn)))
	  || cp_type_quals (fbase) != cp_type_quals (tbase))
	return NULL;

      from = cp_build_qualified_type (tbase, cp_type_quals (fbase));
      from = build_method_type_directly (from,
					 TREE_TYPE (fromfn),
					 TREE_CHAIN (TYPE_ARG_TYPES (fromfn)));
      from = build_ptrmemfunc_type (build_pointer_type (from));
      conv = build_conv (ck_pmem, from, conv);
      conv->base_p = true;
    }
  else if (tcode == BOOLEAN_TYPE)
    {
      /* [conv.bool]

	  An rvalue of arithmetic, enumeration, pointer, or pointer to
	  member type can be converted to an rvalue of type bool.  */
      if (ARITHMETIC_TYPE_P (from)
	  || fcode == ENUMERAL_TYPE
	  || fcode == POINTER_TYPE
	  /* APPLE LOCAL blocks 6040305 (cl) */
	  || fcode == BLOCK_POINTER_TYPE
	  || TYPE_PTR_TO_MEMBER_P (from))
	{
	  conv = build_conv (ck_std, to, conv);
	  if (fcode == POINTER_TYPE
	      || TYPE_PTRMEM_P (from)
	      || (TYPE_PTRMEMFUNC_P (from)
		  && conv->rank < cr_pbool))
	    conv->rank = cr_pbool;
	  return conv;
	}

      return NULL;
    }
  /* We don't check for ENUMERAL_TYPE here because there are no standard
     conversions to enum type.  */
  else if (tcode == INTEGER_TYPE || tcode == BOOLEAN_TYPE
	   || tcode == REAL_TYPE)
    {
      if (! (INTEGRAL_CODE_P (fcode) || fcode == REAL_TYPE))
	return NULL;
      conv = build_conv (ck_std, to, conv);

      /* Give this a better rank if it's a promotion.  */
      if (same_type_p (to, type_promotes_to (from))
	  && conv->u.next->rank <= cr_promotion)
	conv->rank = cr_promotion;
    }
  else if (fcode == VECTOR_TYPE && tcode == VECTOR_TYPE
	   && vector_types_convertible_p (from, to, false))
    return build_conv (ck_std, to, conv);
  else if (!(flags & LOOKUP_CONSTRUCTOR_CALLABLE)
	   && IS_AGGR_TYPE (to) && IS_AGGR_TYPE (from)
	   && is_properly_derived_from (from, to))
    {
      if (conv->kind == ck_rvalue)
	conv = conv->u.next;
      conv = build_conv (ck_base, to, conv);
      /* The derived-to-base conversion indicates the initialization
	 of a parameter with base type from an object of a derived
	 type.  A temporary object is created to hold the result of
	 the conversion.  */
      conv->need_temporary_p = true;
    }
  else
    return NULL;

  return conv;
}