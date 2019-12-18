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
struct mem_ref {scalar_t__ write_p; struct mem_ref* next; } ;

/* Variables and functions */
 int /*<<< orphan*/  READ_CAN_USE_WRITE_PREFETCH ; 
 int /*<<< orphan*/  WRITE_CAN_USE_READ_PREFETCH ; 
 int /*<<< orphan*/  prune_ref_by_group_reuse (struct mem_ref*,struct mem_ref*,int) ; 
 int /*<<< orphan*/  prune_ref_by_self_reuse (struct mem_ref*) ; 

__attribute__((used)) static void
prune_ref_by_reuse (struct mem_ref *ref, struct mem_ref *refs)
{
  struct mem_ref *prune_by;
  bool before = true;

  prune_ref_by_self_reuse (ref);

  for (prune_by = refs; prune_by; prune_by = prune_by->next)
    {
      if (prune_by == ref)
	{
	  before = false;
	  continue;
	}

      if (!WRITE_CAN_USE_READ_PREFETCH
	  && ref->write_p
	  && !prune_by->write_p)
	continue;
      if (!READ_CAN_USE_WRITE_PREFETCH
	  && !ref->write_p
	  && prune_by->write_p)
	continue;

      prune_ref_by_group_reuse (ref, prune_by, before);
    }
}