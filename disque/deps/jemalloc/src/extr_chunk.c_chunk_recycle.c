#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ ret ;
typedef  int /*<<< orphan*/  extent_tree_t ;
typedef  int /*<<< orphan*/  extent_node_t ;
struct TYPE_15__ {scalar_t__ (* commit ) (void*,size_t,int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ ) ;scalar_t__ (* split ) (void*,size_t,size_t,size_t,int,int /*<<< orphan*/ ) ;} ;
typedef  TYPE_1__ chunk_hooks_t ;
struct TYPE_16__ {int /*<<< orphan*/  chunks_mtx; int /*<<< orphan*/  ind; } ;
typedef  TYPE_2__ arena_t ;

/* Variables and functions */
 uintptr_t ALIGNMENT_CEILING (uintptr_t,size_t) ; 
 size_t CHUNK_CEILING (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  JEMALLOC_VALGRIND_MAKE_MEM_DEFINED (void*,size_t) ; 
 int /*<<< orphan*/  arena_chunk_cache_maybe_insert (TYPE_2__*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  arena_chunk_cache_maybe_remove (TYPE_2__*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * arena_node_alloc (TYPE_2__*) ; 
 int /*<<< orphan*/  arena_node_dalloc (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/ * chunk_first_best_fit (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  chunk_hooks_assure_initialized_locked (TYPE_2__*,TYPE_1__*) ; 
 int /*<<< orphan*/  chunk_record (TYPE_2__*,TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,void*,size_t,int,int) ; 
 size_t chunksize ; 
 scalar_t__ config_debug ; 
 void* extent_node_addr_get (int /*<<< orphan*/ *) ; 
 int extent_node_committed_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  extent_node_init (int /*<<< orphan*/ *,TYPE_2__*,void*,size_t,int,int) ; 
 size_t extent_node_size_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  extent_node_size_set (int /*<<< orphan*/ *,size_t) ; 
 int extent_node_zeroed_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  extent_tree_ad_insert (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  extent_tree_ad_remove (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * extent_tree_ad_search (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  extent_tree_szad_insert (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  extent_tree_szad_remove (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  malloc_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  malloc_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (void*,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  s2u (size_t) ; 
 scalar_t__ stub1 (void*,size_t,size_t,size_t,int,int /*<<< orphan*/ ) ; 
 scalar_t__ stub2 (void*,size_t,size_t,size_t,int,int /*<<< orphan*/ ) ; 
 scalar_t__ stub3 (void*,size_t,int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void *
chunk_recycle(arena_t *arena, chunk_hooks_t *chunk_hooks,
    extent_tree_t *chunks_szad, extent_tree_t *chunks_ad, bool cache,
    void *new_addr, size_t size, size_t alignment, bool *zero, bool *commit,
    bool dalloc_node)
{
	void *ret;
	extent_node_t *node;
	size_t alloc_size, leadsize, trailsize;
	bool zeroed, committed;

	assert(new_addr == NULL || alignment == chunksize);
	/*
	 * Cached chunks use the node linkage embedded in their headers, in
	 * which case dalloc_node is true, and new_addr is non-NULL because
	 * we're operating on a specific chunk.
	 */
	assert(dalloc_node || new_addr != NULL);

	alloc_size = CHUNK_CEILING(s2u(size + alignment - chunksize));
	/* Beware size_t wrap-around. */
	if (alloc_size < size)
		return (NULL);
	malloc_mutex_lock(&arena->chunks_mtx);
	chunk_hooks_assure_initialized_locked(arena, chunk_hooks);
	if (new_addr != NULL) {
		extent_node_t key;
		extent_node_init(&key, arena, new_addr, alloc_size, false,
		    false);
		node = extent_tree_ad_search(chunks_ad, &key);
	} else {
		node = chunk_first_best_fit(arena, chunks_szad, chunks_ad,
		    alloc_size);
	}
	if (node == NULL || (new_addr != NULL && extent_node_size_get(node) <
	    size)) {
		malloc_mutex_unlock(&arena->chunks_mtx);
		return (NULL);
	}
	leadsize = ALIGNMENT_CEILING((uintptr_t)extent_node_addr_get(node),
	    alignment) - (uintptr_t)extent_node_addr_get(node);
	assert(new_addr == NULL || leadsize == 0);
	assert(extent_node_size_get(node) >= leadsize + size);
	trailsize = extent_node_size_get(node) - leadsize - size;
	ret = (void *)((uintptr_t)extent_node_addr_get(node) + leadsize);
	zeroed = extent_node_zeroed_get(node);
	if (zeroed)
		*zero = true;
	committed = extent_node_committed_get(node);
	if (committed)
		*commit = true;
	/* Split the lead. */
	if (leadsize != 0 &&
	    chunk_hooks->split(extent_node_addr_get(node),
	    extent_node_size_get(node), leadsize, size, false, arena->ind)) {
		malloc_mutex_unlock(&arena->chunks_mtx);
		return (NULL);
	}
	/* Remove node from the tree. */
	extent_tree_szad_remove(chunks_szad, node);
	extent_tree_ad_remove(chunks_ad, node);
	arena_chunk_cache_maybe_remove(arena, node, cache);
	if (leadsize != 0) {
		/* Insert the leading space as a smaller chunk. */
		extent_node_size_set(node, leadsize);
		extent_tree_szad_insert(chunks_szad, node);
		extent_tree_ad_insert(chunks_ad, node);
		arena_chunk_cache_maybe_insert(arena, node, cache);
		node = NULL;
	}
	if (trailsize != 0) {
		/* Split the trail. */
		if (chunk_hooks->split(ret, size + trailsize, size,
		    trailsize, false, arena->ind)) {
			if (dalloc_node && node != NULL)
				arena_node_dalloc(arena, node);
			malloc_mutex_unlock(&arena->chunks_mtx);
			chunk_record(arena, chunk_hooks, chunks_szad, chunks_ad,
			    cache, ret, size + trailsize, zeroed, committed);
			return (NULL);
		}
		/* Insert the trailing space as a smaller chunk. */
		if (node == NULL) {
			node = arena_node_alloc(arena);
			if (node == NULL) {
				malloc_mutex_unlock(&arena->chunks_mtx);
				chunk_record(arena, chunk_hooks, chunks_szad,
				    chunks_ad, cache, ret, size + trailsize,
				    zeroed, committed);
				return (NULL);
			}
		}
		extent_node_init(node, arena, (void *)((uintptr_t)(ret) + size),
		    trailsize, zeroed, committed);
		extent_tree_szad_insert(chunks_szad, node);
		extent_tree_ad_insert(chunks_ad, node);
		arena_chunk_cache_maybe_insert(arena, node, cache);
		node = NULL;
	}
	if (!committed && chunk_hooks->commit(ret, size, 0, size, arena->ind)) {
		malloc_mutex_unlock(&arena->chunks_mtx);
		chunk_record(arena, chunk_hooks, chunks_szad, chunks_ad, cache,
		    ret, size, zeroed, committed);
		return (NULL);
	}
	malloc_mutex_unlock(&arena->chunks_mtx);

	assert(dalloc_node || node != NULL);
	if (dalloc_node && node != NULL)
		arena_node_dalloc(arena, node);
	if (*zero) {
		if (!zeroed)
			memset(ret, 0, size);
		else if (config_debug) {
			size_t i;
			size_t *p = (size_t *)(uintptr_t)ret;

			JEMALLOC_VALGRIND_MAKE_MEM_DEFINED(ret, size);
			for (i = 0; i < size / sizeof(size_t); i++)
				assert(p[i] == 0);
		}
	}
	return (ret);
}