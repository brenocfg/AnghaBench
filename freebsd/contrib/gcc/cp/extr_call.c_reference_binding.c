#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ tree ;
typedef  int cp_lvalue_kind ;
struct TYPE_13__ {TYPE_1__* next; } ;
struct TYPE_14__ {int need_temporary_p; TYPE_2__ u; } ;
typedef  TYPE_3__ conversion ;
struct TYPE_12__ {int check_copy_constructor_p; } ;

/* Variables and functions */
 scalar_t__ CLASS_TYPE_P (scalar_t__) ; 
 int /*<<< orphan*/  CP_TYPE_CONST_NON_VOLATILE_P (scalar_t__) ; 
 scalar_t__ FUNCTION_TYPE ; 
 int LOOKUP_CONSTRUCTOR_CALLABLE ; 
 int LOOKUP_NO_CONVERSION ; 
 int LOOKUP_NO_TEMP_BIND ; 
 scalar_t__ REFERENCE_TYPE ; 
 scalar_t__ TREE_CODE (scalar_t__) ; 
 scalar_t__ TREE_TYPE (scalar_t__) ; 
 int /*<<< orphan*/  TYPE_PACKED (scalar_t__) ; 
 int /*<<< orphan*/  at_least_as_qualified_p (scalar_t__,scalar_t__) ; 
 TYPE_3__* build_conv (int /*<<< orphan*/ ,scalar_t__,TYPE_3__*) ; 
 TYPE_3__* build_identity_conv (scalar_t__,scalar_t__) ; 
 scalar_t__ build_qualified_type (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ck_ref_bind ; 
 int clk_bitfield ; 
 int clk_none ; 
 int clk_ordinary ; 
 int clk_packed ; 
 TYPE_3__* convert_class_to_reference (scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  cp_type_quals (scalar_t__) ; 
 TYPE_3__* direct_reference_binding (scalar_t__,TYPE_3__*) ; 
 scalar_t__ error_mark_node ; 
 TYPE_3__* implicit_conversion (scalar_t__,scalar_t__,scalar_t__,int,int) ; 
 scalar_t__ instantiate_type (scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 int real_lvalue_p (scalar_t__) ; 
 int reference_compatible_p (scalar_t__,scalar_t__) ; 
 int reference_related_p (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  tf_none ; 
 scalar_t__ type_unknown_p (scalar_t__) ; 

__attribute__((used)) static conversion *
reference_binding (tree rto, tree rfrom, tree expr, bool c_cast_p, int flags)
{
  conversion *conv = NULL;
  tree to = TREE_TYPE (rto);
  tree from = rfrom;
  bool related_p;
  bool compatible_p;
  cp_lvalue_kind lvalue_p = clk_none;

  if (TREE_CODE (to) == FUNCTION_TYPE && expr && type_unknown_p (expr))
    {
      expr = instantiate_type (to, expr, tf_none);
      if (expr == error_mark_node)
	return NULL;
      from = TREE_TYPE (expr);
    }

  if (TREE_CODE (from) == REFERENCE_TYPE)
    {
      /* Anything with reference type is an lvalue.  */
      lvalue_p = clk_ordinary;
      from = TREE_TYPE (from);
    }
  else if (expr)
    lvalue_p = real_lvalue_p (expr);

  /* Figure out whether or not the types are reference-related and
     reference compatible.  We have do do this after stripping
     references from FROM.  */
  related_p = reference_related_p (to, from);
  /* If this is a C cast, first convert to an appropriately qualified
     type, so that we can later do a const_cast to the desired type.  */
  if (related_p && c_cast_p
      && !at_least_as_qualified_p (to, from))
    to = build_qualified_type (to, cp_type_quals (from));
  compatible_p = reference_compatible_p (to, from);

  if (lvalue_p && compatible_p)
    {
      /* [dcl.init.ref]

	 If the initializer expression

	 -- is an lvalue (but not an lvalue for a bit-field), and "cv1 T1"
	    is reference-compatible with "cv2 T2,"

	 the reference is bound directly to the initializer expression
	 lvalue.  */
      conv = build_identity_conv (from, expr);
      conv = direct_reference_binding (rto, conv);
      if ((lvalue_p & clk_bitfield) != 0
	  || ((lvalue_p & clk_packed) != 0 && !TYPE_PACKED (to)))
	/* For the purposes of overload resolution, we ignore the fact
	   this expression is a bitfield or packed field. (In particular,
	   [over.ics.ref] says specifically that a function with a
	   non-const reference parameter is viable even if the
	   argument is a bitfield.)

	   However, when we actually call the function we must create
	   a temporary to which to bind the reference.  If the
	   reference is volatile, or isn't const, then we cannot make
	   a temporary, so we just issue an error when the conversion
	   actually occurs.  */
	conv->need_temporary_p = true;

      return conv;
    }
  else if (CLASS_TYPE_P (from) && !(flags & LOOKUP_NO_CONVERSION))
    {
      /* [dcl.init.ref]

	 If the initializer expression

	 -- has a class type (i.e., T2 is a class type) can be
	    implicitly converted to an lvalue of type "cv3 T3," where
	    "cv1 T1" is reference-compatible with "cv3 T3".  (this
	    conversion is selected by enumerating the applicable
	    conversion functions (_over.match.ref_) and choosing the
	    best one through overload resolution.  (_over.match_).

	the reference is bound to the lvalue result of the conversion
	in the second case.  */
      conv = convert_class_to_reference (to, from, expr);
      if (conv)
	return conv;
    }

  /* From this point on, we conceptually need temporaries, even if we
     elide them.  Only the cases above are "direct bindings".  */
  if (flags & LOOKUP_NO_TEMP_BIND)
    return NULL;

  /* [over.ics.rank]

     When a parameter of reference type is not bound directly to an
     argument expression, the conversion sequence is the one required
     to convert the argument expression to the underlying type of the
     reference according to _over.best.ics_.  Conceptually, this
     conversion sequence corresponds to copy-initializing a temporary
     of the underlying type with the argument expression.  Any
     difference in top-level cv-qualification is subsumed by the
     initialization itself and does not constitute a conversion.  */

  /* [dcl.init.ref]

     Otherwise, the reference shall be to a non-volatile const type.  */
  if (!CP_TYPE_CONST_NON_VOLATILE_P (to))
    return NULL;

  /* [dcl.init.ref]

     If the initializer expression is an rvalue, with T2 a class type,
     and "cv1 T1" is reference-compatible with "cv2 T2", the reference
     is bound in one of the following ways:

     -- The reference is bound to the object represented by the rvalue
	or to a sub-object within that object.

     -- ...

     We use the first alternative.  The implicit conversion sequence
     is supposed to be same as we would obtain by generating a
     temporary.  Fortunately, if the types are reference compatible,
     then this is either an identity conversion or the derived-to-base
     conversion, just as for direct binding.  */
  if (CLASS_TYPE_P (from) && compatible_p)
    {
      conv = build_identity_conv (from, expr);
      conv = direct_reference_binding (rto, conv);
      if (!(flags & LOOKUP_CONSTRUCTOR_CALLABLE))
	conv->u.next->check_copy_constructor_p = true;
      return conv;
    }

  /* [dcl.init.ref]

     Otherwise, a temporary of type "cv1 T1" is created and
     initialized from the initializer expression using the rules for a
     non-reference copy initialization.  If T1 is reference-related to
     T2, cv1 must be the same cv-qualification as, or greater
     cv-qualification than, cv2; otherwise, the program is ill-formed.  */
  if (related_p && !at_least_as_qualified_p (to, from))
    return NULL;

  conv = implicit_conversion (to, from, expr, c_cast_p,
			      flags);
  if (!conv)
    return NULL;

  conv = build_conv (ck_ref_bind, rto, conv);
  /* This reference binding, unlike those above, requires the
     creation of a temporary.  */
  conv->need_temporary_p = true;

  return conv;
}