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
struct inode {int /*<<< orphan*/  i_mode; } ;
typedef  int /*<<< orphan*/  mode_t ;

/* Variables and functions */
 int /*<<< orphan*/  ACL_TYPE_DEFAULT ; 
 int ENOMEM ; 
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (struct posix_acl*) ; 
 int PTR_ERR (struct posix_acl*) ; 
 scalar_t__ S_ISDIR (int /*<<< orphan*/ ) ; 
 struct posix_acl* nfs3_proc_getacl (struct inode*,int /*<<< orphan*/ ) ; 
 int nfs3_proc_setacls (struct inode*,struct posix_acl*,struct posix_acl*) ; 
 struct posix_acl* posix_acl_clone (struct posix_acl*,int /*<<< orphan*/ ) ; 
 int posix_acl_create_masq (struct posix_acl*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  posix_acl_release (struct posix_acl*) ; 

int nfs3_proc_set_default_acl(struct inode *dir, struct inode *inode,
		mode_t mode)
{
	struct posix_acl *dfacl, *acl;
	int error = 0;

	dfacl = nfs3_proc_getacl(dir, ACL_TYPE_DEFAULT);
	if (IS_ERR(dfacl)) {
		error = PTR_ERR(dfacl);
		return (error == -EOPNOTSUPP) ? 0 : error;
	}
	if (!dfacl)
		return 0;
	acl = posix_acl_clone(dfacl, GFP_KERNEL);
	error = -ENOMEM;
	if (!acl)
		goto out_release_dfacl;
	error = posix_acl_create_masq(acl, &mode);
	if (error < 0)
		goto out_release_acl;
	error = nfs3_proc_setacls(inode, acl, S_ISDIR(inode->i_mode) ?
						      dfacl : NULL);
out_release_acl:
	posix_acl_release(acl);
out_release_dfacl:
	posix_acl_release(dfacl);
	return error;
}