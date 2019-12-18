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
struct nfs_inode {scalar_t__ change_attr; int cache_validity; scalar_t__ npages; } ;
struct nfs_fattr {int valid; scalar_t__ pre_change_attr; scalar_t__ change_attr; int /*<<< orphan*/  size; int /*<<< orphan*/  pre_size; int /*<<< orphan*/  mtime; int /*<<< orphan*/  pre_mtime; int /*<<< orphan*/  ctime; int /*<<< orphan*/  pre_ctime; } ;
struct inode {int /*<<< orphan*/  i_mode; int /*<<< orphan*/  i_mtime; int /*<<< orphan*/  i_ctime; } ;

/* Variables and functions */
 int NFS_ATTR_FATTR_CHANGE ; 
 int NFS_ATTR_FATTR_CTIME ; 
 int NFS_ATTR_FATTR_MTIME ; 
 int NFS_ATTR_FATTR_PRECHANGE ; 
 int NFS_ATTR_FATTR_PRECTIME ; 
 int NFS_ATTR_FATTR_PREMTIME ; 
 int NFS_ATTR_FATTR_PRESIZE ; 
 int NFS_ATTR_FATTR_SIZE ; 
 struct nfs_inode* NFS_I (struct inode*) ; 
 unsigned long NFS_INO_INVALID_ATTR ; 
 int NFS_INO_INVALID_DATA ; 
 scalar_t__ S_ISDIR (int /*<<< orphan*/ ) ; 
 scalar_t__ i_size_read (struct inode*) ; 
 int /*<<< orphan*/  i_size_write (struct inode*,scalar_t__) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  nfs_fscache_invalidate (struct inode*) ; 
 scalar_t__ nfs_size_to_loff_t (int /*<<< orphan*/ ) ; 
 scalar_t__ timespec_equal (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static unsigned long nfs_wcc_update_inode(struct inode *inode, struct nfs_fattr *fattr)
{
	struct nfs_inode *nfsi = NFS_I(inode);
	unsigned long ret = 0;

	if ((fattr->valid & NFS_ATTR_FATTR_PRECHANGE)
			&& (fattr->valid & NFS_ATTR_FATTR_CHANGE)
			&& nfsi->change_attr == fattr->pre_change_attr) {
		nfsi->change_attr = fattr->change_attr;
		if (S_ISDIR(inode->i_mode))
			nfsi->cache_validity |= NFS_INO_INVALID_DATA;
		ret |= NFS_INO_INVALID_ATTR;
	}
	/* If we have atomic WCC data, we may update some attributes */
	if ((fattr->valid & NFS_ATTR_FATTR_PRECTIME)
			&& (fattr->valid & NFS_ATTR_FATTR_CTIME)
			&& timespec_equal(&inode->i_ctime, &fattr->pre_ctime)) {
		memcpy(&inode->i_ctime, &fattr->ctime, sizeof(inode->i_ctime));
		ret |= NFS_INO_INVALID_ATTR;
	}

	if ((fattr->valid & NFS_ATTR_FATTR_PREMTIME)
			&& (fattr->valid & NFS_ATTR_FATTR_MTIME)
			&& timespec_equal(&inode->i_mtime, &fattr->pre_mtime)) {
		memcpy(&inode->i_mtime, &fattr->mtime, sizeof(inode->i_mtime));
		if (S_ISDIR(inode->i_mode))
			nfsi->cache_validity |= NFS_INO_INVALID_DATA;
		ret |= NFS_INO_INVALID_ATTR;
	}
	if ((fattr->valid & NFS_ATTR_FATTR_PRESIZE)
			&& (fattr->valid & NFS_ATTR_FATTR_SIZE)
			&& i_size_read(inode) == nfs_size_to_loff_t(fattr->pre_size)
			&& nfsi->npages == 0) {
		i_size_write(inode, nfs_size_to_loff_t(fattr->size));
		ret |= NFS_INO_INVALID_ATTR;
	}

	if (nfsi->cache_validity & NFS_INO_INVALID_DATA)
		nfs_fscache_invalidate(inode);

	return ret;
}