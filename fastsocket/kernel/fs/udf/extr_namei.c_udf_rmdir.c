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
struct udf_fileident_bh {scalar_t__ sbh; scalar_t__ ebh; } ;
struct kernel_lb_addr {int dummy; } ;
struct inode {scalar_t__ i_ino; int i_nlink; int /*<<< orphan*/  i_sb; int /*<<< orphan*/  i_mtime; int /*<<< orphan*/  i_ctime; scalar_t__ i_size; } ;
struct TYPE_2__ {int /*<<< orphan*/  extLocation; } ;
struct fileIdentDesc {TYPE_1__ icb; } ;
struct dentry {int /*<<< orphan*/  d_name; struct inode* d_inode; } ;

/* Variables and functions */
 int EIO ; 
 int ENOENT ; 
 int ENOTEMPTY ; 
 int /*<<< orphan*/  brelse (scalar_t__) ; 
 int /*<<< orphan*/  clear_nlink (struct inode*) ; 
 int /*<<< orphan*/  current_fs_time (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  empty_dir (struct inode*) ; 
 int /*<<< orphan*/  inode_dec_link_count (struct inode*) ; 
 struct kernel_lb_addr lelb_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lock_kernel () ; 
 int /*<<< orphan*/  mark_inode_dirty (struct inode*) ; 
 int udf_delete_entry (struct inode*,struct fileIdentDesc*,struct udf_fileident_bh*,struct fileIdentDesc*) ; 
 struct fileIdentDesc* udf_find_entry (struct inode*,int /*<<< orphan*/ *,struct udf_fileident_bh*,struct fileIdentDesc*) ; 
 scalar_t__ udf_get_lb_pblock (int /*<<< orphan*/ ,struct kernel_lb_addr*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udf_warning (int /*<<< orphan*/ ,char*,char*,int) ; 
 int /*<<< orphan*/  unlock_kernel () ; 

__attribute__((used)) static int udf_rmdir(struct inode *dir, struct dentry *dentry)
{
	int retval;
	struct inode *inode = dentry->d_inode;
	struct udf_fileident_bh fibh;
	struct fileIdentDesc *fi, cfi;
	struct kernel_lb_addr tloc;

	retval = -ENOENT;
	lock_kernel();
	fi = udf_find_entry(dir, &dentry->d_name, &fibh, &cfi);
	if (!fi)
		goto out;

	retval = -EIO;
	tloc = lelb_to_cpu(cfi.icb.extLocation);
	if (udf_get_lb_pblock(dir->i_sb, &tloc, 0) != inode->i_ino)
		goto end_rmdir;
	retval = -ENOTEMPTY;
	if (!empty_dir(inode))
		goto end_rmdir;
	retval = udf_delete_entry(dir, fi, &fibh, &cfi);
	if (retval)
		goto end_rmdir;
	if (inode->i_nlink != 2)
		udf_warning(inode->i_sb, "udf_rmdir",
			    "empty directory has nlink != 2 (%d)",
			    inode->i_nlink);
	clear_nlink(inode);
	inode->i_size = 0;
	inode_dec_link_count(dir);
	inode->i_ctime = dir->i_ctime = dir->i_mtime =
						current_fs_time(dir->i_sb);
	mark_inode_dirty(dir);

end_rmdir:
	if (fibh.sbh != fibh.ebh)
		brelse(fibh.ebh);
	brelse(fibh.sbh);

out:
	unlock_kernel();
	return retval;
}