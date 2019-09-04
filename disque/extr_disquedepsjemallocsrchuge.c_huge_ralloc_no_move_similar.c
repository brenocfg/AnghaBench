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
typedef  int /*<<< orphan*/  extent_node_t ;
typedef  int /*<<< orphan*/  chunk_hooks_t ;
struct TYPE_5__ {int /*<<< orphan*/  huge_mtx; } ;
typedef  TYPE_1__ arena_t ;

/* Variables and functions */
 int /*<<< orphan*/  CHUNK_CEILING (size_t) ; 
 int /*<<< orphan*/  CHUNK_HOOKS_INITIALIZER ; 
 int /*<<< orphan*/  arena_chunk_ralloc_huge_similar (TYPE_1__*,void*,size_t,size_t) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  chunk_purge_wrapper (TYPE_1__*,int /*<<< orphan*/ *,void*,int /*<<< orphan*/ ,size_t,size_t) ; 
 scalar_t__ config_fill ; 
 TYPE_1__* extent_node_arena_get (int /*<<< orphan*/ *) ; 
 size_t extent_node_size_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  extent_node_size_set (int /*<<< orphan*/ *,size_t) ; 
 int extent_node_zeroed_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  extent_node_zeroed_set (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * huge_node_get (void*) ; 
 int /*<<< orphan*/  malloc_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  malloc_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (void*,int,size_t) ; 
 int /*<<< orphan*/  opt_junk_alloc ; 
 int /*<<< orphan*/  opt_junk_free ; 
 int /*<<< orphan*/  opt_zero ; 
 size_t s2u (size_t) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
huge_ralloc_no_move_similar(void *ptr, size_t oldsize, size_t usize_min,
    size_t usize_max, bool zero)
{
	size_t usize, usize_next;
	extent_node_t *node;
	arena_t *arena;
	chunk_hooks_t chunk_hooks = CHUNK_HOOKS_INITIALIZER;
	bool pre_zeroed, post_zeroed;

	/* Increase usize to incorporate extra. */
	for (usize = usize_min; usize < usize_max && (usize_next = s2u(usize+1))
	    <= oldsize; usize = usize_next)
		; /* Do nothing. */

	if (oldsize == usize)
		return;

	node = huge_node_get(ptr);
	arena = extent_node_arena_get(node);
	pre_zeroed = extent_node_zeroed_get(node);

	/* Fill if necessary (shrinking). */
	if (oldsize > usize) {
		size_t sdiff = oldsize - usize;
		if (config_fill && unlikely(opt_junk_free)) {
			memset((void *)((uintptr_t)ptr + usize), 0x5a, sdiff);
			post_zeroed = false;
		} else {
			post_zeroed = !chunk_purge_wrapper(arena, &chunk_hooks,
			    ptr, CHUNK_CEILING(oldsize), usize, sdiff);
		}
	} else
		post_zeroed = pre_zeroed;

	malloc_mutex_lock(&arena->huge_mtx);
	/* Update the size of the huge allocation. */
	assert(extent_node_size_get(node) != usize);
	extent_node_size_set(node, usize);
	/* Update zeroed. */
	extent_node_zeroed_set(node, post_zeroed);
	malloc_mutex_unlock(&arena->huge_mtx);

	arena_chunk_ralloc_huge_similar(arena, ptr, oldsize, usize);

	/* Fill if necessary (growing). */
	if (oldsize < usize) {
		if (zero || (config_fill && unlikely(opt_zero))) {
			if (!pre_zeroed) {
				memset((void *)((uintptr_t)ptr + oldsize), 0,
				    usize - oldsize);
			}
		} else if (config_fill && unlikely(opt_junk_alloc)) {
			memset((void *)((uintptr_t)ptr + oldsize), 0xa5, usize -
			    oldsize);
		}
	}
}