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
struct nfs_inode {scalar_t__ fileid; scalar_t__ change_attr; scalar_t__ npages; unsigned long cache_validity; int /*<<< orphan*/  read_cache_jiffies; } ;
struct nfs_fattr {int valid; scalar_t__ fileid; int mode; scalar_t__ change_attr; scalar_t__ uid; scalar_t__ gid; scalar_t__ nlink; int /*<<< orphan*/  time_start; int /*<<< orphan*/  atime; int /*<<< orphan*/  size; int /*<<< orphan*/  mtime; } ;
struct inode {int i_mode; scalar_t__ i_uid; scalar_t__ i_gid; scalar_t__ i_nlink; int /*<<< orphan*/  i_atime; int /*<<< orphan*/  i_mtime; } ;
typedef  scalar_t__ loff_t ;

/* Variables and functions */
 int EIO ; 
 int NFS_ATTR_FATTR_ATIME ; 
 int NFS_ATTR_FATTR_CHANGE ; 
 int NFS_ATTR_FATTR_FILEID ; 
 int NFS_ATTR_FATTR_GROUP ; 
 int NFS_ATTR_FATTR_MODE ; 
 int NFS_ATTR_FATTR_MTIME ; 
 int NFS_ATTR_FATTR_NLINK ; 
 int NFS_ATTR_FATTR_OWNER ; 
 int NFS_ATTR_FATTR_SIZE ; 
 int NFS_ATTR_FATTR_TYPE ; 
 struct nfs_inode* NFS_I (struct inode*) ; 
 unsigned long NFS_INO_INVALID_ACCESS ; 
 unsigned long NFS_INO_INVALID_ACL ; 
 unsigned long NFS_INO_INVALID_ATIME ; 
 unsigned long NFS_INO_INVALID_ATTR ; 
 unsigned long NFS_INO_REVAL_PAGECACHE ; 
 int S_IALLUGO ; 
 int S_IFMT ; 
 scalar_t__ i_size_read (struct inode*) ; 
 scalar_t__ nfs_have_delegated_attributes (struct inode*) ; 
 scalar_t__ nfs_size_to_loff_t (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  timespec_equal (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int nfs_check_inode_attributes(struct inode *inode, struct nfs_fattr *fattr)
{
	struct nfs_inode *nfsi = NFS_I(inode);
	loff_t cur_size, new_isize;
	unsigned long invalid = 0;


	if (nfs_have_delegated_attributes(inode))
		return 0;
	/* Has the inode gone and changed behind our back? */
	if ((fattr->valid & NFS_ATTR_FATTR_FILEID) && nfsi->fileid != fattr->fileid)
		return -EIO;
	if ((fattr->valid & NFS_ATTR_FATTR_TYPE) && (inode->i_mode & S_IFMT) != (fattr->mode & S_IFMT))
		return -EIO;

	if ((fattr->valid & NFS_ATTR_FATTR_CHANGE) != 0 &&
			nfsi->change_attr != fattr->change_attr)
		invalid |= NFS_INO_INVALID_ATTR|NFS_INO_REVAL_PAGECACHE;

	/* Verify a few of the more important attributes */
	if ((fattr->valid & NFS_ATTR_FATTR_MTIME) && !timespec_equal(&inode->i_mtime, &fattr->mtime))
		invalid |= NFS_INO_INVALID_ATTR;

	if (fattr->valid & NFS_ATTR_FATTR_SIZE) {
		cur_size = i_size_read(inode);
		new_isize = nfs_size_to_loff_t(fattr->size);
		if (cur_size != new_isize && nfsi->npages == 0)
			invalid |= NFS_INO_INVALID_ATTR|NFS_INO_REVAL_PAGECACHE;
	}

	/* Have any file permissions changed? */
	if ((fattr->valid & NFS_ATTR_FATTR_MODE) && (inode->i_mode & S_IALLUGO) != (fattr->mode & S_IALLUGO))
		invalid |= NFS_INO_INVALID_ATTR | NFS_INO_INVALID_ACCESS | NFS_INO_INVALID_ACL;
	if ((fattr->valid & NFS_ATTR_FATTR_OWNER) && inode->i_uid != fattr->uid)
		invalid |= NFS_INO_INVALID_ATTR | NFS_INO_INVALID_ACCESS | NFS_INO_INVALID_ACL;
	if ((fattr->valid & NFS_ATTR_FATTR_GROUP) && inode->i_gid != fattr->gid)
		invalid |= NFS_INO_INVALID_ATTR | NFS_INO_INVALID_ACCESS | NFS_INO_INVALID_ACL;

	/* Has the link count changed? */
	if ((fattr->valid & NFS_ATTR_FATTR_NLINK) && inode->i_nlink != fattr->nlink)
		invalid |= NFS_INO_INVALID_ATTR;

	if ((fattr->valid & NFS_ATTR_FATTR_ATIME) && !timespec_equal(&inode->i_atime, &fattr->atime))
		invalid |= NFS_INO_INVALID_ATIME;

	if (invalid != 0)
		nfsi->cache_validity |= invalid;

	nfsi->read_cache_jiffies = fattr->time_start;
	return 0;
}