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
typedef  int /*<<< orphan*/  tsd_t ;
typedef  int /*<<< orphan*/  tcache_t ;
typedef  int /*<<< orphan*/  extent_node_t ;
struct TYPE_4__ {int /*<<< orphan*/  huge_mtx; int /*<<< orphan*/  huge; } ;
typedef  TYPE_1__ arena_t ;

/* Variables and functions */
 int /*<<< orphan*/  arena_chunk_dalloc_huge (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  extent_node_addr_get (int /*<<< orphan*/ *) ; 
 TYPE_1__* extent_node_arena_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  extent_node_size_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  huge_dalloc_junk (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * huge_node_get (void*) ; 
 int /*<<< orphan*/  huge_node_unset (void*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  idalloctm (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  malloc_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  malloc_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ql_link ; 
 int /*<<< orphan*/  ql_remove (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void
huge_dalloc(tsd_t *tsd, void *ptr, tcache_t *tcache)
{
	extent_node_t *node;
	arena_t *arena;

	node = huge_node_get(ptr);
	arena = extent_node_arena_get(node);
	huge_node_unset(ptr, node);
	malloc_mutex_lock(&arena->huge_mtx);
	ql_remove(&arena->huge, node, ql_link);
	malloc_mutex_unlock(&arena->huge_mtx);

	huge_dalloc_junk(extent_node_addr_get(node),
	    extent_node_size_get(node));
	arena_chunk_dalloc_huge(extent_node_arena_get(node),
	    extent_node_addr_get(node), extent_node_size_get(node));
	idalloctm(tsd, node, tcache, true);
}