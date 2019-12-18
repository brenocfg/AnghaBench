#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_2__* variable ;
typedef  int /*<<< orphan*/  tree ;
typedef  void* rtx ;
typedef  TYPE_3__* location_chain ;
struct TYPE_15__ {int /*<<< orphan*/  vars; } ;
typedef  TYPE_4__ dataflow_set ;
struct TYPE_14__ {void* loc; struct TYPE_14__* next; } ;
struct TYPE_13__ {int refcount; int n_var_parts; TYPE_1__* var_part; int /*<<< orphan*/  decl; } ;
struct TYPE_12__ {int /*<<< orphan*/ * cur_loc; TYPE_3__* loc_chain; void* offset; } ;
typedef  void* HOST_WIDE_INT ;

/* Variables and functions */
 int /*<<< orphan*/  INSERT ; 
 int MAX_VAR_PARTS ; 
 scalar_t__ REGNO (void*) ; 
 scalar_t__ REG_P (void*) ; 
 int /*<<< orphan*/  VARIABLE_HASH_VAL (int /*<<< orphan*/ ) ; 
 int find_variable_location_part (TYPE_2__*,void*,int*) ; 
 int /*<<< orphan*/  gcc_assert (int) ; 
 void** htab_find_slot_with_hash (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  loc_chain_pool ; 
 void* pool_alloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pool_free (int /*<<< orphan*/ ,TYPE_3__*) ; 
 scalar_t__ rtx_equal_p (void*,void*) ; 
 TYPE_2__* unshare_variable (TYPE_4__*,TYPE_2__*) ; 
 int /*<<< orphan*/  var_pool ; 
 int /*<<< orphan*/  variable_was_changed (TYPE_2__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
set_variable_part (dataflow_set *set, rtx loc, tree decl, HOST_WIDE_INT offset)
{
  int pos;
  location_chain node, next;
  location_chain *nextp;
  variable var;
  void **slot;
  
  slot = htab_find_slot_with_hash (set->vars, decl,
				   VARIABLE_HASH_VAL (decl), INSERT);
  if (!*slot)
    {
      /* Create new variable information.  */
      var = pool_alloc (var_pool);
      var->decl = decl;
      var->refcount = 1;
      var->n_var_parts = 1;
      var->var_part[0].offset = offset;
      var->var_part[0].loc_chain = NULL;
      var->var_part[0].cur_loc = NULL;
      *slot = var;
      pos = 0;
    }
  else
    {
      int inspos = 0;

      var = (variable) *slot;

      pos = find_variable_location_part (var, offset, &inspos);

      if (pos >= 0)
	{
	  node = var->var_part[pos].loc_chain;

	  if (node
	      && ((REG_P (node->loc) && REG_P (loc)
		   && REGNO (node->loc) == REGNO (loc))
		  || rtx_equal_p (node->loc, loc)))
	    {
	      /* LOC is in the beginning of the chain so we have nothing
		 to do.  */
	      return;
	    }
	  else
	    {
	      /* We have to make a copy of a shared variable.  */
	      if (var->refcount > 1)
		var = unshare_variable (set, var);
	    }
	}
      else
	{
	  /* We have not found the location part, new one will be created.  */

	  /* We have to make a copy of the shared variable.  */
	  if (var->refcount > 1)
	    var = unshare_variable (set, var);

	  /* We track only variables whose size is <= MAX_VAR_PARTS bytes
	     thus there are at most MAX_VAR_PARTS different offsets.  */
	  gcc_assert (var->n_var_parts < MAX_VAR_PARTS);

	  /* We have to move the elements of array starting at index
	     inspos to the next position.  */
	  for (pos = var->n_var_parts; pos > inspos; pos--)
	    var->var_part[pos] = var->var_part[pos - 1];

	  var->n_var_parts++;
	  var->var_part[pos].offset = offset;
	  var->var_part[pos].loc_chain = NULL;
	  var->var_part[pos].cur_loc = NULL;
	}
    }

  /* Delete the location from the list.  */
  nextp = &var->var_part[pos].loc_chain;
  for (node = var->var_part[pos].loc_chain; node; node = next)
    {
      next = node->next;
      if ((REG_P (node->loc) && REG_P (loc)
	   && REGNO (node->loc) == REGNO (loc))
	  || rtx_equal_p (node->loc, loc))
	{
	  pool_free (loc_chain_pool, node);
	  *nextp = next;
	  break;
	}
      else
	nextp = &node->next;
    }

  /* Add the location to the beginning.  */
  node = pool_alloc (loc_chain_pool);
  node->loc = loc;
  node->next = var->var_part[pos].loc_chain;
  var->var_part[pos].loc_chain = node;

  /* If no location was emitted do so.  */
  if (var->var_part[pos].cur_loc == NULL)
    {
      var->var_part[pos].cur_loc = loc;
      variable_was_changed (var, set->vars);
    }
}