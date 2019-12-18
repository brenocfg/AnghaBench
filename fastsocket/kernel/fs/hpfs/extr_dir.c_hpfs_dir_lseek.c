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
struct super_block {int dummy; } ;
struct quad_buffer_head {int dummy; } ;
struct inode {int /*<<< orphan*/  i_mutex; struct super_block* i_sb; } ;
struct hpfs_inode_info {int /*<<< orphan*/  i_dno; } ;
struct TYPE_4__ {TYPE_1__* dentry; } ;
struct file {int f_pos; TYPE_2__ f_path; } ;
typedef  int loff_t ;
struct TYPE_3__ {struct inode* d_inode; } ;

/* Variables and functions */
 int ESPIPE ; 
 int /*<<< orphan*/  hpfs_brelse4 (struct quad_buffer_head*) ; 
 scalar_t__ hpfs_de_as_down_as_possible (struct super_block*,int /*<<< orphan*/ ) ; 
 struct hpfs_inode_info* hpfs_i (struct inode*) ; 
 int /*<<< orphan*/  lock_kernel () ; 
 scalar_t__ map_pos_dirent (struct inode*,int*,struct quad_buffer_head*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  unlock_kernel () ; 

__attribute__((used)) static loff_t hpfs_dir_lseek(struct file *filp, loff_t off, int whence)
{
	loff_t new_off = off + (whence == 1 ? filp->f_pos : 0);
	loff_t pos;
	struct quad_buffer_head qbh;
	struct inode *i = filp->f_path.dentry->d_inode;
	struct hpfs_inode_info *hpfs_inode = hpfs_i(i);
	struct super_block *s = i->i_sb;

	lock_kernel();

	/*printk("dir lseek\n");*/
	if (new_off == 0 || new_off == 1 || new_off == 11 || new_off == 12 || new_off == 13) goto ok;
	mutex_lock(&i->i_mutex);
	pos = ((loff_t) hpfs_de_as_down_as_possible(s, hpfs_inode->i_dno) << 4) + 1;
	while (pos != new_off) {
		if (map_pos_dirent(i, &pos, &qbh)) hpfs_brelse4(&qbh);
		else goto fail;
		if (pos == 12) goto fail;
	}
	mutex_unlock(&i->i_mutex);
ok:
	unlock_kernel();
	return filp->f_pos = new_off;
fail:
	mutex_unlock(&i->i_mutex);
	/*printk("illegal lseek: %016llx\n", new_off);*/
	unlock_kernel();
	return -ESPIPE;
}