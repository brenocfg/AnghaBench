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
struct nfs_fattr {int dummy; } ;
struct inode {int /*<<< orphan*/  i_mode; } ;
struct iattr {int ia_valid; scalar_t__ ia_size; } ;
struct dentry {struct inode* d_inode; } ;
struct TYPE_2__ {int (* setattr ) (struct dentry*,struct nfs_fattr*,struct iattr*) ;} ;

/* Variables and functions */
 int ATTR_FILE ; 
 int ATTR_GID ; 
 int ATTR_KILL_SGID ; 
 int ATTR_KILL_SUID ; 
 int ATTR_MODE ; 
 int ATTR_OPEN ; 
 int ATTR_SIZE ; 
 int ATTR_UID ; 
 int ENOMEM ; 
 int /*<<< orphan*/  NFSIOS_VFSSETATTR ; 
 TYPE_1__* NFS_PROTO (struct inode*) ; 
 int NFS_VALID_ATTRS ; 
 scalar_t__ S_ISREG (int /*<<< orphan*/ ) ; 
 scalar_t__ i_size_read (struct inode*) ; 
 struct nfs_fattr* nfs_alloc_fattr () ; 
 int /*<<< orphan*/  nfs_free_fattr (struct nfs_fattr*) ; 
 int /*<<< orphan*/  nfs_inc_stats (struct inode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfs_inode_return_delegation (struct inode*) ; 
 int /*<<< orphan*/  nfs_refresh_inode (struct inode*,struct nfs_fattr*) ; 
 int /*<<< orphan*/  nfs_wb_all (struct inode*) ; 
 int stub1 (struct dentry*,struct nfs_fattr*,struct iattr*) ; 

int
nfs_setattr(struct dentry *dentry, struct iattr *attr)
{
	struct inode *inode = dentry->d_inode;
	struct nfs_fattr *fattr;
	int error = -ENOMEM;

	nfs_inc_stats(inode, NFSIOS_VFSSETATTR);

	/* skip mode change if it's just for clearing setuid/setgid */
	if (attr->ia_valid & (ATTR_KILL_SUID | ATTR_KILL_SGID))
		attr->ia_valid &= ~ATTR_MODE;

	if (attr->ia_valid & ATTR_SIZE) {
		if (!S_ISREG(inode->i_mode) || attr->ia_size == i_size_read(inode))
			attr->ia_valid &= ~ATTR_SIZE;
	}

	/* Optimization: if the end result is no change, don't RPC */
	attr->ia_valid &= NFS_VALID_ATTRS;
	if ((attr->ia_valid & ~(ATTR_FILE|ATTR_OPEN)) == 0)
		return 0;

	/* Write all dirty data */
	if (S_ISREG(inode->i_mode))
		nfs_wb_all(inode);

	fattr = nfs_alloc_fattr();
	if (fattr == NULL)
		goto out;
	/*
	 * Return any delegations if we're going to change ACLs
	 */
	if ((attr->ia_valid & (ATTR_MODE|ATTR_UID|ATTR_GID)) != 0)
		nfs_inode_return_delegation(inode);
	error = NFS_PROTO(inode)->setattr(dentry, fattr, attr);
	if (error == 0)
		nfs_refresh_inode(inode, fattr);
	nfs_free_fattr(fattr);
out:
	return error;
}