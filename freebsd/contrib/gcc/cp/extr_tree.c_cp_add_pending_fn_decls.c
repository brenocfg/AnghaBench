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
typedef  int /*<<< orphan*/  varray_type ;
typedef  scalar_t__ tree ;
struct saved_scope {scalar_t__ function_decl; struct saved_scope* prev; } ;

/* Variables and functions */
 int /*<<< orphan*/  VARRAY_PUSH_TREE (int /*<<< orphan*/ ,scalar_t__) ; 
 struct saved_scope* scope_chain ; 

tree
cp_add_pending_fn_decls (void* fns_p, tree prev_fn)
{
  varray_type *fnsp = (varray_type *)fns_p;
  struct saved_scope *s;

  for (s = scope_chain; s; s = s->prev)
    if (s->function_decl && s->function_decl != prev_fn)
      {
	VARRAY_PUSH_TREE (*fnsp, s->function_decl);
	prev_fn = s->function_decl;
      }

  return prev_fn;
}