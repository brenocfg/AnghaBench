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
struct inode {scalar_t__ i_acl; scalar_t__ i_default_acl; } ;

/* Variables and functions */
 scalar_t__ ACL_NOT_CACHED ; 
 int /*<<< orphan*/  BUG_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fsnotify_inode_delete (struct inode*) ; 
 int /*<<< orphan*/  inode_has_buffers (struct inode*) ; 
 int /*<<< orphan*/  posix_acl_release (scalar_t__) ; 
 int /*<<< orphan*/  security_inode_free (struct inode*) ; 

void __destroy_inode(struct inode *inode)
{
	BUG_ON(inode_has_buffers(inode));
	security_inode_free(inode);
	fsnotify_inode_delete(inode);
#ifdef CONFIG_FS_POSIX_ACL
	if (inode->i_acl && inode->i_acl != ACL_NOT_CACHED)
		posix_acl_release(inode->i_acl);
	if (inode->i_default_acl && inode->i_default_acl != ACL_NOT_CACHED)
		posix_acl_release(inode->i_default_acl);
#endif
}