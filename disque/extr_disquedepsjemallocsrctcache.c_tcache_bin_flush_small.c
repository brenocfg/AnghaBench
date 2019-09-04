#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_22__   TYPE_7__ ;
typedef  struct TYPE_21__   TYPE_6__ ;
typedef  struct TYPE_20__   TYPE_5__ ;
typedef  struct TYPE_19__   TYPE_4__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tsd_t ;
struct TYPE_18__ {int /*<<< orphan*/  prof_accumbytes; } ;
typedef  TYPE_3__ tcache_t ;
struct TYPE_17__ {scalar_t__ nrequests; } ;
struct TYPE_19__ {unsigned int ncached; void** avail; int low_water; TYPE_2__ tstats; } ;
typedef  TYPE_4__ tcache_bin_t ;
typedef  size_t szind_t ;
struct TYPE_20__ {TYPE_7__* bins; } ;
typedef  TYPE_5__ arena_t ;
struct TYPE_21__ {int /*<<< orphan*/  node; } ;
typedef  TYPE_6__ arena_chunk_t ;
typedef  int /*<<< orphan*/  arena_chunk_map_bits_t ;
struct TYPE_16__ {int /*<<< orphan*/  nrequests; int /*<<< orphan*/  nflushes; } ;
struct TYPE_22__ {int /*<<< orphan*/  lock; TYPE_1__ stats; } ;
typedef  TYPE_7__ arena_bin_t ;

/* Variables and functions */
 scalar_t__ CHUNK_ADDR2BASE (void*) ; 
 uintptr_t LG_PAGE ; 
 size_t NBINS ; 
 int /*<<< orphan*/ * arena_bitselm_get (TYPE_6__*,size_t) ; 
 TYPE_5__* arena_choose (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  arena_dalloc_bin_junked_locked (TYPE_5__*,TYPE_6__*,void*,int /*<<< orphan*/ *) ; 
 scalar_t__ arena_prof_accum (TYPE_5__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ config_prof ; 
 scalar_t__ config_stats ; 
 TYPE_5__* extent_node_arena_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  malloc_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  malloc_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memmove (void**,void**,unsigned int) ; 
 int /*<<< orphan*/  prof_idump () ; 

void
tcache_bin_flush_small(tsd_t *tsd, tcache_t *tcache, tcache_bin_t *tbin,
    szind_t binind, unsigned rem)
{
	arena_t *arena;
	void *ptr;
	unsigned i, nflush, ndeferred;
	bool merged_stats = false;

	assert(binind < NBINS);
	assert(rem <= tbin->ncached);

	arena = arena_choose(tsd, NULL);
	assert(arena != NULL);
	for (nflush = tbin->ncached - rem; nflush > 0; nflush = ndeferred) {
		/* Lock the arena bin associated with the first object. */
		arena_chunk_t *chunk = (arena_chunk_t *)CHUNK_ADDR2BASE(
		    tbin->avail[0]);
		arena_t *bin_arena = extent_node_arena_get(&chunk->node);
		arena_bin_t *bin = &bin_arena->bins[binind];

		if (config_prof && bin_arena == arena) {
			if (arena_prof_accum(arena, tcache->prof_accumbytes))
				prof_idump();
			tcache->prof_accumbytes = 0;
		}

		malloc_mutex_lock(&bin->lock);
		if (config_stats && bin_arena == arena) {
			assert(!merged_stats);
			merged_stats = true;
			bin->stats.nflushes++;
			bin->stats.nrequests += tbin->tstats.nrequests;
			tbin->tstats.nrequests = 0;
		}
		ndeferred = 0;
		for (i = 0; i < nflush; i++) {
			ptr = tbin->avail[i];
			assert(ptr != NULL);
			chunk = (arena_chunk_t *)CHUNK_ADDR2BASE(ptr);
			if (extent_node_arena_get(&chunk->node) == bin_arena) {
				size_t pageind = ((uintptr_t)ptr -
				    (uintptr_t)chunk) >> LG_PAGE;
				arena_chunk_map_bits_t *bitselm =
				    arena_bitselm_get(chunk, pageind);
				arena_dalloc_bin_junked_locked(bin_arena, chunk,
				    ptr, bitselm);
			} else {
				/*
				 * This object was allocated via a different
				 * arena bin than the one that is currently
				 * locked.  Stash the object, so that it can be
				 * handled in a future pass.
				 */
				tbin->avail[ndeferred] = ptr;
				ndeferred++;
			}
		}
		malloc_mutex_unlock(&bin->lock);
	}
	if (config_stats && !merged_stats) {
		/*
		 * The flush loop didn't happen to flush to this thread's
		 * arena, so the stats didn't get merged.  Manually do so now.
		 */
		arena_bin_t *bin = &arena->bins[binind];
		malloc_mutex_lock(&bin->lock);
		bin->stats.nflushes++;
		bin->stats.nrequests += tbin->tstats.nrequests;
		tbin->tstats.nrequests = 0;
		malloc_mutex_unlock(&bin->lock);
	}

	memmove(tbin->avail, &tbin->avail[tbin->ncached - rem],
	    rem * sizeof(void *));
	tbin->ncached = rem;
	if ((int)tbin->ncached < tbin->low_water)
		tbin->low_water = tbin->ncached;
}