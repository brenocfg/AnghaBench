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
typedef  int u32 ;
struct super_block {TYPE_1__* s_root; } ;
struct inode {int i_generation; } ;
struct fid {int* raw; } ;
struct dentry {int /*<<< orphan*/  d_op; } ;
typedef  int loff_t ;
struct TYPE_4__ {int i_logstart; } ;
struct TYPE_3__ {int /*<<< orphan*/  d_op; } ;

/* Variables and functions */
 int /*<<< orphan*/  IS_ERR (struct dentry*) ; 
 TYPE_2__* MSDOS_I (struct inode*) ; 
 struct dentry* d_obtain_alias (struct inode*) ; 
 struct inode* fat_iget (struct super_block*,int) ; 
 struct inode* ilookup (struct super_block*,int) ; 
 int /*<<< orphan*/  iput (struct inode*) ; 

__attribute__((used)) static struct dentry *fat_fh_to_dentry(struct super_block *sb,
		struct fid *fid, int fh_len, int fh_type)
{
	struct inode *inode = NULL;
	struct dentry *result;
	u32 *fh = fid->raw;

	if (fh_len < 5 || fh_type != 3)
		return NULL;

	inode = ilookup(sb, fh[0]);
	if (!inode || inode->i_generation != fh[1]) {
		if (inode)
			iput(inode);
		inode = NULL;
	}
	if (!inode) {
		loff_t i_pos;
		int i_logstart = fh[3] & 0x0fffffff;

		i_pos = (loff_t)fh[2] << 8;
		i_pos |= ((fh[3] >> 24) & 0xf0) | (fh[4] >> 28);

		/* try 2 - see if i_pos is in F-d-c
		 * require i_logstart to be the same
		 * Will fail if you truncate and then re-write
		 */

		inode = fat_iget(sb, i_pos);
		if (inode && MSDOS_I(inode)->i_logstart != i_logstart) {
			iput(inode);
			inode = NULL;
		}
	}

	/*
	 * For now, do nothing if the inode is not found.
	 *
	 * What we could do is:
	 *
	 *	- follow the file starting at fh[4], and record the ".." entry,
	 *	  and the name of the fh[2] entry.
	 *	- then follow the ".." file finding the next step up.
	 *
	 * This way we build a path to the root of the tree. If this works, we
	 * lookup the path and so get this inode into the cache.  Finally try
	 * the fat_iget lookup again.  If that fails, then we are totally out
	 * of luck.  But all that is for another day
	 */
	result = d_obtain_alias(inode);
	if (!IS_ERR(result))
		result->d_op = sb->s_root->d_op;
	return result;
}