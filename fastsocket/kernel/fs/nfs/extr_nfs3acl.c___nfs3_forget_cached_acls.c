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
struct nfs_inode {void* acl_default; void* acl_access; } ;

/* Variables and functions */
 int /*<<< orphan*/  EAGAIN ; 
 void* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IS_ERR (void*) ; 
 int /*<<< orphan*/  posix_acl_release (void*) ; 

__attribute__((used)) static void __nfs3_forget_cached_acls(struct nfs_inode *nfsi)
{
	if (!IS_ERR(nfsi->acl_access)) {
		posix_acl_release(nfsi->acl_access);
		nfsi->acl_access = ERR_PTR(-EAGAIN);
	}
	if (!IS_ERR(nfsi->acl_default)) {
		posix_acl_release(nfsi->acl_default);
		nfsi->acl_default = ERR_PTR(-EAGAIN);
	}
}