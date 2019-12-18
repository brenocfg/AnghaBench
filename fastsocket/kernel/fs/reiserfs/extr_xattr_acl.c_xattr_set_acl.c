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
struct reiserfs_transaction_handle {int dummy; } ;
struct posix_acl {int dummy; } ;
struct inode {int /*<<< orphan*/  i_sb; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 int EPERM ; 
 scalar_t__ IS_ERR (struct posix_acl*) ; 
 int PTR_ERR (struct posix_acl*) ; 
 int /*<<< orphan*/  is_owner_or_cap (struct inode*) ; 
 int journal_begin (struct reiserfs_transaction_handle*,int /*<<< orphan*/ ,size_t) ; 
 int journal_end (struct reiserfs_transaction_handle*,int /*<<< orphan*/ ,size_t) ; 
 struct posix_acl* posix_acl_from_xattr (void const*,size_t) ; 
 int /*<<< orphan*/  posix_acl_release (struct posix_acl*) ; 
 int posix_acl_valid (struct posix_acl*) ; 
 int /*<<< orphan*/  reiserfs_posixacl (int /*<<< orphan*/ ) ; 
 int reiserfs_set_acl (struct reiserfs_transaction_handle*,struct inode*,int,struct posix_acl*) ; 
 int /*<<< orphan*/  reiserfs_write_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reiserfs_write_unlock (int /*<<< orphan*/ ) ; 
 int reiserfs_xattr_jcreate_nblocks (struct inode*) ; 
 int reiserfs_xattr_nblocks (struct inode*,size_t) ; 

__attribute__((used)) static int
xattr_set_acl(struct inode *inode, int type, const void *value, size_t size)
{
	struct posix_acl *acl;
	int error, error2;
	struct reiserfs_transaction_handle th;
	size_t jcreate_blocks;
	if (!reiserfs_posixacl(inode->i_sb))
		return -EOPNOTSUPP;
	if (!is_owner_or_cap(inode))
		return -EPERM;

	if (value) {
		acl = posix_acl_from_xattr(value, size);
		if (IS_ERR(acl)) {
			return PTR_ERR(acl);
		} else if (acl) {
			error = posix_acl_valid(acl);
			if (error)
				goto release_and_out;
		}
	} else
		acl = NULL;

	/* Pessimism: We can't assume that anything from the xattr root up
	 * has been created. */

	jcreate_blocks = reiserfs_xattr_jcreate_nblocks(inode) +
			 reiserfs_xattr_nblocks(inode, size) * 2;

	reiserfs_write_lock(inode->i_sb);
	error = journal_begin(&th, inode->i_sb, jcreate_blocks);
	if (error == 0) {
		error = reiserfs_set_acl(&th, inode, type, acl);
		error2 = journal_end(&th, inode->i_sb, jcreate_blocks);
		if (error2)
			error = error2;
	}
	reiserfs_write_unlock(inode->i_sb);

      release_and_out:
	posix_acl_release(acl);
	return error;
}