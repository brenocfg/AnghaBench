#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct inode {int /*<<< orphan*/  i_sb; } ;
struct ext3_reserve_window_node {int /*<<< orphan*/  rsv_window; } ;
struct ext3_inode_info {struct ext3_block_alloc_info* i_block_alloc_info; } ;
struct ext3_block_alloc_info {struct ext3_reserve_window_node rsv_window_node; } ;
typedef  int /*<<< orphan*/  spinlock_t ;
struct TYPE_2__ {int /*<<< orphan*/  s_rsv_window_lock; } ;

/* Variables and functions */
 struct ext3_inode_info* EXT3_I (struct inode*) ; 
 TYPE_1__* EXT3_SB (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rsv_is_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rsv_window_remove (int /*<<< orphan*/ ,struct ext3_reserve_window_node*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trace_ext3_discard_reservation (struct inode*,struct ext3_reserve_window_node*) ; 

void ext3_discard_reservation(struct inode *inode)
{
	struct ext3_inode_info *ei = EXT3_I(inode);
	struct ext3_block_alloc_info *block_i = ei->i_block_alloc_info;
	struct ext3_reserve_window_node *rsv;
	spinlock_t *rsv_lock = &EXT3_SB(inode->i_sb)->s_rsv_window_lock;

	if (!block_i)
		return;

	rsv = &block_i->rsv_window_node;
	if (!rsv_is_empty(&rsv->rsv_window)) {
		spin_lock(rsv_lock);
		if (!rsv_is_empty(&rsv->rsv_window)) {
			trace_ext3_discard_reservation(inode, rsv);
			rsv_window_remove(inode->i_sb, rsv);
		}
		spin_unlock(rsv_lock);
	}
}