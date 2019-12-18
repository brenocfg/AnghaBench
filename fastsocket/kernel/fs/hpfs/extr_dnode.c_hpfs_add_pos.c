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
struct inode {int dummy; } ;
struct hpfs_inode_info {int /*<<< orphan*/ ** i_rddir_off; } ;
typedef  int /*<<< orphan*/  loff_t ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_NOFS ; 
 struct hpfs_inode_info* hpfs_i (struct inode*) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/ ** kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ **,int /*<<< orphan*/ **,int) ; 
 int /*<<< orphan*/  printk (char*) ; 

void hpfs_add_pos(struct inode *inode, loff_t *pos)
{
	struct hpfs_inode_info *hpfs_inode = hpfs_i(inode);
	int i = 0;
	loff_t **ppos;

	if (hpfs_inode->i_rddir_off)
		for (; hpfs_inode->i_rddir_off[i]; i++)
			if (hpfs_inode->i_rddir_off[i] == pos) return;
	if (!(i&0x0f)) {
		if (!(ppos = kmalloc((i+0x11) * sizeof(loff_t*), GFP_NOFS))) {
			printk("HPFS: out of memory for position list\n");
			return;
		}
		if (hpfs_inode->i_rddir_off) {
			memcpy(ppos, hpfs_inode->i_rddir_off, i * sizeof(loff_t));
			kfree(hpfs_inode->i_rddir_off);
		}
		hpfs_inode->i_rddir_off = ppos;
	}
	hpfs_inode->i_rddir_off[i] = pos;
	hpfs_inode->i_rddir_off[i + 1] = NULL;
}