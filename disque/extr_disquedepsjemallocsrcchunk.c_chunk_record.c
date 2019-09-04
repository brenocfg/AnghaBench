#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  extent_tree_t ;
typedef  int /*<<< orphan*/  extent_node_t ;
struct TYPE_14__ {int /*<<< orphan*/  (* merge ) (void*,uintptr_t,void*,size_t,int,int /*<<< orphan*/ ) ;} ;
typedef  TYPE_1__ chunk_hooks_t ;
struct TYPE_15__ {int /*<<< orphan*/  chunks_mtx; int /*<<< orphan*/  ind; } ;
typedef  TYPE_2__ arena_t ;

/* Variables and functions */
 int /*<<< orphan*/  JEMALLOC_VALGRIND_MAKE_MEM_NOACCESS (void*,size_t) ; 
 int /*<<< orphan*/  arena_chunk_cache_maybe_insert (TYPE_2__*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  arena_chunk_cache_maybe_remove (TYPE_2__*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * arena_node_alloc (TYPE_2__*) ; 
 int /*<<< orphan*/  arena_node_dalloc (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  chunk_hooks_assure_initialized_locked (TYPE_2__*,TYPE_1__*) ; 
 int /*<<< orphan*/  chunk_purge_wrapper (TYPE_2__*,TYPE_1__*,void*,size_t,int /*<<< orphan*/ ,size_t) ; 
 void* extent_node_addr_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  extent_node_addr_set (int /*<<< orphan*/ *,void*) ; 
 int extent_node_committed_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  extent_node_init (int /*<<< orphan*/ *,TYPE_2__*,void*,size_t,int,int) ; 
 uintptr_t extent_node_size_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  extent_node_size_set (int /*<<< orphan*/ *,uintptr_t) ; 
 scalar_t__ extent_node_zeroed_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  extent_node_zeroed_set (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  extent_tree_ad_insert (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * extent_tree_ad_nsearch (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * extent_tree_ad_prev (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  extent_tree_ad_remove (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  extent_tree_szad_insert (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  extent_tree_szad_remove (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  malloc_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  malloc_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (void*,size_t,void*,uintptr_t,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (void*,uintptr_t,void*,size_t,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
chunk_record(arena_t *arena, chunk_hooks_t *chunk_hooks,
    extent_tree_t *chunks_szad, extent_tree_t *chunks_ad, bool cache,
    void *chunk, size_t size, bool zeroed, bool committed)
{
	bool unzeroed;
	extent_node_t *node, *prev;
	extent_node_t key;

	assert(!cache || !zeroed);
	unzeroed = cache || !zeroed;
	JEMALLOC_VALGRIND_MAKE_MEM_NOACCESS(chunk, size);

	malloc_mutex_lock(&arena->chunks_mtx);
	chunk_hooks_assure_initialized_locked(arena, chunk_hooks);
	extent_node_init(&key, arena, (void *)((uintptr_t)chunk + size), 0,
	    false, false);
	node = extent_tree_ad_nsearch(chunks_ad, &key);
	/* Try to coalesce forward. */
	if (node != NULL && extent_node_addr_get(node) ==
	    extent_node_addr_get(&key) && extent_node_committed_get(node) ==
	    committed && !chunk_hooks->merge(chunk, size,
	    extent_node_addr_get(node), extent_node_size_get(node), false,
	    arena->ind)) {
		/*
		 * Coalesce chunk with the following address range.  This does
		 * not change the position within chunks_ad, so only
		 * remove/insert from/into chunks_szad.
		 */
		extent_tree_szad_remove(chunks_szad, node);
		arena_chunk_cache_maybe_remove(arena, node, cache);
		extent_node_addr_set(node, chunk);
		extent_node_size_set(node, size + extent_node_size_get(node));
		extent_node_zeroed_set(node, extent_node_zeroed_get(node) &&
		    !unzeroed);
		extent_tree_szad_insert(chunks_szad, node);
		arena_chunk_cache_maybe_insert(arena, node, cache);
	} else {
		/* Coalescing forward failed, so insert a new node. */
		node = arena_node_alloc(arena);
		if (node == NULL) {
			/*
			 * Node allocation failed, which is an exceedingly
			 * unlikely failure.  Leak chunk after making sure its
			 * pages have already been purged, so that this is only
			 * a virtual memory leak.
			 */
			if (cache) {
				chunk_purge_wrapper(arena, chunk_hooks, chunk,
				    size, 0, size);
			}
			goto label_return;
		}
		extent_node_init(node, arena, chunk, size, !unzeroed,
		    committed);
		extent_tree_ad_insert(chunks_ad, node);
		extent_tree_szad_insert(chunks_szad, node);
		arena_chunk_cache_maybe_insert(arena, node, cache);
	}

	/* Try to coalesce backward. */
	prev = extent_tree_ad_prev(chunks_ad, node);
	if (prev != NULL && (void *)((uintptr_t)extent_node_addr_get(prev) +
	    extent_node_size_get(prev)) == chunk &&
	    extent_node_committed_get(prev) == committed &&
	    !chunk_hooks->merge(extent_node_addr_get(prev),
	    extent_node_size_get(prev), chunk, size, false, arena->ind)) {
		/*
		 * Coalesce chunk with the previous address range.  This does
		 * not change the position within chunks_ad, so only
		 * remove/insert node from/into chunks_szad.
		 */
		extent_tree_szad_remove(chunks_szad, prev);
		extent_tree_ad_remove(chunks_ad, prev);
		arena_chunk_cache_maybe_remove(arena, prev, cache);
		extent_tree_szad_remove(chunks_szad, node);
		arena_chunk_cache_maybe_remove(arena, node, cache);
		extent_node_addr_set(node, extent_node_addr_get(prev));
		extent_node_size_set(node, extent_node_size_get(prev) +
		    extent_node_size_get(node));
		extent_node_zeroed_set(node, extent_node_zeroed_get(prev) &&
		    extent_node_zeroed_get(node));
		extent_tree_szad_insert(chunks_szad, node);
		arena_chunk_cache_maybe_insert(arena, node, cache);

		arena_node_dalloc(arena, prev);
	}

label_return:
	malloc_mutex_unlock(&arena->chunks_mtx);
}