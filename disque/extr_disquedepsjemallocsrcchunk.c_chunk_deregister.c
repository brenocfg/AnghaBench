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
 size_t atomic_read_z (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_sub_z (int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  chunks_rtree ; 
 size_t chunksize ; 
 scalar_t__ config_prof ; 
 int /*<<< orphan*/  curchunks ; 
 size_t extent_node_size_get (int /*<<< orphan*/  const*) ; 
 scalar_t__ opt_prof ; 
 int rtree_set (int /*<<< orphan*/ *,uintptr_t,int /*<<< orphan*/ *) ; 

void
chunk_deregister(const void *chunk, const extent_node_t *node)
{
	bool err;

	err = rtree_set(&chunks_rtree, (uintptr_t)chunk, NULL);
	assert(!err);
	if (config_prof && opt_prof) {
		size_t size = extent_node_size_get(node);
		size_t nsub = (size == 0) ? 1 : size / chunksize;
		assert(atomic_read_z(&curchunks) >= nsub);
		atomic_sub_z(&curchunks, nsub);
	}
}