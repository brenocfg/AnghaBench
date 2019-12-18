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
struct ocfs2_super {int /*<<< orphan*/  node_map_lock; } ;
struct ocfs2_node_map {int num_nodes; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  __ocfs2_node_map_clear_bit (struct ocfs2_node_map*,int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

void ocfs2_node_map_clear_bit(struct ocfs2_super *osb,
			      struct ocfs2_node_map *map,
			      int bit)
{
	if (bit==-1)
		return;
	BUG_ON(bit >= map->num_nodes);
	spin_lock(&osb->node_map_lock);
	__ocfs2_node_map_clear_bit(map, bit);
	spin_unlock(&osb->node_map_lock);
}