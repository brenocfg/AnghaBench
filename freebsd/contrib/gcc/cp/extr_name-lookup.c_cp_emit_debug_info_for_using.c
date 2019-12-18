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
 scalar_t__ BASELINK_FUNCTIONS (scalar_t__) ; 
 scalar_t__ BASELINK_P (scalar_t__) ; 
 scalar_t__ DECL_BUILT_IN (scalar_t__) ; 
 scalar_t__ DECL_EXTERNAL (scalar_t__) ; 
 scalar_t__ FUNCTION_DECL ; 
 scalar_t__ NULL_TREE ; 
 scalar_t__ OVL_CURRENT (scalar_t__) ; 
 scalar_t__ OVL_NEXT (scalar_t__) ; 
 scalar_t__ TEMPLATE_DECL ; 
 scalar_t__ TREE_CODE (scalar_t__) ; 
 TYPE_1__* debug_hooks ; 
 scalar_t__ errorcount ; 
 scalar_t__ global_namespace ; 
 scalar_t__ sorrycount ; 
 int /*<<< orphan*/  stub1 (scalar_t__,scalar_t__) ; 

void
cp_emit_debug_info_for_using (tree t, tree context)
{
  /* Don't try to emit any debug information if we have errors.  */
  if (sorrycount || errorcount)
    return;

  /* Ignore this FUNCTION_DECL if it refers to a builtin declaration
     of a builtin function.  */
  if (TREE_CODE (t) == FUNCTION_DECL
      && DECL_EXTERNAL (t)
      && DECL_BUILT_IN (t))
    return;

  /* Do not supply context to imported_module_or_decl, if
     it is a global namespace.  */
  if (context == global_namespace)
    context = NULL_TREE;

  if (BASELINK_P (t))
    t = BASELINK_FUNCTIONS (t);

  /* FIXME: Handle TEMPLATE_DECLs.  */
  for (t = OVL_CURRENT (t); t; t = OVL_NEXT (t))
    if (TREE_CODE (t) != TEMPLATE_DECL)
      (*debug_hooks->imported_module_or_decl) (t, context);
}