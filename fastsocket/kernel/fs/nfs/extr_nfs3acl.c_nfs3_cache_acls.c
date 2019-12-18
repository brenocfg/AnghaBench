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
struct nfs_inode {void* acl_default; void* acl_access; } ;
struct inode {int /*<<< orphan*/  i_lock; int /*<<< orphan*/  i_ino; TYPE_1__* i_sb; } ;
struct TYPE_2__ {int /*<<< orphan*/  s_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  IS_ERR (struct posix_acl*) ; 
 struct nfs_inode* NFS_I (struct inode*) ; 
 int /*<<< orphan*/  __nfs3_forget_cached_acls (struct nfs_inode*) ; 
 int /*<<< orphan*/  dprintk (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct posix_acl*,struct posix_acl*) ; 
 void* posix_acl_dup (struct posix_acl*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void nfs3_cache_acls(struct inode *inode, struct posix_acl *acl,
		    struct posix_acl *dfacl)
{
	struct nfs_inode *nfsi = NFS_I(inode);

	dprintk("nfs3_cache_acls(%s/%ld, %p, %p)\n", inode->i_sb->s_id,
		inode->i_ino, acl, dfacl);
	spin_lock(&inode->i_lock);
	__nfs3_forget_cached_acls(NFS_I(inode));
	if (!IS_ERR(acl))
		nfsi->acl_access = posix_acl_dup(acl);
	if (!IS_ERR(dfacl))
		nfsi->acl_default = posix_acl_dup(dfacl);
	spin_unlock(&inode->i_lock);
}