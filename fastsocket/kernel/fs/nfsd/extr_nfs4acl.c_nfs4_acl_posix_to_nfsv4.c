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
struct posix_acl {int a_count; } ;
struct nfs4_acl {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ENOMEM ; 
 struct nfs4_acl* ERR_PTR (int /*<<< orphan*/ ) ; 
 unsigned int NFS4_ACL_TYPE_DEFAULT ; 
 int /*<<< orphan*/  _posix_to_nfsv4_one (struct posix_acl*,struct nfs4_acl*,unsigned int) ; 
 struct nfs4_acl* nfs4_acl_new (int) ; 
 scalar_t__ posix_acl_valid (struct posix_acl*) ; 

struct nfs4_acl *
nfs4_acl_posix_to_nfsv4(struct posix_acl *pacl, struct posix_acl *dpacl,
			unsigned int flags)
{
	struct nfs4_acl *acl;
	int size = 0;

	if (pacl) {
		if (posix_acl_valid(pacl) < 0)
			return ERR_PTR(-EINVAL);
		size += 2*pacl->a_count;
	}
	if (dpacl) {
		if (posix_acl_valid(dpacl) < 0)
			return ERR_PTR(-EINVAL);
		size += 2*dpacl->a_count;
	}

	/* Allocate for worst case: one (deny, allow) pair each: */
	acl = nfs4_acl_new(size);
	if (acl == NULL)
		return ERR_PTR(-ENOMEM);

	if (pacl)
		_posix_to_nfsv4_one(pacl, acl, flags & ~NFS4_ACL_TYPE_DEFAULT);

	if (dpacl)
		_posix_to_nfsv4_one(dpacl, acl, flags | NFS4_ACL_TYPE_DEFAULT);

	return acl;
}