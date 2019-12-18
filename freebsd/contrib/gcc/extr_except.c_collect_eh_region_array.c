#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct eh_region {struct eh_region* next_peer; struct eh_region* outer; struct eh_region* inner; int /*<<< orphan*/  region_number; } ;
struct TYPE_4__ {TYPE_1__* eh; } ;
struct TYPE_3__ {int /*<<< orphan*/  region_array; scalar_t__ last_region_number; struct eh_region* region_tree; } ;

/* Variables and functions */
 int /*<<< orphan*/  VEC_replace (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct eh_region*) ; 
 int /*<<< orphan*/  VEC_safe_grow (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 TYPE_2__* cfun ; 
 int /*<<< orphan*/  eh_region ; 
 int /*<<< orphan*/  gc ; 

void
collect_eh_region_array (void)
{
  struct eh_region *i;

  i = cfun->eh->region_tree;
  if (! i)
    return;

  VEC_safe_grow (eh_region, gc, cfun->eh->region_array,
		 cfun->eh->last_region_number + 1);
  VEC_replace (eh_region, cfun->eh->region_array, 0, 0);

  while (1)
    {
      VEC_replace (eh_region, cfun->eh->region_array, i->region_number, i);

      /* If there are sub-regions, process them.  */
      if (i->inner)
	i = i->inner;
      /* If there are peers, process them.  */
      else if (i->next_peer)
	i = i->next_peer;
      /* Otherwise, step back up the tree to the next peer.  */
      else
	{
	  do {
	    i = i->outer;
	    if (i == NULL)
	      return;
	  } while (i->next_peer == NULL);
	  i = i->next_peer;
	}
    }
}