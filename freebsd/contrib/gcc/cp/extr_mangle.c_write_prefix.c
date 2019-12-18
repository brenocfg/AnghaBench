#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/ * tree ;
struct TYPE_2__ {int need_abi_warning; } ;

/* Variables and functions */
 scalar_t__ CLASSTYPE_TEMPLATE_ID_P (int /*<<< orphan*/ * const) ; 
 int /*<<< orphan*/ * CP_DECL_CONTEXT (int /*<<< orphan*/ *) ; 
 scalar_t__ DECL_P (int /*<<< orphan*/ * const) ; 
 scalar_t__ FUNCTION_DECL ; 
 TYPE_1__ G ; 
 int /*<<< orphan*/  MANGLE_TRACE_TREE (char*,int /*<<< orphan*/ * const) ; 
 scalar_t__ TEMPLATE_TYPE_PARM ; 
 int /*<<< orphan*/  TI_ARGS (int /*<<< orphan*/ *) ; 
 scalar_t__ TREE_CODE (int /*<<< orphan*/ * const) ; 
 int /*<<< orphan*/ * TYPE_NAME (int /*<<< orphan*/ * const) ; 
 int /*<<< orphan*/ * TYPE_TEMPLATE_INFO (int /*<<< orphan*/ * const) ; 
 scalar_t__ abi_version_at_least (int) ; 
 int /*<<< orphan*/  add_substitution (int /*<<< orphan*/ * const) ; 
 int /*<<< orphan*/  decl_is_template_id (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 scalar_t__ find_substitution (int /*<<< orphan*/ * const) ; 
 int /*<<< orphan*/ * const global_namespace ; 
 int /*<<< orphan*/  write_template_args (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_template_param (int /*<<< orphan*/ * const) ; 
 int /*<<< orphan*/  write_template_prefix (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_unqualified_name (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
write_prefix (const tree node)
{
  tree decl;
  /* Non-NULL if NODE represents a template-id.  */
  tree template_info = NULL;

  MANGLE_TRACE_TREE ("prefix", node);

  if (node == NULL
      || node == global_namespace)
    return;

  if (find_substitution (node))
    return;

  if (DECL_P (node))
    {
      /* If this is a function decl, that means we've hit function
	 scope, so this prefix must be for a local name.  In this
	 case, we're under the <local-name> production, which encodes
	 the enclosing function scope elsewhere.  So don't continue
	 here.  */
      if (TREE_CODE (node) == FUNCTION_DECL)
	return;

      decl = node;
      decl_is_template_id (decl, &template_info);
    }
  else
    {
      /* Node is a type.  */
      decl = TYPE_NAME (node);
      if (CLASSTYPE_TEMPLATE_ID_P (node))
	template_info = TYPE_TEMPLATE_INFO (node);
    }

  /* In G++ 3.2, the name of the template parameter was used.  */
  if (TREE_CODE (node) == TEMPLATE_TYPE_PARM
      && !abi_version_at_least (2))
    G.need_abi_warning = true;

  if (TREE_CODE (node) == TEMPLATE_TYPE_PARM
      && abi_version_at_least (2))
    write_template_param (node);
  else if (template_info != NULL)
    /* Templated.  */
    {
      write_template_prefix (decl);
      write_template_args (TI_ARGS (template_info));
    }
  else
    /* Not templated.  */
    {
      write_prefix (CP_DECL_CONTEXT (decl));
      write_unqualified_name (decl);
    }

  add_substitution (node);
}