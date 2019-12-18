#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  extent_node_t ;

/* Variables and functions */
 size_t CACHELINE_CEILING (size_t) ; 
 int /*<<< orphan*/  JEMALLOC_VALGRIND_MAKE_MEM_DEFINED (void*,size_t) ; 
 scalar_t__ PAGE_CEILING (uintptr_t) ; 
 size_t base_allocated ; 
 int /*<<< orphan*/  base_avail_szad ; 
 int /*<<< orphan*/ * base_chunk_alloc (size_t) ; 
 int /*<<< orphan*/  base_mtx ; 
 int /*<<< orphan*/  base_node_dalloc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  base_resident ; 
 scalar_t__ config_stats ; 
 void* extent_node_addr_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  extent_node_addr_set (int /*<<< orphan*/ *,void*) ; 
 int /*<<< orphan*/  extent_node_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,size_t,int,int) ; 
 size_t extent_node_size_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  extent_node_size_set (int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  extent_tree_szad_insert (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * extent_tree_szad_nsearch (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  extent_tree_szad_remove (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  malloc_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  malloc_mutex_unlock (int /*<<< orphan*/ *) ; 
 size_t s2u (size_t) ; 

void *
base_alloc(size_t size)
{
	void *ret;
	size_t csize, usize;
	extent_node_t *node;
	extent_node_t key;

	/*
	 * Round size up to nearest multiple of the cacheline size, so that
	 * there is no chance of false cache line sharing.
	 */
	csize = CACHELINE_CEILING(size);

	usize = s2u(csize);
	extent_node_init(&key, NULL, NULL, usize, false, false);
	malloc_mutex_lock(&base_mtx);
	node = extent_tree_szad_nsearch(&base_avail_szad, &key);
	if (node != NULL) {
		/* Use existing space. */
		extent_tree_szad_remove(&base_avail_szad, node);
	} else {
		/* Try to allocate more space. */
		node = base_chunk_alloc(csize);
	}
	if (node == NULL) {
		ret = NULL;
		goto label_return;
	}

	ret = extent_node_addr_get(node);
	if (extent_node_size_get(node) > csize) {
		extent_node_addr_set(node, (void *)((uintptr_t)ret + csize));
		extent_node_size_set(node, extent_node_size_get(node) - csize);
		extent_tree_szad_insert(&base_avail_szad, node);
	} else
		base_node_dalloc(node);
	if (config_stats) {
		base_allocated += csize;
		/*
		 * Add one PAGE to base_resident for every page boundary that is
		 * crossed by the new allocation.
		 */
		base_resident += PAGE_CEILING((uintptr_t)ret + csize) -
		    PAGE_CEILING((uintptr_t)ret);
	}
	JEMALLOC_VALGRIND_MAKE_MEM_DEFINED(ret, csize);
label_return:
	malloc_mutex_unlock(&base_mtx);
	return (ret);
}