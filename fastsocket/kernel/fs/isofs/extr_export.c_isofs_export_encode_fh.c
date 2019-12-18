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
struct iso_inode_info {scalar_t__ i_iget5_offset; int /*<<< orphan*/  i_iget5_block; } ;
struct inode {int /*<<< orphan*/  i_generation; int /*<<< orphan*/  i_mode; } ;
struct dentry {int /*<<< orphan*/  d_lock; TYPE_1__* d_parent; struct inode* d_inode; } ;
typedef  int /*<<< orphan*/  __u32 ;
typedef  scalar_t__ __u16 ;
struct TYPE_2__ {struct inode* d_inode; } ;

/* Variables and functions */
 struct iso_inode_info* ISOFS_I (struct inode*) ; 
 int /*<<< orphan*/  S_ISDIR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
isofs_export_encode_fh(struct dentry *dentry,
		       __u32 *fh32,
		       int *max_len,
		       int connectable)
{
	struct inode * inode = dentry->d_inode;
	struct iso_inode_info * ei = ISOFS_I(inode);
	int len = *max_len;
	int type = 1;
	__u16 *fh16 = (__u16*)fh32;

	/*
	 * WARNING: max_len is 5 for NFSv2.  Because of this
	 * limitation, we use the lower 16 bits of fh32[1] to hold the
	 * offset of the inode and the upper 16 bits of fh32[1] to
	 * hold the offset of the parent.
	 */

	if (len < 3 || (connectable && len < 5))
		return 255;

	len = 3;
	fh32[0] = ei->i_iget5_block;
 	fh16[2] = (__u16)ei->i_iget5_offset;  /* fh16 [sic] */
	fh32[2] = inode->i_generation;
	if (connectable && !S_ISDIR(inode->i_mode)) {
		struct inode *parent;
		struct iso_inode_info *eparent;
		spin_lock(&dentry->d_lock);
		parent = dentry->d_parent->d_inode;
		eparent = ISOFS_I(parent);
		fh32[3] = eparent->i_iget5_block;
		fh16[3] = (__u16)eparent->i_iget5_offset;  /* fh16 [sic] */
		fh32[4] = parent->i_generation;
		spin_unlock(&dentry->d_lock);
		len = 5;
		type = 2;
	}
	*max_len = len;
	return type;
}