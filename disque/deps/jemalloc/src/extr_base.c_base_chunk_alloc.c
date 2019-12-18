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
 size_t CACHELINE_CEILING (int) ; 
 size_t CHUNK_CEILING (size_t) ; 
 scalar_t__ PAGE_CEILING (size_t) ; 
 int /*<<< orphan*/  assert (int) ; 
 size_t base_allocated ; 
 size_t base_mapped ; 
 int /*<<< orphan*/  base_node_dalloc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * base_node_try_alloc () ; 
 int /*<<< orphan*/  base_resident ; 
 void* chunk_alloc_base (size_t) ; 
 scalar_t__ config_stats ; 
 int /*<<< orphan*/  extent_node_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void*,size_t,int,int) ; 

__attribute__((used)) static extent_node_t *
base_chunk_alloc(size_t minsize)
{
	extent_node_t *node;
	size_t csize, nsize;
	void *addr;

	assert(minsize != 0);
	node = base_node_try_alloc();
	/* Allocate enough space to also carve a node out if necessary. */
	nsize = (node == NULL) ? CACHELINE_CEILING(sizeof(extent_node_t)) : 0;
	csize = CHUNK_CEILING(minsize + nsize);
	addr = chunk_alloc_base(csize);
	if (addr == NULL) {
		if (node != NULL)
			base_node_dalloc(node);
		return (NULL);
	}
	base_mapped += csize;
	if (node == NULL) {
		node = (extent_node_t *)addr;
		addr = (void *)((uintptr_t)addr + nsize);
		csize -= nsize;
		if (config_stats) {
			base_allocated += nsize;
			base_resident += PAGE_CEILING(nsize);
		}
	}
	extent_node_init(node, NULL, addr, csize, true, true);
	return (node);
}