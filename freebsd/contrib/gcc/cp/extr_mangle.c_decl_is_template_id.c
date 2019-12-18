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
 scalar_t__ CLASSTYPE_TEMPLATE_ID_P (int /*<<< orphan*/  const) ; 
 scalar_t__ CLASS_TYPE_P (int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/ * DECL_LANG_SPECIFIC (int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  DECL_TEMPLATE_INFO (int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  DECL_TI_TEMPLATE (int /*<<< orphan*/  const) ; 
 scalar_t__ DECL_USE_TEMPLATE (int /*<<< orphan*/  const) ; 
 scalar_t__ PRIMARY_TEMPLATE_P (int /*<<< orphan*/ ) ; 
 scalar_t__ TEMPLATE_DECL ; 
 scalar_t__ TREE_CODE (int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  TREE_TYPE (int /*<<< orphan*/  const) ; 
 scalar_t__ TYPE_DECL ; 
 int /*<<< orphan*/  TYPE_TEMPLATE_INFO (int /*<<< orphan*/  const) ; 

__attribute__((used)) static int
decl_is_template_id (const tree decl, tree* const template_info)
{
  if (TREE_CODE (decl) == TYPE_DECL)
    {
      /* TYPE_DECLs are handled specially.  Look at its type to decide
	 if this is a template instantiation.  */
      const tree type = TREE_TYPE (decl);

      if (CLASS_TYPE_P (type) && CLASSTYPE_TEMPLATE_ID_P (type))
	{
	  if (template_info != NULL)
	    /* For a templated TYPE_DECL, the template info is hanging
	       off the type.  */
	    *template_info = TYPE_TEMPLATE_INFO (type);
	  return 1;
	}
    }
  else
    {
      /* Check if this is a primary template.  */
      if (DECL_LANG_SPECIFIC (decl) != NULL
	  && DECL_USE_TEMPLATE (decl)
	  && PRIMARY_TEMPLATE_P (DECL_TI_TEMPLATE (decl))
	  && TREE_CODE (decl) != TEMPLATE_DECL)
	{
	  if (template_info != NULL)
	    /* For most templated decls, the template info is hanging
	       off the decl.  */
	    *template_info = DECL_TEMPLATE_INFO (decl);
	  return 1;
	}
    }

  /* It's not a template id.  */
  return 0;
}