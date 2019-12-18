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
struct posix_acl {int dummy; } ;
struct nfs_inode {struct posix_acl* acl_default; struct posix_acl* acl_access; } ;
struct inode {int /*<<< orphan*/  i_ino; TYPE_1__* i_sb; int /*<<< orphan*/  i_lock; } ;
struct TYPE_2__ {int /*<<< orphan*/  s_id; } ;

/* Variables and functions */
#define  ACL_TYPE_ACCESS 129 
#define  ACL_TYPE_DEFAULT 128 
 int /*<<< orphan*/  EAGAIN ; 
 int /*<<< orphan*/  EINVAL ; 
 struct posix_acl* ERR_PTR (int /*<<< orphan*/ ) ; 
 scalar_t__ IS_ERR (struct posix_acl*) ; 
 struct nfs_inode* NFS_I (struct inode*) ; 
 int /*<<< orphan*/  dprintk (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,struct posix_acl*) ; 
 struct posix_acl* posix_acl_dup (struct posix_acl*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct posix_acl *nfs3_get_cached_acl(struct inode *inode, int type)
{
	struct nfs_inode *nfsi = NFS_I(inode);
	struct posix_acl *acl = ERR_PTR(-EINVAL);

	spin_lock(&inode->i_lock);
	switch(type) {
		case ACL_TYPE_ACCESS:
			acl = nfsi->acl_access;
			break;

		case ACL_TYPE_DEFAULT:
			acl = nfsi->acl_default;
			break;

		default:
			goto out;
	}
	if (IS_ERR(acl))
		acl = ERR_PTR(-EAGAIN);
	else
		acl = posix_acl_dup(acl);
out:
	spin_unlock(&inode->i_lock);
	dprintk("NFS: nfs3_get_cached_acl(%s/%ld, %d) = %p\n", inode->i_sb->s_id,
		inode->i_ino, type, acl);
	return acl;
}