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
struct sta_info {int dummy; } ;
struct mesh_path {int sn; int /*<<< orphan*/  state_lock; int /*<<< orphan*/  flags; scalar_t__ exp_time; scalar_t__ hop_count; scalar_t__ metric; } ;

/* Variables and functions */
 int /*<<< orphan*/  MESH_PATH_FIXED ; 
 int /*<<< orphan*/  mesh_path_activate (struct mesh_path*) ; 
 int /*<<< orphan*/  mesh_path_assign_nexthop (struct mesh_path*,struct sta_info*) ; 
 int /*<<< orphan*/  mesh_path_tx_pending (struct mesh_path*) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

void mesh_path_fix_nexthop(struct mesh_path *mpath, struct sta_info *next_hop)
{
	spin_lock_bh(&mpath->state_lock);
	mesh_path_assign_nexthop(mpath, next_hop);
	mpath->sn = 0xffff;
	mpath->metric = 0;
	mpath->hop_count = 0;
	mpath->exp_time = 0;
	mpath->flags |= MESH_PATH_FIXED;
	mesh_path_activate(mpath);
	spin_unlock_bh(&mpath->state_lock);
	mesh_path_tx_pending(mpath);
}