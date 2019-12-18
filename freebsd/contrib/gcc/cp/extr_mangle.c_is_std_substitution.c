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
typedef  int /*<<< orphan*/ * tree ;
typedef  size_t substitution_identifier_index_t ;

/* Variables and functions */
 scalar_t__ CLASS_TYPE_P (int /*<<< orphan*/ * const) ; 
 int /*<<< orphan*/  CP_DECL_CONTEXT (int /*<<< orphan*/ *) ; 
 scalar_t__ DECL_NAME (int /*<<< orphan*/ ) ; 
 scalar_t__ DECL_NAMESPACE_STD_P (int /*<<< orphan*/ ) ; 
 scalar_t__ DECL_P (int /*<<< orphan*/ * const) ; 
 int /*<<< orphan*/ * TREE_TYPE (int /*<<< orphan*/ * const) ; 
 scalar_t__ TYPE_LANG_SPECIFIC (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * TYPE_NAME (int /*<<< orphan*/ * const) ; 
 scalar_t__ TYPE_TEMPLATE_INFO (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TYPE_TI_TEMPLATE (int /*<<< orphan*/ *) ; 
 scalar_t__* subst_identifiers ; 

__attribute__((used)) static inline int
is_std_substitution (const tree node,
		     const substitution_identifier_index_t index)
{
  tree type = NULL;
  tree decl = NULL;

  if (DECL_P (node))
    {
      type = TREE_TYPE (node);
      decl = node;
    }
  else if (CLASS_TYPE_P (node))
    {
      type = node;
      decl = TYPE_NAME (node);
    }
  else
    /* These are not the droids you're looking for.  */
    return 0;

  return (DECL_NAMESPACE_STD_P (CP_DECL_CONTEXT (decl))
	  && TYPE_LANG_SPECIFIC (type)
	  && TYPE_TEMPLATE_INFO (type)
	  && (DECL_NAME (TYPE_TI_TEMPLATE (type))
	      == subst_identifiers[index]));
}