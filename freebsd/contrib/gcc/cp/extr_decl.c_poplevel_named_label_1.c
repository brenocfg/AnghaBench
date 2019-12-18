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
struct named_label_use_entry {int in_omp_scope; scalar_t__ names_in_scope; struct cp_binding_level* binding_level; struct named_label_use_entry* next; } ;
struct named_label_entry {int in_try_scope; int in_catch_scope; int in_omp_scope; struct named_label_use_entry* uses; scalar_t__ names_in_scope; struct cp_binding_level* binding_level; int /*<<< orphan*/  bad_decls; } ;
struct cp_binding_level {int kind; scalar_t__ names; struct cp_binding_level* level_chain; } ;

/* Variables and functions */
 scalar_t__ TREE_CHAIN (scalar_t__) ; 
 scalar_t__ decl_jump_unsafe (scalar_t__) ; 
#define  sk_catch 130 
#define  sk_omp 129 
#define  sk_try 128 
 int /*<<< orphan*/  tree_cons (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
poplevel_named_label_1 (void **slot, void *data)
{
  struct named_label_entry *ent = (struct named_label_entry *) *slot;
  struct cp_binding_level *bl = (struct cp_binding_level *) data;
  struct cp_binding_level *obl = bl->level_chain;

  if (ent->binding_level == bl)
    {
      tree decl;

      for (decl = ent->names_in_scope; decl; decl = TREE_CHAIN (decl))
	if (decl_jump_unsafe (decl))
	  ent->bad_decls = tree_cons (NULL, decl, ent->bad_decls);

      ent->binding_level = obl;
      ent->names_in_scope = obl->names;
      switch (bl->kind)
	{
	case sk_try:
	  ent->in_try_scope = true;
	  break;
	case sk_catch:
	  ent->in_catch_scope = true;
	  break;
	case sk_omp:
	  ent->in_omp_scope = true;
	  break;
	default:
	  break;
	}
    }
  else if (ent->uses)
    {
      struct named_label_use_entry *use;

      for (use = ent->uses; use ; use = use->next)
	if (use->binding_level == bl)
	  {
	    use->binding_level = obl;
	    use->names_in_scope = obl->names;
	    if (bl->kind == sk_omp)
	      use->in_omp_scope = true;
	  }
    }

  return 1;
}