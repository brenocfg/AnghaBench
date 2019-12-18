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
struct mpath_node {int /*<<< orphan*/  rcu; int /*<<< orphan*/  list; struct mesh_path* mpath; } ;
struct mesh_table {int /*<<< orphan*/  entries; } ;
struct mesh_path {int /*<<< orphan*/  state_lock; scalar_t__ is_gate; int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  MESH_PATH_RESOLVING ; 
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  call_rcu (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hlist_del_rcu (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mesh_gate_del (struct mesh_table*,struct mesh_path*) ; 
 int /*<<< orphan*/  mesh_path_node_reclaim ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void __mesh_path_del(struct mesh_table *tbl, struct mpath_node *node)
{
	struct mesh_path *mpath;
	mpath = node->mpath;
	spin_lock(&mpath->state_lock);
	mpath->flags |= MESH_PATH_RESOLVING;
	if (mpath->is_gate)
		mesh_gate_del(tbl, mpath);
	hlist_del_rcu(&node->list);
	call_rcu(&node->rcu, mesh_path_node_reclaim);
	spin_unlock(&mpath->state_lock);
	atomic_dec(&tbl->entries);
}