#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct super_operations {void (* delete_inode ) (struct inode*) ;} ;
struct inode {int i_state; int /*<<< orphan*/  i_hash; int /*<<< orphan*/  i_data; int /*<<< orphan*/  i_sb_list; int /*<<< orphan*/  i_list; TYPE_1__* i_sb; } ;
struct TYPE_4__ {int /*<<< orphan*/  nr_inodes; } ;
struct TYPE_3__ {struct super_operations* s_op; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int I_CLEAR ; 
 int I_FREEING ; 
 int I_NEW ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  clear_inode (struct inode*) ; 
 int /*<<< orphan*/  destroy_inode (struct inode*) ; 
 int /*<<< orphan*/  hlist_del_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  inode_lock ; 
 TYPE_2__ inodes_stat ; 
 int /*<<< orphan*/  is_bad_inode (struct inode*) ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  security_inode_delete (struct inode*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  truncate_inode_pages (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vfs_dq_init (struct inode*) ; 
 int /*<<< orphan*/  wake_up_inode (struct inode*) ; 

void generic_delete_inode(struct inode *inode)
{
	const struct super_operations *op = inode->i_sb->s_op;

	list_del_init(&inode->i_list);
	list_del_init(&inode->i_sb_list);
	WARN_ON(inode->i_state & I_NEW);
	inode->i_state |= I_FREEING;
	inodes_stat.nr_inodes--;
	spin_unlock(&inode_lock);

	security_inode_delete(inode);

	if (op->delete_inode) {
		void (*delete)(struct inode *) = op->delete_inode;
		if (!is_bad_inode(inode))
			vfs_dq_init(inode);
		/* Filesystems implementing their own
		 * s_op->delete_inode are required to call
		 * truncate_inode_pages and clear_inode()
		 * internally */
		delete(inode);
	} else {
		truncate_inode_pages(&inode->i_data, 0);
		clear_inode(inode);
	}
	spin_lock(&inode_lock);
	hlist_del_init(&inode->i_hash);
	spin_unlock(&inode_lock);
	wake_up_inode(inode);
	BUG_ON(inode->i_state != I_CLEAR);
	destroy_inode(inode);
}