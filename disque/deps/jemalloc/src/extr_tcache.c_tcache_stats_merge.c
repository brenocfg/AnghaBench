#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_8__ ;
typedef  struct TYPE_17__   TYPE_7__ ;
typedef  struct TYPE_16__   TYPE_6__ ;
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {TYPE_5__* tbins; } ;
typedef  TYPE_4__ tcache_t ;
struct TYPE_13__ {scalar_t__ nrequests; } ;
struct TYPE_15__ {TYPE_3__ tstats; } ;
typedef  TYPE_5__ tcache_bin_t ;
struct TYPE_16__ {int /*<<< orphan*/  nrequests; } ;
typedef  TYPE_6__ malloc_large_stats_t ;
struct TYPE_12__ {int /*<<< orphan*/  nrequests_large; TYPE_6__* lstats; } ;
struct TYPE_17__ {TYPE_2__ stats; TYPE_8__* bins; } ;
typedef  TYPE_7__ arena_t ;
struct TYPE_11__ {int /*<<< orphan*/  nrequests; } ;
struct TYPE_18__ {int /*<<< orphan*/  lock; TYPE_1__ stats; } ;
typedef  TYPE_8__ arena_bin_t ;

/* Variables and functions */
 unsigned int NBINS ; 
 int /*<<< orphan*/  cassert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  config_stats ; 
 int /*<<< orphan*/  malloc_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  malloc_mutex_unlock (int /*<<< orphan*/ *) ; 
 unsigned int nhbins ; 

void
tcache_stats_merge(tcache_t *tcache, arena_t *arena)
{
	unsigned i;

	cassert(config_stats);

	/* Merge and reset tcache stats. */
	for (i = 0; i < NBINS; i++) {
		arena_bin_t *bin = &arena->bins[i];
		tcache_bin_t *tbin = &tcache->tbins[i];
		malloc_mutex_lock(&bin->lock);
		bin->stats.nrequests += tbin->tstats.nrequests;
		malloc_mutex_unlock(&bin->lock);
		tbin->tstats.nrequests = 0;
	}

	for (; i < nhbins; i++) {
		malloc_large_stats_t *lstats = &arena->stats.lstats[i - NBINS];
		tcache_bin_t *tbin = &tcache->tbins[i];
		arena->stats.nrequests_large += tbin->tstats.nrequests;
		lstats->nrequests += tbin->tstats.nrequests;
		tbin->tstats.nrequests = 0;
	}
}