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
struct inode {int /*<<< orphan*/  i_lock; struct posix_acl* i_default_acl; struct posix_acl* i_acl; } ;

/* Variables and functions */
#define  ACL_TYPE_ACCESS 129 
#define  ACL_TYPE_DEFAULT 128 
 void* posix_acl_dup (struct posix_acl*) ; 
 int /*<<< orphan*/  posix_acl_release (struct posix_acl*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
shmem_set_acl(struct inode *inode, int type, struct posix_acl *acl)
{
	struct posix_acl *free = NULL;

	spin_lock(&inode->i_lock);
	switch(type) {
		case ACL_TYPE_ACCESS:
			free = inode->i_acl;
			inode->i_acl = posix_acl_dup(acl);
			break;

		case ACL_TYPE_DEFAULT:
			free = inode->i_default_acl;
			inode->i_default_acl = posix_acl_dup(acl);
			break;
	}
	spin_unlock(&inode->i_lock);
	posix_acl_release(free);
}