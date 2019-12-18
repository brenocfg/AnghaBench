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
struct inode {scalar_t__ i_ino; int i_state; int /*<<< orphan*/  i_sb; int /*<<< orphan*/  i_nlink; int /*<<< orphan*/  i_count; } ;
struct hpfs_inode_info {int /*<<< orphan*/  i_parent_mutex; int /*<<< orphan*/  i_mutex; scalar_t__ i_dirty; int /*<<< orphan*/  i_parent_dir; scalar_t__* i_rddir_off; } ;
struct TYPE_2__ {scalar_t__ sb_root; } ;

/* Variables and functions */
 int I_NEW ; 
 int /*<<< orphan*/  atomic_read (int /*<<< orphan*/ *) ; 
 struct hpfs_inode_info* hpfs_i (struct inode*) ; 
 int /*<<< orphan*/  hpfs_init_inode (struct inode*) ; 
 int /*<<< orphan*/  hpfs_read_inode (struct inode*) ; 
 TYPE_1__* hpfs_sb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hpfs_write_inode_nolock (struct inode*) ; 
 struct inode* iget_locked (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iput (struct inode*) ; 
 int /*<<< orphan*/  kfree (scalar_t__*) ; 
 int /*<<< orphan*/  mark_inode_dirty (struct inode*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printk (char*) ; 
 int /*<<< orphan*/  unlock_new_inode (struct inode*) ; 

void hpfs_write_inode(struct inode *i)
{
	struct hpfs_inode_info *hpfs_inode = hpfs_i(i);
	struct inode *parent;
	if (i->i_ino == hpfs_sb(i->i_sb)->sb_root) return;
	if (hpfs_inode->i_rddir_off && !atomic_read(&i->i_count)) {
		if (*hpfs_inode->i_rddir_off) printk("HPFS: write_inode: some position still there\n");
		kfree(hpfs_inode->i_rddir_off);
		hpfs_inode->i_rddir_off = NULL;
	}
	mutex_lock(&hpfs_inode->i_parent_mutex);
	if (!i->i_nlink) {
		mutex_unlock(&hpfs_inode->i_parent_mutex);
		return;
	}
	parent = iget_locked(i->i_sb, hpfs_inode->i_parent_dir);
	if (parent) {
		hpfs_inode->i_dirty = 0;
		if (parent->i_state & I_NEW) {
			hpfs_init_inode(parent);
			hpfs_read_inode(parent);
			unlock_new_inode(parent);
		}
		mutex_lock(&hpfs_inode->i_mutex);
		hpfs_write_inode_nolock(i);
		mutex_unlock(&hpfs_inode->i_mutex);
		iput(parent);
	} else {
		mark_inode_dirty(i);
	}
	mutex_unlock(&hpfs_inode->i_parent_mutex);
}