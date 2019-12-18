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
struct o2nm_cluster {int /*<<< orphan*/  cl_nodes_lock; int /*<<< orphan*/  cl_nodes_bitmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int EINVAL ; 
 int /*<<< orphan*/  memcpy (unsigned long*,int /*<<< orphan*/ ,int) ; 
 struct o2nm_cluster* o2nm_single_cluster ; 
 int /*<<< orphan*/  read_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_unlock (int /*<<< orphan*/ *) ; 

int o2nm_configured_node_map(unsigned long *map, unsigned bytes)
{
	struct o2nm_cluster *cluster = o2nm_single_cluster;

	BUG_ON(bytes < (sizeof(cluster->cl_nodes_bitmap)));

	if (cluster == NULL)
		return -EINVAL;

	read_lock(&cluster->cl_nodes_lock);
	memcpy(map, cluster->cl_nodes_bitmap, sizeof(cluster->cl_nodes_bitmap));
	read_unlock(&cluster->cl_nodes_lock);

	return 0;
}