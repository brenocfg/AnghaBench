#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct function {TYPE_1__* eh; } ;
struct eh_region {int region_number; struct eh_region* next_peer; struct eh_region* outer; struct eh_region* inner; scalar_t__ may_contain_throw; } ;
struct TYPE_6__ {TYPE_2__* eh; } ;
struct TYPE_5__ {int /*<<< orphan*/  region_array; } ;
struct TYPE_4__ {int last_region_number; struct eh_region* region_tree; } ;

/* Variables and functions */
 struct eh_region* VEC_index (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 TYPE_3__* cfun ; 
 int /*<<< orphan*/  dump_eh_tree (int /*<<< orphan*/ ,struct function*) ; 
 int /*<<< orphan*/  eh_region ; 
 int /*<<< orphan*/  error (char*,...) ; 
 int /*<<< orphan*/  internal_error (char*) ; 
 int /*<<< orphan*/  stderr ; 

void
verify_eh_tree (struct function *fun)
{
  struct eh_region *i, *outer = NULL;
  bool err = false;
  int nvisited = 0;
  int count = 0;
  int j;
  int depth = 0;

  i = fun->eh->region_tree;
  if (! i)
    return;
  for (j = fun->eh->last_region_number; j > 0; --j)
    if ((i = VEC_index (eh_region, cfun->eh->region_array, j)))
      {
	count++;
	if (i->region_number != j)
	  {
	    error ("region_array is corrupted for region %i", i->region_number);
	    err = true;
	  }
      }

  while (1)
    {
      if (VEC_index (eh_region, cfun->eh->region_array, i->region_number) != i)
	{
	  error ("region_array is corrupted for region %i", i->region_number);
	  err = true;
	}
      if (i->outer != outer)
	{
	  error ("outer block of region %i is wrong", i->region_number);
	  err = true;
	}
      if (i->may_contain_throw && outer && !outer->may_contain_throw)
	{
	  error ("region %i may contain throw and is contained in region that may not",
		 i->region_number);
	  err = true;
	}
      if (depth < 0)
	{
	  error ("negative nesting depth of region %i", i->region_number);
	  err = true;
	}
      nvisited ++;
      /* If there are sub-regions, process them.  */
      if (i->inner)
	outer = i, i = i->inner, depth++;
      /* If there are peers, process them.  */
      else if (i->next_peer)
	i = i->next_peer;
      /* Otherwise, step back up the tree to the next peer.  */
      else
	{
	  do {
	    i = i->outer;
	    depth--;
	    if (i == NULL)
	      {
		if (depth != -1)
		  {
		    error ("tree list ends on depth %i", depth + 1);
		    err = true;
		  }
		if (count != nvisited)
		  {
		    error ("array does not match the region tree");
		    err = true;
		  }
		if (err)
		  {
		    dump_eh_tree (stderr, fun);
		    internal_error ("verify_eh_tree failed");
		  }
	        return;
	      }
	    outer = i->outer;
	  } while (i->next_peer == NULL);
	  i = i->next_peer;
	}
    }
}