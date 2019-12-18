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
typedef  scalar_t__ tree ;
struct TYPE_2__ {int /*<<< orphan*/  (* imported_module_or_decl ) (scalar_t__,scalar_t__) ;} ;

/* Variables and functions */
 scalar_t__ NAMESPACE_DECL ; 
 scalar_t__ NULL_TREE ; 
 scalar_t__ ORIGINAL_NAMESPACE (scalar_t__) ; 
 scalar_t__ TREE_CODE (scalar_t__) ; 
 int /*<<< orphan*/  USING_STMT ; 
 int /*<<< orphan*/  add_stmt (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  add_using_namespace (scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  build_stmt (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ building_stmt_tree () ; 
 scalar_t__ current_namespace ; 
 scalar_t__ current_scope () ; 
 TYPE_1__* debug_hooks ; 
 scalar_t__ error_mark_node ; 
 int /*<<< orphan*/  gcc_assert (int) ; 
 scalar_t__ global_namespace ; 
 int /*<<< orphan*/  processing_template_decl ; 
 int /*<<< orphan*/  push_using_directive (scalar_t__) ; 
 int /*<<< orphan*/  stub1 (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  toplevel_bindings_p () ; 

void
do_using_directive (tree namespace)
{
  tree context = NULL_TREE;

  if (namespace == error_mark_node)
    return;

  gcc_assert (TREE_CODE (namespace) == NAMESPACE_DECL);

  if (building_stmt_tree ())
    add_stmt (build_stmt (USING_STMT, namespace));
  namespace = ORIGINAL_NAMESPACE (namespace);

  if (!toplevel_bindings_p ())
    {
      push_using_directive (namespace);
      context = current_scope ();
    }
  else
    {
      /* direct usage */
      add_using_namespace (current_namespace, namespace, 0);
      if (current_namespace != global_namespace)
	context = current_namespace;
    }

  /* Emit debugging info.  */
  if (!processing_template_decl)
    (*debug_hooks->imported_module_or_decl) (namespace, context);
}