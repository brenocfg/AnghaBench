#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_2__* variable ;
typedef  TYPE_3__* location_chain ;
struct TYPE_11__ {int /*<<< orphan*/  vars; } ;
typedef  TYPE_4__ dataflow_set ;
struct TYPE_10__ {int /*<<< orphan*/ * loc; struct TYPE_10__* next; } ;
struct TYPE_9__ {int refcount; int n_var_parts; int /*<<< orphan*/  decl; TYPE_1__* var_part; } ;
struct TYPE_8__ {int /*<<< orphan*/ * cur_loc; TYPE_3__* loc_chain; int /*<<< orphan*/  offset; } ;

/* Variables and functions */
 int /*<<< orphan*/  INSERT ; 
 int /*<<< orphan*/  VARIABLE_HASH_VAL (int /*<<< orphan*/ ) ; 
 void** htab_find_slot_with_hash (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  loc_chain_pool ; 
 void* pool_alloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  var_pool ; 

__attribute__((used)) static variable
unshare_variable (dataflow_set *set, variable var)
{
  void **slot;
  variable new_var;
  int i;

  new_var = pool_alloc (var_pool);
  new_var->decl = var->decl;
  new_var->refcount = 1;
  var->refcount--;
  new_var->n_var_parts = var->n_var_parts;

  for (i = 0; i < var->n_var_parts; i++)
    {
      location_chain node;
      location_chain *nextp;

      new_var->var_part[i].offset = var->var_part[i].offset;
      nextp = &new_var->var_part[i].loc_chain;
      for (node = var->var_part[i].loc_chain; node; node = node->next)
	{
	  location_chain new_lc;

	  new_lc = pool_alloc (loc_chain_pool);
	  new_lc->next = NULL;
	  new_lc->loc = node->loc;

	  *nextp = new_lc;
	  nextp = &new_lc->next;
	}

      /* We are at the basic block boundary when copying variable description
	 so set the CUR_LOC to be the first element of the chain.  */
      if (new_var->var_part[i].loc_chain)
	new_var->var_part[i].cur_loc = new_var->var_part[i].loc_chain->loc;
      else
	new_var->var_part[i].cur_loc = NULL;
    }

  slot = htab_find_slot_with_hash (set->vars, new_var->decl,
				   VARIABLE_HASH_VAL (new_var->decl),
				   INSERT);
  *slot = new_var;
  return new_var;
}