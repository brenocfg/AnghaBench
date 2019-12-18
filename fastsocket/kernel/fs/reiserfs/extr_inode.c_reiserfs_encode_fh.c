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
struct inode {int /*<<< orphan*/  i_generation; int /*<<< orphan*/  i_ino; } ;
struct dentry {int /*<<< orphan*/  d_lock; TYPE_1__* d_parent; struct inode* d_inode; } ;
typedef  int /*<<< orphan*/  __u32 ;
struct TYPE_4__ {int /*<<< orphan*/  k_dir_id; } ;
struct TYPE_3__ {struct inode* d_inode; } ;

/* Variables and functions */
 TYPE_2__* INODE_PKEY (struct inode*) ; 
 int /*<<< orphan*/  le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

int reiserfs_encode_fh(struct dentry *dentry, __u32 * data, int *lenp,
		       int need_parent)
{
	struct inode *inode = dentry->d_inode;
	int maxlen = *lenp;

	if (maxlen < 3)
		return 255;

	data[0] = inode->i_ino;
	data[1] = le32_to_cpu(INODE_PKEY(inode)->k_dir_id);
	data[2] = inode->i_generation;
	*lenp = 3;
	/* no room for directory info? return what we've stored so far */
	if (maxlen < 5 || !need_parent)
		return 3;

	spin_lock(&dentry->d_lock);
	inode = dentry->d_parent->d_inode;
	data[3] = inode->i_ino;
	data[4] = le32_to_cpu(INODE_PKEY(inode)->k_dir_id);
	*lenp = 5;
	if (maxlen >= 6) {
		data[5] = inode->i_generation;
		*lenp = 6;
	}
	spin_unlock(&dentry->d_lock);
	return *lenp;
}