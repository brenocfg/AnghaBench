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
struct qstr {scalar_t__ len; int /*<<< orphan*/  name; } ;
struct inode {int dummy; } ;
struct dlmfs_inode_private {struct dlm_ctxt* ip_dlm; } ;
struct dlm_protocol_version {int dummy; } ;
struct dlm_ctxt {int dummy; } ;
struct dentry {struct qstr d_name; } ;

/* Variables and functions */
 struct dlmfs_inode_private* DLMFS_I (struct inode*) ; 
 int EINVAL ; 
 int ENOMEM ; 
 scalar_t__ IS_ERR (struct dlm_ctxt*) ; 
 int /*<<< orphan*/  ML_ERROR ; 
 scalar_t__ O2NM_MAX_NAME_LEN ; 
 int PTR_ERR (struct dlm_ctxt*) ; 
 int S_IFDIR ; 
 int /*<<< orphan*/  d_instantiate (struct dentry*,struct inode*) ; 
 int /*<<< orphan*/  dget (struct dentry*) ; 
 struct inode* dlmfs_get_inode (struct inode*,struct dentry*,int) ; 
 int /*<<< orphan*/  inc_nlink (struct inode*) ; 
 int /*<<< orphan*/  iput (struct inode*) ; 
 int /*<<< orphan*/  mlog (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  mlog_errno (int) ; 
 struct dlm_ctxt* user_dlm_register_context (struct qstr*,struct dlm_protocol_version*) ; 
 struct dlm_protocol_version user_locking_protocol ; 

__attribute__((used)) static int dlmfs_mkdir(struct inode * dir,
		       struct dentry * dentry,
		       int mode)
{
	int status;
	struct inode *inode = NULL;
	struct qstr *domain = &dentry->d_name;
	struct dlmfs_inode_private *ip;
	struct dlm_ctxt *dlm;
	struct dlm_protocol_version proto = user_locking_protocol;

	mlog(0, "mkdir %.*s\n", domain->len, domain->name);

	/* verify that we have a proper domain */
	if (domain->len >= O2NM_MAX_NAME_LEN) {
		status = -EINVAL;
		mlog(ML_ERROR, "invalid domain name for directory.\n");
		goto bail;
	}

	inode = dlmfs_get_inode(dir, dentry, mode | S_IFDIR);
	if (!inode) {
		status = -ENOMEM;
		mlog_errno(status);
		goto bail;
	}

	ip = DLMFS_I(inode);

	dlm = user_dlm_register_context(domain, &proto);
	if (IS_ERR(dlm)) {
		status = PTR_ERR(dlm);
		mlog(ML_ERROR, "Error %d could not register domain \"%.*s\"\n",
		     status, domain->len, domain->name);
		goto bail;
	}
	ip->ip_dlm = dlm;

	inc_nlink(dir);
	d_instantiate(dentry, inode);
	dget(dentry);	/* Extra count - pin the dentry in core */

	status = 0;
bail:
	if (status < 0)
		iput(inode);
	return status;
}