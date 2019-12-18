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
 scalar_t__ NAMESPACE_DECL ; 
 scalar_t__ TREE_CODE (scalar_t__) ; 
 scalar_t__ current_scope () ; 
 scalar_t__ current_template_parms ; 
 int /*<<< orphan*/  error (char*,...) ; 

__attribute__((used)) static bool
check_specialization_scope (void)
{
  tree scope = current_scope ();

  /* [temp.expl.spec]

     An explicit specialization shall be declared in the namespace of
     which the template is a member, or, for member templates, in the
     namespace of which the enclosing class or enclosing class
     template is a member.  An explicit specialization of a member
     function, member class or static data member of a class template
     shall be declared in the namespace of which the class template
     is a member.  */
  if (scope && TREE_CODE (scope) != NAMESPACE_DECL)
    {
      error ("explicit specialization in non-namespace scope %qD", scope);
      return false;
    }

  /* [temp.expl.spec]

     In an explicit specialization declaration for a member of a class
     template or a member template that appears in namespace scope,
     the member template and some of its enclosing class templates may
     remain unspecialized, except that the declaration shall not
     explicitly specialize a class member template if its enclosing
     class templates are not explicitly specialized as well.  */
  if (current_template_parms)
    {
      error ("enclosing class templates are not explicitly specialized");
      return false;
    }

  return true;
}