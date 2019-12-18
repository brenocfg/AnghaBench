#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {scalar_t__ ndalloc_huge; scalar_t__ nmalloc_huge; scalar_t__ allocated_huge; scalar_t__ nrequests_large; scalar_t__ ndalloc_large; scalar_t__ nmalloc_large; scalar_t__ allocated_large; scalar_t__ metadata_allocated; scalar_t__ metadata_mapped; scalar_t__ purged; scalar_t__ nmadvise; scalar_t__ npurge; scalar_t__ mapped; } ;
struct TYPE_12__ {TYPE_1__* hstats; TYPE_4__* lstats; TYPE_3__* bstats; TYPE_2__ astats; scalar_t__ nrequests_small; scalar_t__ ndalloc_small; scalar_t__ nmalloc_small; scalar_t__ allocated_small; scalar_t__ pdirty; scalar_t__ pactive; } ;
typedef  TYPE_5__ ctl_arena_stats_t ;
struct TYPE_11__ {scalar_t__ curruns; scalar_t__ nrequests; scalar_t__ ndalloc; scalar_t__ nmalloc; } ;
struct TYPE_10__ {scalar_t__ curruns; scalar_t__ reruns; scalar_t__ nruns; scalar_t__ nflushes; scalar_t__ nfills; scalar_t__ curregs; scalar_t__ nrequests; scalar_t__ ndalloc; scalar_t__ nmalloc; } ;
struct TYPE_8__ {scalar_t__ curhchunks; scalar_t__ ndalloc; scalar_t__ nmalloc; } ;

/* Variables and functions */
 unsigned int NBINS ; 
 scalar_t__ config_tcache ; 
 unsigned int nhclasses ; 
 unsigned int nlclasses ; 

__attribute__((used)) static void
ctl_arena_stats_smerge(ctl_arena_stats_t *sstats, ctl_arena_stats_t *astats)
{
	unsigned i;

	sstats->pactive += astats->pactive;
	sstats->pdirty += astats->pdirty;

	sstats->astats.mapped += astats->astats.mapped;
	sstats->astats.npurge += astats->astats.npurge;
	sstats->astats.nmadvise += astats->astats.nmadvise;
	sstats->astats.purged += astats->astats.purged;

	sstats->astats.metadata_mapped += astats->astats.metadata_mapped;
	sstats->astats.metadata_allocated += astats->astats.metadata_allocated;

	sstats->allocated_small += astats->allocated_small;
	sstats->nmalloc_small += astats->nmalloc_small;
	sstats->ndalloc_small += astats->ndalloc_small;
	sstats->nrequests_small += astats->nrequests_small;

	sstats->astats.allocated_large += astats->astats.allocated_large;
	sstats->astats.nmalloc_large += astats->astats.nmalloc_large;
	sstats->astats.ndalloc_large += astats->astats.ndalloc_large;
	sstats->astats.nrequests_large += astats->astats.nrequests_large;

	sstats->astats.allocated_huge += astats->astats.allocated_huge;
	sstats->astats.nmalloc_huge += astats->astats.nmalloc_huge;
	sstats->astats.ndalloc_huge += astats->astats.ndalloc_huge;

	for (i = 0; i < NBINS; i++) {
		sstats->bstats[i].nmalloc += astats->bstats[i].nmalloc;
		sstats->bstats[i].ndalloc += astats->bstats[i].ndalloc;
		sstats->bstats[i].nrequests += astats->bstats[i].nrequests;
		sstats->bstats[i].curregs += astats->bstats[i].curregs;
		if (config_tcache) {
			sstats->bstats[i].nfills += astats->bstats[i].nfills;
			sstats->bstats[i].nflushes +=
			    astats->bstats[i].nflushes;
		}
		sstats->bstats[i].nruns += astats->bstats[i].nruns;
		sstats->bstats[i].reruns += astats->bstats[i].reruns;
		sstats->bstats[i].curruns += astats->bstats[i].curruns;
	}

	for (i = 0; i < nlclasses; i++) {
		sstats->lstats[i].nmalloc += astats->lstats[i].nmalloc;
		sstats->lstats[i].ndalloc += astats->lstats[i].ndalloc;
		sstats->lstats[i].nrequests += astats->lstats[i].nrequests;
		sstats->lstats[i].curruns += astats->lstats[i].curruns;
	}

	for (i = 0; i < nhclasses; i++) {
		sstats->hstats[i].nmalloc += astats->hstats[i].nmalloc;
		sstats->hstats[i].ndalloc += astats->hstats[i].ndalloc;
		sstats->hstats[i].curhchunks += astats->hstats[i].curhchunks;
	}
}