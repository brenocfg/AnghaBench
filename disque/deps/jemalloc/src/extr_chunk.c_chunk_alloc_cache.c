#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  chunk_hooks_t ;
struct TYPE_4__ {int /*<<< orphan*/  chunks_ad_cached; int /*<<< orphan*/  chunks_szad_cached; } ;
typedef  TYPE_1__ arena_t ;

/* Variables and functions */
 int /*<<< orphan*/  JEMALLOC_VALGRIND_MAKE_MEM_UNDEFINED (void*,size_t) ; 
 int /*<<< orphan*/  assert (int) ; 
 void* chunk_recycle (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,void*,size_t,size_t,int*,int*,int) ; 
 size_t chunksize_mask ; 
 scalar_t__ config_valgrind ; 

void *
chunk_alloc_cache(arena_t *arena, chunk_hooks_t *chunk_hooks, void *new_addr,
    size_t size, size_t alignment, bool *zero, bool dalloc_node)
{
	void *ret;
	bool commit;

	assert(size != 0);
	assert((size & chunksize_mask) == 0);
	assert(alignment != 0);
	assert((alignment & chunksize_mask) == 0);

	commit = true;
	ret = chunk_recycle(arena, chunk_hooks, &arena->chunks_szad_cached,
	    &arena->chunks_ad_cached, true, new_addr, size, alignment, zero,
	    &commit, dalloc_node);
	if (ret == NULL)
		return (NULL);
	assert(commit);
	if (config_valgrind)
		JEMALLOC_VALGRIND_MAKE_MEM_UNDEFINED(ret, size);
	return (ret);
}