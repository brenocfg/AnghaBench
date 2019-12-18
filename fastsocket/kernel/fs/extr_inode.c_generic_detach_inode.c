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
struct super_block {int s_flags; } ;
struct inode {int i_state; int /*<<< orphan*/  i_sb_list; int /*<<< orphan*/  i_list; int /*<<< orphan*/  i_hash; struct super_block* i_sb; } ;
struct TYPE_2__ {int /*<<< orphan*/  nr_inodes; int /*<<< orphan*/  nr_unused; } ;

/* Variables and functions */
 int I_DIRTY ; 
 int I_FREEING ; 
 int I_NEW ; 
 int I_SYNC ; 
 int I_WILL_FREE ; 
 int MS_ACTIVE ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  hlist_del_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hlist_unhashed (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  inode_lock ; 
 int /*<<< orphan*/  inode_unused ; 
 TYPE_1__ inodes_stat ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_move (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_inode_now (struct inode*,int) ; 

int generic_detach_inode(struct inode *inode)
{
	struct super_block *sb = inode->i_sb;

	if (!hlist_unhashed(&inode->i_hash)) {
		if (!(inode->i_state & (I_DIRTY|I_SYNC)))
			list_move(&inode->i_list, &inode_unused);
		inodes_stat.nr_unused++;
		if (sb->s_flags & MS_ACTIVE) {
			spin_unlock(&inode_lock);
			return 0;
		}
		WARN_ON(inode->i_state & I_NEW);
		inode->i_state |= I_WILL_FREE;
		spin_unlock(&inode_lock);
		write_inode_now(inode, 1);
		spin_lock(&inode_lock);
		WARN_ON(inode->i_state & I_NEW);
		inode->i_state &= ~I_WILL_FREE;
		inodes_stat.nr_unused--;
		hlist_del_init(&inode->i_hash);
	}
	list_del_init(&inode->i_list);
	list_del_init(&inode->i_sb_list);
	WARN_ON(inode->i_state & I_NEW);
	inode->i_state |= I_FREEING;
	inodes_stat.nr_inodes--;
	spin_unlock(&inode_lock);
	return 1;
}