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
 int /*<<< orphan*/  assert (int) ; 
 size_t atomic_add_z (int /*<<< orphan*/ *,size_t) ; 
 scalar_t__ atomic_cas_z (int /*<<< orphan*/ *,size_t,size_t) ; 
 size_t atomic_read_z (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  chunks_rtree ; 
 size_t chunksize ; 
 scalar_t__ config_prof ; 
 int /*<<< orphan*/  curchunks ; 
 void const* extent_node_addr_get (int /*<<< orphan*/  const*) ; 
 size_t extent_node_size_get (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  highchunks ; 
 scalar_t__ opt_prof ; 
 int /*<<< orphan*/  prof_gdump () ; 
 scalar_t__ prof_gdump_get_unlocked () ; 
 scalar_t__ rtree_set (int /*<<< orphan*/ *,uintptr_t,int /*<<< orphan*/  const*) ; 

bool
chunk_register(const void *chunk, const extent_node_t *node)
{

	assert(extent_node_addr_get(node) == chunk);

	if (rtree_set(&chunks_rtree, (uintptr_t)chunk, node))
		return (true);
	if (config_prof && opt_prof) {
		size_t size = extent_node_size_get(node);
		size_t nadd = (size == 0) ? 1 : size / chunksize;
		size_t cur = atomic_add_z(&curchunks, nadd);
		size_t high = atomic_read_z(&highchunks);
		while (cur > high && atomic_cas_z(&highchunks, high, cur)) {
			/*
			 * Don't refresh cur, because it may have decreased
			 * since this thread lost the highchunks update race.
			 */
			high = atomic_read_z(&highchunks);
		}
		if (cur > high && prof_gdump_get_unlocked())
			prof_gdump();
	}

	return (false);
}