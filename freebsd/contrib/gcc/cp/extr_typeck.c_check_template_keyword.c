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
 scalar_t__ BASELINK_FUNCTIONS (scalar_t__) ; 
 scalar_t__ BASELINK_P (scalar_t__) ; 
 int /*<<< orphan*/  DECL_TI_TEMPLATE (scalar_t__) ; 
 scalar_t__ DECL_USE_TEMPLATE (scalar_t__) ; 
 scalar_t__ FUNCTION_DECL ; 
 scalar_t__ OVL_CURRENT (scalar_t__) ; 
 scalar_t__ OVL_NEXT (scalar_t__) ; 
 scalar_t__ PRIMARY_TEMPLATE_P (int /*<<< orphan*/ ) ; 
 scalar_t__ TEMPLATE_DECL ; 
 scalar_t__ TEMPLATE_ID_EXPR ; 
 scalar_t__ TREE_CODE (scalar_t__) ; 
 int /*<<< orphan*/  is_overloaded_fn (scalar_t__) ; 
 int /*<<< orphan*/  pedwarn (char*,scalar_t__) ; 

void
check_template_keyword (tree decl)
{
  /* The standard says:

      [temp.names]

      If a name prefixed by the keyword template is not a member
      template, the program is ill-formed.

     DR 228 removed the restriction that the template be a member
     template.

     DR 96, if accepted would add the further restriction that explicit
     template arguments must be provided if the template keyword is
     used, but, as of 2005-10-16, that DR is still in "drafting".  If
     this DR is accepted, then the semantic checks here can be
     simplified, as the entity named must in fact be a template
     specialization, rather than, as at present, a set of overloaded
     functions containing at least one template function.  */
  if (TREE_CODE (decl) != TEMPLATE_DECL
      && TREE_CODE (decl) != TEMPLATE_ID_EXPR)
    {
      if (!is_overloaded_fn (decl))
	pedwarn ("%qD is not a template", decl);
      else
	{
	  tree fns;
	  fns = decl;
	  if (BASELINK_P (fns))
	    fns = BASELINK_FUNCTIONS (fns);
	  while (fns)
	    {
	      tree fn = OVL_CURRENT (fns);
	      if (TREE_CODE (fn) == TEMPLATE_DECL
		  || TREE_CODE (fn) == TEMPLATE_ID_EXPR)
		break;
	      if (TREE_CODE (fn) == FUNCTION_DECL
		  && DECL_USE_TEMPLATE (fn)
		  && PRIMARY_TEMPLATE_P (DECL_TI_TEMPLATE (fn)))
		break;
	      fns = OVL_NEXT (fns);
	    }
	  if (!fns)
	    pedwarn ("%qD is not a template", decl);
	}
    }
}