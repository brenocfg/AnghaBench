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
typedef  scalar_t__ rtx ;
typedef  TYPE_3__* location_chain ;
struct TYPE_15__ {int /*<<< orphan*/  vars; } ;
typedef  TYPE_4__ dataflow_set ;
struct TYPE_14__ {scalar_t__ loc; struct TYPE_14__* next; } ;
struct TYPE_13__ {int refcount; int n_var_parts; TYPE_1__* var_part; } ;
struct TYPE_12__ {TYPE_3__* loc_chain; scalar_t__ cur_loc; } ;
typedef  int /*<<< orphan*/  HOST_WIDE_INT ;

/* Variables and functions */
 int /*<<< orphan*/  NO_INSERT ; 
 scalar_t__ REGNO (scalar_t__) ; 
 scalar_t__ REG_P (scalar_t__) ; 
 int /*<<< orphan*/  VARIABLE_HASH_VAL (int /*<<< orphan*/ ) ; 
 int find_variable_location_part (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 void** htab_find_slot_with_hash (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  loc_chain_pool ; 
 int /*<<< orphan*/  pool_free (int /*<<< orphan*/ ,TYPE_3__*) ; 
 scalar_t__ rtx_equal_p (scalar_t__,scalar_t__) ; 
 TYPE_2__* unshare_variable (TYPE_4__*,TYPE_2__*) ; 
 int /*<<< orphan*/  variable_was_changed (TYPE_2__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
delete_variable_part (dataflow_set *set, rtx loc, tree decl,
		      HOST_WIDE_INT offset)
{
  void **slot;
    
  slot = htab_find_slot_with_hash (set->vars, decl, VARIABLE_HASH_VAL (decl),
				   NO_INSERT);
  if (slot)
    {
      variable var = (variable) *slot;
      int pos = find_variable_location_part (var, offset, NULL);

      if (pos >= 0)
	{
	  location_chain node, next;
	  location_chain *nextp;
	  bool changed;

	  if (var->refcount > 1)
	    {
	      /* If the variable contains the location part we have to
		 make a copy of the variable.  */
	      for (node = var->var_part[pos].loc_chain; node;
		   node = node->next)
		{
		  if ((REG_P (node->loc) && REG_P (loc)
		       && REGNO (node->loc) == REGNO (loc))
		      || rtx_equal_p (node->loc, loc))
		    {
		      var = unshare_variable (set, var);
		      break;
		    }
		}
	    }

	  /* Delete the location part.  */
	  nextp = &var->var_part[pos].loc_chain;
	  for (node = *nextp; node; node = next)
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

	  /* If we have deleted the location which was last emitted
	     we have to emit new location so add the variable to set
	     of changed variables.  */
	  if (var->var_part[pos].cur_loc
	      && ((REG_P (loc)
		   && REG_P (var->var_part[pos].cur_loc)
		   && REGNO (loc) == REGNO (var->var_part[pos].cur_loc))
		  || rtx_equal_p (loc, var->var_part[pos].cur_loc)))
	    {
	      changed = true;
	      if (var->var_part[pos].loc_chain)
		var->var_part[pos].cur_loc = var->var_part[pos].loc_chain->loc;
	    }
	  else
	    changed = false;

	  if (var->var_part[pos].loc_chain == NULL)
	    {
	      var->n_var_parts--;
	      while (pos < var->n_var_parts)
		{
		  var->var_part[pos] = var->var_part[pos + 1];
		  pos++;
		}
	    }
	  if (changed)
	    variable_was_changed (var, set->vars);
	}
    }
}