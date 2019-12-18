#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int allocated_small; TYPE_3__* bstats; int /*<<< orphan*/  nrequests_small; int /*<<< orphan*/  ndalloc_small; int /*<<< orphan*/  nmalloc_small; int /*<<< orphan*/  hstats; int /*<<< orphan*/  lstats; int /*<<< orphan*/  astats; int /*<<< orphan*/  pdirty; int /*<<< orphan*/  pactive; int /*<<< orphan*/  lg_dirty_mult; int /*<<< orphan*/  dss; } ;
typedef  TYPE_1__ ctl_arena_stats_t ;
typedef  int /*<<< orphan*/  arena_t ;
struct TYPE_5__ {int curregs; scalar_t__ nrequests; scalar_t__ ndalloc; scalar_t__ nmalloc; } ;

/* Variables and functions */
 unsigned int NBINS ; 
 int /*<<< orphan*/  arena_stats_merge (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int index2size (unsigned int) ; 

__attribute__((used)) static void
ctl_arena_stats_amerge(ctl_arena_stats_t *cstats, arena_t *arena)
{
	unsigned i;

	arena_stats_merge(arena, &cstats->dss, &cstats->lg_dirty_mult,
	    &cstats->pactive, &cstats->pdirty, &cstats->astats, cstats->bstats,
	    cstats->lstats, cstats->hstats);

	for (i = 0; i < NBINS; i++) {
		cstats->allocated_small += cstats->bstats[i].curregs *
		    index2size(i);
		cstats->nmalloc_small += cstats->bstats[i].nmalloc;
		cstats->ndalloc_small += cstats->bstats[i].ndalloc;
		cstats->nrequests_small += cstats->bstats[i].nrequests;
	}
}