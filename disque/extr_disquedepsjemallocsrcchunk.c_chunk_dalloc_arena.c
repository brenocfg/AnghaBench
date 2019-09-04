#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int (* decommit ) (void*,size_t,int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* purge ) (void*,size_t,int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* dalloc ) (void*,size_t,int,int /*<<< orphan*/ ) ;} ;
typedef  TYPE_1__ chunk_hooks_t ;
struct TYPE_10__ {int /*<<< orphan*/  chunks_ad_retained; int /*<<< orphan*/  chunks_szad_retained; int /*<<< orphan*/  ind; } ;
typedef  TYPE_2__ arena_t ;

/* Variables and functions */
 void* CHUNK_ADDR2BASE (void*) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  chunk_hooks_assure_initialized (TYPE_2__*,TYPE_1__*) ; 
 int /*<<< orphan*/  chunk_record (TYPE_2__*,TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,void*,size_t,int,int) ; 
 size_t chunksize_mask ; 
 int /*<<< orphan*/  stub1 (void*,size_t,int,int /*<<< orphan*/ ) ; 
 int stub2 (void*,size_t,int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub3 (void*,size_t,int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ ) ; 

void
chunk_dalloc_arena(arena_t *arena, chunk_hooks_t *chunk_hooks, void *chunk,
    size_t size, bool zeroed, bool committed)
{

	assert(chunk != NULL);
	assert(CHUNK_ADDR2BASE(chunk) == chunk);
	assert(size != 0);
	assert((size & chunksize_mask) == 0);

	chunk_hooks_assure_initialized(arena, chunk_hooks);
	/* Try to deallocate. */
	if (!chunk_hooks->dalloc(chunk, size, committed, arena->ind))
		return;
	/* Try to decommit; purge if that fails. */
	if (committed) {
		committed = chunk_hooks->decommit(chunk, size, 0, size,
		    arena->ind);
	}
	zeroed = !committed || !chunk_hooks->purge(chunk, size, 0, size,
	    arena->ind);
	chunk_record(arena, chunk_hooks, &arena->chunks_szad_retained,
	    &arena->chunks_ad_retained, false, chunk, size, zeroed, committed);
}