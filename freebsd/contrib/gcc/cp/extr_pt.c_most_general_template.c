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

/* Variables and functions */
 scalar_t__ CLASSTYPE_TEMPLATE_SPECIALIZATION (scalar_t__) ; 
 scalar_t__ CLASS_TYPE_P (scalar_t__) ; 
 scalar_t__ DECL_CONTEXT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DECL_NAMESPACE_SCOPE_P (int /*<<< orphan*/ ) ; 
 scalar_t__ DECL_TEMPLATE_INFO (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DECL_TI_TEMPLATE (int /*<<< orphan*/ ) ; 
 scalar_t__ FUNCTION_DECL ; 
 int /*<<< orphan*/  NULL_TREE ; 
 scalar_t__ TEMPLATE_DECL ; 
 scalar_t__ TREE_CODE (int /*<<< orphan*/ ) ; 
 scalar_t__ TREE_TYPE (int /*<<< orphan*/ ) ; 

tree
most_general_template (tree decl)
{
  /* If DECL is a FUNCTION_DECL, find the TEMPLATE_DECL of which it is
     an immediate specialization.  */
  if (TREE_CODE (decl) == FUNCTION_DECL)
    {
      if (DECL_TEMPLATE_INFO (decl)) {
	decl = DECL_TI_TEMPLATE (decl);

	/* The DECL_TI_TEMPLATE can be an IDENTIFIER_NODE for a
	   template friend.  */
	if (TREE_CODE (decl) != TEMPLATE_DECL)
	  return NULL_TREE;
      } else
	return NULL_TREE;
    }

  /* Look for more and more general templates.  */
  while (DECL_TEMPLATE_INFO (decl))
    {
      /* The DECL_TI_TEMPLATE can be an IDENTIFIER_NODE in some cases.
	 (See cp-tree.h for details.)  */
      if (TREE_CODE (DECL_TI_TEMPLATE (decl)) != TEMPLATE_DECL)
	break;

      if (CLASS_TYPE_P (TREE_TYPE (decl))
	  && CLASSTYPE_TEMPLATE_SPECIALIZATION (TREE_TYPE (decl)))
	break;

      /* Stop if we run into an explicitly specialized class template.  */
      if (!DECL_NAMESPACE_SCOPE_P (decl)
	  && DECL_CONTEXT (decl)
	  && CLASSTYPE_TEMPLATE_SPECIALIZATION (DECL_CONTEXT (decl)))
	break;

      decl = DECL_TI_TEMPLATE (decl);
    }

  return decl;
}