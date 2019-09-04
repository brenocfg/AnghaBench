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
typedef  int /*<<< orphan*/  extent_node_t ;
struct TYPE_4__ {int /*<<< orphan*/  huge_mtx; } ;
typedef  TYPE_1__ arena_t ;

/* Variables and functions */
 size_t CHUNK_CEILING (size_t) ; 
 scalar_t__ arena_chunk_ralloc_huge_expand (TYPE_1__*,void*,size_t,size_t,int*) ; 
 scalar_t__ config_fill ; 
 TYPE_1__* extent_node_arena_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  extent_node_size_set (int /*<<< orphan*/ *,size_t) ; 
 int extent_node_zeroed_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * huge_node_get (void*) ; 
 int /*<<< orphan*/  malloc_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  malloc_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (void*,int,size_t) ; 
 int /*<<< orphan*/  opt_junk_alloc ; 
 int /*<<< orphan*/  opt_zero ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool
huge_ralloc_no_move_expand(void *ptr, size_t oldsize, size_t usize, bool zero) {
	extent_node_t *node;
	arena_t *arena;
	bool is_zeroed_subchunk, is_zeroed_chunk;

	node = huge_node_get(ptr);
	arena = extent_node_arena_get(node);
	malloc_mutex_lock(&arena->huge_mtx);
	is_zeroed_subchunk = extent_node_zeroed_get(node);
	malloc_mutex_unlock(&arena->huge_mtx);

	/*
	 * Copy zero into is_zeroed_chunk and pass the copy to chunk_alloc(), so
	 * that it is possible to make correct junk/zero fill decisions below.
	 */
	is_zeroed_chunk = zero;

	if (arena_chunk_ralloc_huge_expand(arena, ptr, oldsize, usize,
	     &is_zeroed_chunk))
		return (true);

	malloc_mutex_lock(&arena->huge_mtx);
	/* Update the size of the huge allocation. */
	extent_node_size_set(node, usize);
	malloc_mutex_unlock(&arena->huge_mtx);

	if (zero || (config_fill && unlikely(opt_zero))) {
		if (!is_zeroed_subchunk) {
			memset((void *)((uintptr_t)ptr + oldsize), 0,
			    CHUNK_CEILING(oldsize) - oldsize);
		}
		if (!is_zeroed_chunk) {
			memset((void *)((uintptr_t)ptr +
			    CHUNK_CEILING(oldsize)), 0, usize -
			    CHUNK_CEILING(oldsize));
		}
	} else if (config_fill && unlikely(opt_junk_alloc)) {
		memset((void *)((uintptr_t)ptr + oldsize), 0xa5, usize -
		    oldsize);
	}

	return (false);
}