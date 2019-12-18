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
struct cp_binding_level {scalar_t__ kind; struct cp_binding_level* level_chain; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLASS_TYPE_P (scalar_t__) ; 
 scalar_t__ CP_DECL_CONTEXT (scalar_t__) ; 
 scalar_t__ NAMESPACE_DECL ; 
 int /*<<< orphan*/  NAMESPACE_LEVEL (scalar_t__) ; 
 scalar_t__ TREE_CODE (scalar_t__) ; 
 scalar_t__ TYPE_NAME (scalar_t__) ; 
 struct cp_binding_level* current_binding_level ; 
 scalar_t__ current_namespace ; 
 int /*<<< orphan*/  pushclass (scalar_t__) ; 
 int /*<<< orphan*/  resume_scope (int /*<<< orphan*/ ) ; 
 scalar_t__ sk_template_parms ; 

__attribute__((used)) static void
push_inner_scope_r (tree outer, tree inner)
{
  tree prev;

  if (outer == inner
      || (TREE_CODE (inner) != NAMESPACE_DECL && !CLASS_TYPE_P (inner)))
    return;

  prev = CP_DECL_CONTEXT (TREE_CODE (inner) == NAMESPACE_DECL ? inner : TYPE_NAME (inner));
  if (outer != prev)
    push_inner_scope_r (outer, prev);
  if (TREE_CODE (inner) == NAMESPACE_DECL)
    {
      struct cp_binding_level *save_template_parm = 0;
      /* Temporary take out template parameter scopes.  They are saved
	 in reversed order in save_template_parm.  */
      while (current_binding_level->kind == sk_template_parms)
	{
	  struct cp_binding_level *b = current_binding_level;
	  current_binding_level = b->level_chain;
	  b->level_chain = save_template_parm;
	  save_template_parm = b;
	}

      resume_scope (NAMESPACE_LEVEL (inner));
      current_namespace = inner;

      /* Restore template parameter scopes.  */
      while (save_template_parm)
	{
	  struct cp_binding_level *b = save_template_parm;
	  save_template_parm = b->level_chain;
	  b->level_chain = current_binding_level;
	  current_binding_level = b;
	}
    }
  else
    pushclass (inner);
}