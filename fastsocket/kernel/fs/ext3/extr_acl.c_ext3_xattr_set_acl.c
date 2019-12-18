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
struct posix_acl {int dummy; } ;
struct inode {int /*<<< orphan*/  i_sb; } ;
typedef  struct posix_acl handle_t ;

/* Variables and functions */
 int ENOSPC ; 
 int EOPNOTSUPP ; 
 int EPERM ; 
 int /*<<< orphan*/  EXT3_DATA_TRANS_BLOCKS (int /*<<< orphan*/ ) ; 
 scalar_t__ IS_ERR (struct posix_acl*) ; 
 int /*<<< orphan*/  POSIX_ACL ; 
 int PTR_ERR (struct posix_acl*) ; 
 struct posix_acl* ext3_journal_start (struct inode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ext3_journal_stop (struct posix_acl*) ; 
 int ext3_set_acl (struct posix_acl*,struct inode*,int,struct posix_acl*) ; 
 scalar_t__ ext3_should_retry_alloc (int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  is_owner_or_cap (struct inode*) ; 
 struct posix_acl* posix_acl_from_xattr (void const*,size_t) ; 
 int /*<<< orphan*/  posix_acl_release (struct posix_acl*) ; 
 int posix_acl_valid (struct posix_acl*) ; 
 int /*<<< orphan*/  test_opt (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ext3_xattr_set_acl(struct inode *inode, int type, const void *value,
		   size_t size)
{
	handle_t *handle;
	struct posix_acl *acl;
	int error, retries = 0;

	if (!test_opt(inode->i_sb, POSIX_ACL))
		return -EOPNOTSUPP;
	if (!is_owner_or_cap(inode))
		return -EPERM;

	if (value) {
		acl = posix_acl_from_xattr(value, size);
		if (IS_ERR(acl))
			return PTR_ERR(acl);
		else if (acl) {
			error = posix_acl_valid(acl);
			if (error)
				goto release_and_out;
		}
	} else
		acl = NULL;

retry:
	handle = ext3_journal_start(inode, EXT3_DATA_TRANS_BLOCKS(inode->i_sb));
	if (IS_ERR(handle))
		return PTR_ERR(handle);
	error = ext3_set_acl(handle, inode, type, acl);
	ext3_journal_stop(handle);
	if (error == -ENOSPC && ext3_should_retry_alloc(inode->i_sb, &retries))
		goto retry;

release_and_out:
	posix_acl_release(acl);
	return error;
}