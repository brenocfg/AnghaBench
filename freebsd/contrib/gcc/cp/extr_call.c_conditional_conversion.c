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
typedef  int /*<<< orphan*/  tree ;
typedef  int /*<<< orphan*/  conversion ;

/* Variables and functions */
 scalar_t__ CLASS_TYPE_P (int /*<<< orphan*/ ) ; 
 int DERIVED_FROM_P (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LOOKUP_NORMAL ; 
 int /*<<< orphan*/  LOOKUP_NO_TEMP_BIND ; 
 int /*<<< orphan*/  TREE_TYPE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TYPE_MAIN_VARIANT (int /*<<< orphan*/ ) ; 
 scalar_t__ at_least_as_qualified_p (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * build_conv (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * build_identity_conv (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  build_reference_type (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ck_base ; 
 int /*<<< orphan*/  ck_rvalue ; 
 int /*<<< orphan*/ * implicit_conversion (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  non_reference (int /*<<< orphan*/ ) ; 
 scalar_t__ real_lvalue_p (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  same_type_p (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static conversion *
conditional_conversion (tree e1, tree e2)
{
  tree t1 = non_reference (TREE_TYPE (e1));
  tree t2 = non_reference (TREE_TYPE (e2));
  conversion *conv;
  bool good_base;

  /* [expr.cond]

     If E2 is an lvalue: E1 can be converted to match E2 if E1 can be
     implicitly converted (clause _conv_) to the type "reference to
     T2", subject to the constraint that in the conversion the
     reference must bind directly (_dcl.init.ref_) to E1.  */
  if (real_lvalue_p (e2))
    {
      conv = implicit_conversion (build_reference_type (t2),
				  t1,
				  e1,
				  /*c_cast_p=*/false,
				  LOOKUP_NO_TEMP_BIND);
      if (conv)
	return conv;
    }

  /* [expr.cond]

     If E1 and E2 have class type, and the underlying class types are
     the same or one is a base class of the other: E1 can be converted
     to match E2 if the class of T2 is the same type as, or a base
     class of, the class of T1, and the cv-qualification of T2 is the
     same cv-qualification as, or a greater cv-qualification than, the
     cv-qualification of T1.  If the conversion is applied, E1 is
     changed to an rvalue of type T2 that still refers to the original
     source class object (or the appropriate subobject thereof).  */
  if (CLASS_TYPE_P (t1) && CLASS_TYPE_P (t2)
      && ((good_base = DERIVED_FROM_P (t2, t1)) || DERIVED_FROM_P (t1, t2)))
    {
      if (good_base && at_least_as_qualified_p (t2, t1))
	{
	  conv = build_identity_conv (t1, e1);
	  if (!same_type_p (TYPE_MAIN_VARIANT (t1),
			    TYPE_MAIN_VARIANT (t2)))
	    conv = build_conv (ck_base, t2, conv);
	  else
	    conv = build_conv (ck_rvalue, t2, conv);
	  return conv;
	}
      else
	return NULL;
    }
  else
    /* [expr.cond]

       Otherwise: E1 can be converted to match E2 if E1 can be implicitly
       converted to the type that expression E2 would have if E2 were
       converted to an rvalue (or the type it has, if E2 is an rvalue).  */
    return implicit_conversion (t2, t1, e1, /*c_cast_p=*/false,
				LOOKUP_NORMAL);
}