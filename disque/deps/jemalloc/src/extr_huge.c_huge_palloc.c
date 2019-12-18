#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tsd_t ;
typedef  int /*<<< orphan*/  tcache_t ;
typedef  int /*<<< orphan*/  extent_node_t ;
struct TYPE_9__ {int /*<<< orphan*/  huge_mtx; int /*<<< orphan*/  huge; } ;
typedef  TYPE_1__ arena_t ;

/* Variables and functions */
 int /*<<< orphan*/  CACHELINE ; 
 int /*<<< orphan*/  CACHELINE_CEILING (int) ; 
 TYPE_1__* arena_choose (int /*<<< orphan*/ *,TYPE_1__*) ; 
 void* arena_chunk_alloc_huge (TYPE_1__*,size_t,size_t,int*) ; 
 int /*<<< orphan*/  arena_chunk_dalloc_huge (TYPE_1__*,void*,size_t) ; 
 int /*<<< orphan*/  assert (int) ; 
 size_t chunksize ; 
 scalar_t__ config_fill ; 
 int /*<<< orphan*/  extent_node_init (int /*<<< orphan*/ *,TYPE_1__*,void*,size_t,int,int) ; 
 scalar_t__ huge_node_set (void*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  idalloctm (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * ipallocztm (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int,TYPE_1__*) ; 
 int /*<<< orphan*/  malloc_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  malloc_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (void*,int,size_t) ; 
 int opt_junk_alloc ; 
 int opt_zero ; 
 int /*<<< orphan*/  ql_elm_new (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ql_link ; 
 int /*<<< orphan*/  ql_tail_insert (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 size_t sa2u (size_t,size_t) ; 
 scalar_t__ unlikely (int) ; 

void *
huge_palloc(tsd_t *tsd, arena_t *arena, size_t size, size_t alignment,
    bool zero, tcache_t *tcache)
{
	void *ret;
	size_t usize;
	extent_node_t *node;
	bool is_zeroed;

	/* Allocate one or more contiguous chunks for this request. */

	usize = sa2u(size, alignment);
	if (unlikely(usize == 0))
		return (NULL);
	assert(usize >= chunksize);

	/* Allocate an extent node with which to track the chunk. */
	node = ipallocztm(tsd, CACHELINE_CEILING(sizeof(extent_node_t)),
	    CACHELINE, false, tcache, true, arena);
	if (node == NULL)
		return (NULL);

	/*
	 * Copy zero into is_zeroed and pass the copy to chunk_alloc(), so that
	 * it is possible to make correct junk/zero fill decisions below.
	 */
	is_zeroed = zero;
	arena = arena_choose(tsd, arena);
	if (unlikely(arena == NULL) || (ret = arena_chunk_alloc_huge(arena,
	    size, alignment, &is_zeroed)) == NULL) {
		idalloctm(tsd, node, tcache, true);
		return (NULL);
	}

	extent_node_init(node, arena, ret, size, is_zeroed, true);

	if (huge_node_set(ret, node)) {
		arena_chunk_dalloc_huge(arena, ret, size);
		idalloctm(tsd, node, tcache, true);
		return (NULL);
	}

	/* Insert node into huge. */
	malloc_mutex_lock(&arena->huge_mtx);
	ql_elm_new(node, ql_link);
	ql_tail_insert(&arena->huge, node, ql_link);
	malloc_mutex_unlock(&arena->huge_mtx);

	if (zero || (config_fill && unlikely(opt_zero))) {
		if (!is_zeroed)
			memset(ret, 0, size);
	} else if (config_fill && unlikely(opt_junk_alloc))
		memset(ret, 0xa5, size);

	return (ret);
}