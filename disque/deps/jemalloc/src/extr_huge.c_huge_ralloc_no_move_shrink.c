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
typedef  int /*<<< orphan*/  extent_node_t ;
struct TYPE_9__ {scalar_t__ (* split ) (void*,size_t,size_t,size_t,int,int /*<<< orphan*/ ) ;} ;
typedef  TYPE_1__ chunk_hooks_t ;
struct TYPE_10__ {int /*<<< orphan*/  huge_mtx; int /*<<< orphan*/  ind; } ;
typedef  TYPE_2__ arena_t ;

/* Variables and functions */
 int /*<<< orphan*/  CHUNK_ADDR2BASE (uintptr_t) ; 
 int /*<<< orphan*/  CHUNK_ADDR2OFFSET (uintptr_t) ; 
 size_t CHUNK_CEILING (size_t) ; 
 int /*<<< orphan*/  arena_chunk_ralloc_huge_shrink (TYPE_2__*,void*,size_t,size_t) ; 
 int /*<<< orphan*/  assert (int) ; 
 TYPE_1__ chunk_hooks_get (TYPE_2__*) ; 
 int /*<<< orphan*/  chunk_purge_wrapper (TYPE_2__*,TYPE_1__*,int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ ,size_t) ; 
 scalar_t__ config_fill ; 
 TYPE_2__* extent_node_arena_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  extent_node_size_set (int /*<<< orphan*/ *,size_t) ; 
 int extent_node_zeroed_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  extent_node_zeroed_set (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  huge_dalloc_junk (void*,size_t) ; 
 int /*<<< orphan*/ * huge_node_get (void*) ; 
 int /*<<< orphan*/  malloc_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  malloc_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  opt_junk_free ; 
 scalar_t__ stub1 (void*,size_t,size_t,size_t,int,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool
huge_ralloc_no_move_shrink(void *ptr, size_t oldsize, size_t usize)
{
	extent_node_t *node;
	arena_t *arena;
	chunk_hooks_t chunk_hooks;
	size_t cdiff;
	bool pre_zeroed, post_zeroed;

	node = huge_node_get(ptr);
	arena = extent_node_arena_get(node);
	pre_zeroed = extent_node_zeroed_get(node);
	chunk_hooks = chunk_hooks_get(arena);

	assert(oldsize > usize);

	/* Split excess chunks. */
	cdiff = CHUNK_CEILING(oldsize) - CHUNK_CEILING(usize);
	if (cdiff != 0 && chunk_hooks.split(ptr, CHUNK_CEILING(oldsize),
	    CHUNK_CEILING(usize), cdiff, true, arena->ind))
		return (true);

	if (oldsize > usize) {
		size_t sdiff = oldsize - usize;
		if (config_fill && unlikely(opt_junk_free)) {
			huge_dalloc_junk((void *)((uintptr_t)ptr + usize),
			    sdiff);
			post_zeroed = false;
		} else {
			post_zeroed = !chunk_purge_wrapper(arena, &chunk_hooks,
			    CHUNK_ADDR2BASE((uintptr_t)ptr + usize),
			    CHUNK_CEILING(oldsize),
			    CHUNK_ADDR2OFFSET((uintptr_t)ptr + usize), sdiff);
		}
	} else
		post_zeroed = pre_zeroed;

	malloc_mutex_lock(&arena->huge_mtx);
	/* Update the size of the huge allocation. */
	extent_node_size_set(node, usize);
	/* Update zeroed. */
	extent_node_zeroed_set(node, post_zeroed);
	malloc_mutex_unlock(&arena->huge_mtx);

	/* Zap the excess chunks. */
	arena_chunk_ralloc_huge_shrink(arena, ptr, oldsize, usize);

	return (false);
}