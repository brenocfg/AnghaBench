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
typedef  scalar_t__ access_kind ;

/* Variables and functions */
 scalar_t__ BINFO_INHERITANCE_CHAIN (scalar_t__) ; 
 scalar_t__ BINFO_TYPE (scalar_t__) ; 
 scalar_t__ DECL_NONSTATIC_MEMBER_P (scalar_t__) ; 
 int /*<<< orphan*/  DERIVED_FROM_P (scalar_t__,scalar_t__) ; 
 scalar_t__ access_in_type (scalar_t__,scalar_t__) ; 
 scalar_t__ ak_none ; 
 scalar_t__ context_for_name_lookup (scalar_t__) ; 

__attribute__((used)) static int
protected_accessible_p (tree decl, tree derived, tree binfo)
{
  access_kind access;

  /* We're checking this clause from [class.access.base]

       m as a member of N is protected, and the reference occurs in a
       member or friend of class N, or in a member or friend of a
       class P derived from N, where m as a member of P is private or
       protected.

    Here DERIVED is a possible P and DECL is m.  accessible_p will
    iterate over various values of N, but the access to m in DERIVED
    does not change.

    Note that I believe that the passage above is wrong, and should read
    "...is private or protected or public"; otherwise you get bizarre results
    whereby a public using-decl can prevent you from accessing a protected
    member of a base.  (jason 2000/02/28)  */

  /* If DERIVED isn't derived from m's class, then it can't be a P.  */
  if (!DERIVED_FROM_P (context_for_name_lookup (decl), derived))
    return 0;

  access = access_in_type (derived, decl);

  /* If m is inaccessible in DERIVED, then it's not a P.  */
  if (access == ak_none)
    return 0;

  /* [class.protected]

     When a friend or a member function of a derived class references
     a protected nonstatic member of a base class, an access check
     applies in addition to those described earlier in clause
     _class.access_) Except when forming a pointer to member
     (_expr.unary.op_), the access must be through a pointer to,
     reference to, or object of the derived class itself (or any class
     derived from that class) (_expr.ref_).  If the access is to form
     a pointer to member, the nested-name-specifier shall name the
     derived class (or any class derived from that class).  */
  if (DECL_NONSTATIC_MEMBER_P (decl))
    {
      /* We can tell through what the reference is occurring by
	 chasing BINFO up to the root.  */
      tree t = binfo;
      while (BINFO_INHERITANCE_CHAIN (t))
	t = BINFO_INHERITANCE_CHAIN (t);

      if (!DERIVED_FROM_P (derived, BINFO_TYPE (t)))
	return 0;
    }

  return 1;
}