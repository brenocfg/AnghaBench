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
struct inode {int i_mode; scalar_t__ i_ino; int /*<<< orphan*/  i_sb; } ;
struct dentry {struct inode* d_inode; } ;
struct coda_vattr {int dummy; } ;
struct coda_inode_info {int c_flags; int /*<<< orphan*/  c_fid; } ;
typedef  scalar_t__ ino_t ;

/* Variables and functions */
 int C_FLUSH ; 
 int C_PURGE ; 
 int C_VATTR ; 
 int EIO ; 
 struct coda_inode_info* ITOC (struct inode*) ; 
 int S_IFMT ; 
 int /*<<< orphan*/  coda_f2s (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  coda_flag_inode_children (struct inode*,int) ; 
 int /*<<< orphan*/  coda_vattr_to_iattr (struct inode*,struct coda_vattr*) ; 
 int /*<<< orphan*/  lock_kernel () ; 
 int /*<<< orphan*/  printk (char*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unlock_kernel () ; 
 int venus_getattr (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct coda_vattr*) ; 

int coda_revalidate_inode(struct dentry *dentry)
{
	struct coda_vattr attr;
	int error = 0;
	int old_mode;
	ino_t old_ino;
	struct inode *inode = dentry->d_inode;
	struct coda_inode_info *cii = ITOC(inode);

	lock_kernel();
	if ( !cii->c_flags )
		goto ok;

	if (cii->c_flags & (C_VATTR | C_PURGE | C_FLUSH)) {
		error = venus_getattr(inode->i_sb, &(cii->c_fid), &attr);
		if ( error )
			goto return_bad;

		/* this inode may be lost if:
		   - it's ino changed 
		   - type changes must be permitted for repair and
		   missing mount points.
		*/
		old_mode = inode->i_mode;
		old_ino = inode->i_ino;
		coda_vattr_to_iattr(inode, &attr);

		if ((old_mode & S_IFMT) != (inode->i_mode & S_IFMT)) {
			printk("Coda: inode %ld, fid %s changed type!\n",
			       inode->i_ino, coda_f2s(&(cii->c_fid)));
		}

		/* the following can happen when a local fid is replaced 
		   with a global one, here we lose and declare the inode bad */
		if (inode->i_ino != old_ino)
			goto return_bad;
		
		coda_flag_inode_children(inode, C_FLUSH);
		cii->c_flags &= ~(C_VATTR | C_PURGE | C_FLUSH);
	}

ok:
	unlock_kernel();
	return 0;

return_bad:
	unlock_kernel();
	return -EIO;
}