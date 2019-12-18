#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_2__* variable ;
typedef  int /*<<< orphan*/  tree ;
typedef  scalar_t__ rtx ;
typedef  TYPE_3__* location_chain ;
struct TYPE_13__ {TYPE_5__** regs; int /*<<< orphan*/  vars; } ;
typedef  TYPE_4__ dataflow_set ;
typedef  TYPE_5__* attrs ;
struct TYPE_14__ {scalar_t__ offset; int /*<<< orphan*/  decl; struct TYPE_14__* next; } ;
struct TYPE_12__ {scalar_t__ loc; struct TYPE_12__* next; } ;
struct TYPE_11__ {TYPE_1__* var_part; } ;
struct TYPE_10__ {TYPE_3__* loc_chain; } ;
typedef  scalar_t__ HOST_WIDE_INT ;

/* Variables and functions */
 int /*<<< orphan*/  DECL_P (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NO_INSERT ; 
 size_t REGNO (scalar_t__) ; 
 scalar_t__ REG_P (scalar_t__) ; 
 int /*<<< orphan*/  VARIABLE_HASH_VAL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  attrs_pool ; 
 int /*<<< orphan*/  delete_variable_part (TYPE_4__*,scalar_t__,int /*<<< orphan*/ ,scalar_t__) ; 
 int find_variable_location_part (TYPE_2__*,scalar_t__,int /*<<< orphan*/ *) ; 
 void** htab_find_slot_with_hash (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pool_free (int /*<<< orphan*/ ,TYPE_5__*) ; 

__attribute__((used)) static void
clobber_variable_part (dataflow_set *set, rtx loc, tree decl,
		      HOST_WIDE_INT offset)
{
  void **slot;

  if (! decl || ! DECL_P (decl))
    return;

  slot = htab_find_slot_with_hash (set->vars, decl, VARIABLE_HASH_VAL (decl),
				   NO_INSERT);
  if (slot)
    {
      variable var = (variable) *slot;
      int pos = find_variable_location_part (var, offset, NULL);

      if (pos >= 0)
	{
	  location_chain node, next;

	  /* Remove the register locations from the dataflow set.  */
	  next = var->var_part[pos].loc_chain;
	  for (node = next; node; node = next)
	    {
	      next = node->next;
	      if (node->loc != loc)
		{
		  if (REG_P (node->loc))
		    {
		      attrs anode, anext;
		      attrs *anextp;

		      /* Remove the variable part from the register's
			 list, but preserve any other variable parts
			 that might be regarded as live in that same
			 register.  */
		      anextp = &set->regs[REGNO (node->loc)];
		      for (anode = *anextp; anode; anode = anext)
			{
			  anext = anode->next;
			  if (anode->decl == decl
			      && anode->offset == offset)
			    {
			      pool_free (attrs_pool, anode);
			      *anextp = anext;
			    }
			}
		    }

		  delete_variable_part (set, node->loc, decl, offset);
		}
	    }
	}
    }
}