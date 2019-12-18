#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  chunk_hooks_t ;
struct TYPE_5__ {int /*<<< orphan*/  chunks_ad_cached; int /*<<< orphan*/  chunks_szad_cached; } ;
typedef  TYPE_1__ arena_t ;

/* Variables and functions */
 void* CHUNK_ADDR2BASE (void*) ; 
 int /*<<< orphan*/  arena_maybe_purge (TYPE_1__*) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  chunk_record (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,void*,size_t,int,int) ; 
 size_t chunksize_mask ; 

void
chunk_dalloc_cache(arena_t *arena, chunk_hooks_t *chunk_hooks, void *chunk,
    size_t size, bool committed)
{

	assert(chunk != NULL);
	assert(CHUNK_ADDR2BASE(chunk) == chunk);
	assert(size != 0);
	assert((size & chunksize_mask) == 0);

	chunk_record(arena, chunk_hooks, &arena->chunks_szad_cached,
	    &arena->chunks_ad_cached, true, chunk, size, false, committed);
	arena_maybe_purge(arena);
}