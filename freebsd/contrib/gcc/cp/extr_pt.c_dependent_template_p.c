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
 int /*<<< orphan*/  CP_DECL_CONTEXT (scalar_t__) ; 
 int /*<<< orphan*/  DECL_CONTEXT (scalar_t__) ; 
 scalar_t__ DECL_TEMPLATE_TEMPLATE_PARM_P (scalar_t__) ; 
 scalar_t__ IDENTIFIER_NODE ; 
 scalar_t__ OVERLOAD ; 
 scalar_t__ OVL_CHAIN (scalar_t__) ; 
 scalar_t__ OVL_FUNCTION (scalar_t__) ; 
 scalar_t__ SCOPE_REF ; 
 scalar_t__ TEMPLATE_TEMPLATE_PARM ; 
 scalar_t__ TREE_CODE (scalar_t__) ; 
 scalar_t__ TYPE_P (int /*<<< orphan*/ ) ; 
 int dependent_type_p (int /*<<< orphan*/ ) ; 

bool
dependent_template_p (tree tmpl)
{
  if (TREE_CODE (tmpl) == OVERLOAD)
    {
      while (tmpl)
	{
	  if (dependent_template_p (OVL_FUNCTION (tmpl)))
	    return true;
	  tmpl = OVL_CHAIN (tmpl);
	}
      return false;
    }

  /* Template template parameters are dependent.  */
  if (DECL_TEMPLATE_TEMPLATE_PARM_P (tmpl)
      || TREE_CODE (tmpl) == TEMPLATE_TEMPLATE_PARM)
    return true;
  /* So are names that have not been looked up.  */
  if (TREE_CODE (tmpl) == SCOPE_REF
      || TREE_CODE (tmpl) == IDENTIFIER_NODE)
    return true;
  /* So are member templates of dependent classes.  */
  if (TYPE_P (CP_DECL_CONTEXT (tmpl)))
    return dependent_type_p (DECL_CONTEXT (tmpl));
  return false;
}