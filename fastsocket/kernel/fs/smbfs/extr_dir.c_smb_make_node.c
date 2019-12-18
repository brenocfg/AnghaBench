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
struct inode {int dummy; } ;
struct iattr {int ia_valid; int ia_mode; int /*<<< orphan*/  ia_gid; int /*<<< orphan*/  ia_uid; } ;
struct dentry {int dummy; } ;
typedef  int /*<<< orphan*/  dev_t ;

/* Variables and functions */
 int ATTR_GID ; 
 int ATTR_MODE ; 
 int ATTR_UID ; 
 int EINVAL ; 
 int /*<<< orphan*/  MAJOR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MINOR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  current_euid_egid (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  new_valid_dev (int /*<<< orphan*/ ) ; 
 int smb_instantiate (struct dentry*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smb_invalid_dir_cache (struct inode*) ; 
 int smb_proc_setattr_unix (struct dentry*,struct iattr*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
smb_make_node(struct inode *dir, struct dentry *dentry, int mode, dev_t dev)
{
	int error;
	struct iattr attr;

	attr.ia_valid = ATTR_MODE | ATTR_UID | ATTR_GID;
	attr.ia_mode = mode;
	current_euid_egid(&attr.ia_uid, &attr.ia_gid);

	if (!new_valid_dev(dev))
		return -EINVAL;

	smb_invalid_dir_cache(dir);
	error = smb_proc_setattr_unix(dentry, &attr, MAJOR(dev), MINOR(dev));
	if (!error) {
		error = smb_instantiate(dentry, 0, 0);
	}
	return error;
}