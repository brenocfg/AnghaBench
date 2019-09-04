#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  prof_tctx_t ;
typedef  int /*<<< orphan*/  extent_node_t ;
struct TYPE_3__ {int /*<<< orphan*/  huge_mtx; } ;
typedef  TYPE_1__ arena_t ;

/* Variables and functions */
 TYPE_1__* extent_node_arena_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  extent_node_prof_tctx_set (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * huge_node_get (void const*) ; 
 int /*<<< orphan*/  malloc_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  malloc_mutex_unlock (int /*<<< orphan*/ *) ; 

void
huge_prof_tctx_set(const void *ptr, prof_tctx_t *tctx)
{
	extent_node_t *node;
	arena_t *arena;

	node = huge_node_get(ptr);
	arena = extent_node_arena_get(node);
	malloc_mutex_lock(&arena->huge_mtx);
	extent_node_prof_tctx_set(node, tctx);
	malloc_mutex_unlock(&arena->huge_mtx);
}