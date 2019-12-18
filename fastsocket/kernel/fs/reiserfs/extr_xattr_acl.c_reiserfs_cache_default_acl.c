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
struct posix_acl {int /*<<< orphan*/  a_count; } ;
struct inode {int /*<<< orphan*/  i_sb; } ;
struct TYPE_2__ {int /*<<< orphan*/  i_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACL_TYPE_DEFAULT ; 
 int /*<<< orphan*/  IS_ERR (struct posix_acl*) ; 
 scalar_t__ IS_PRIVATE (struct inode*) ; 
 scalar_t__ JOURNAL_BLOCKS_PER_OBJECT (int /*<<< orphan*/ ) ; 
 TYPE_1__* REISERFS_I (struct inode*) ; 
 int /*<<< orphan*/  i_has_xattr_dir ; 
 int /*<<< orphan*/  posix_acl_release (struct posix_acl*) ; 
 int reiserfs_acl_size (int /*<<< orphan*/ ) ; 
 struct posix_acl* reiserfs_get_acl (struct inode*,int /*<<< orphan*/ ) ; 
 int reiserfs_xattr_jcreate_nblocks (struct inode*) ; 
 int reiserfs_xattr_nblocks (struct inode*,int) ; 

int reiserfs_cache_default_acl(struct inode *inode)
{
	struct posix_acl *acl;
	int nblocks = 0;

	if (IS_PRIVATE(inode))
		return 0;

	acl = reiserfs_get_acl(inode, ACL_TYPE_DEFAULT);

	if (acl && !IS_ERR(acl)) {
		int size = reiserfs_acl_size(acl->a_count);

		/* Other xattrs can be created during inode creation. We don't
		 * want to claim too many blocks, so we check to see if we
		 * we need to create the tree to the xattrs, and then we
		 * just want two files. */
		nblocks = reiserfs_xattr_jcreate_nblocks(inode);
		nblocks += JOURNAL_BLOCKS_PER_OBJECT(inode->i_sb);

		REISERFS_I(inode)->i_flags |= i_has_xattr_dir;

		/* We need to account for writes + bitmaps for two files */
		nblocks += reiserfs_xattr_nblocks(inode, size) * 4;
		posix_acl_release(acl);
	}

	return nblocks;
}