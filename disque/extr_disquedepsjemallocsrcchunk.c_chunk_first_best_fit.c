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
typedef  int /*<<< orphan*/  extent_tree_t ;
typedef  int /*<<< orphan*/  extent_node_t ;
typedef  int /*<<< orphan*/  arena_t ;

/* Variables and functions */
 size_t CHUNK_CEILING (size_t) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  extent_node_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,size_t,int,int) ; 
 int /*<<< orphan*/ * extent_tree_szad_nsearch (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static extent_node_t *
chunk_first_best_fit(arena_t *arena, extent_tree_t *chunks_szad,
    extent_tree_t *chunks_ad, size_t size)
{
	extent_node_t key;

	assert(size == CHUNK_CEILING(size));

	extent_node_init(&key, arena, NULL, size, false, false);
	return (extent_tree_szad_nsearch(chunks_szad, &key));
}