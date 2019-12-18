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
struct iattr {int ia_valid; int /*<<< orphan*/  ia_ctime; int /*<<< orphan*/  ia_mtime; int /*<<< orphan*/  ia_atime; int /*<<< orphan*/  ia_size; int /*<<< orphan*/  ia_gid; int /*<<< orphan*/  ia_uid; int /*<<< orphan*/  ia_mode; } ;
struct hostfs_iattr {int /*<<< orphan*/  ia_valid; int /*<<< orphan*/  ia_ctime; int /*<<< orphan*/  ia_mtime; int /*<<< orphan*/  ia_atime; int /*<<< orphan*/  ia_size; int /*<<< orphan*/  ia_gid; int /*<<< orphan*/  ia_uid; int /*<<< orphan*/  ia_mode; } ;
struct dentry {int /*<<< orphan*/  d_inode; } ;
struct TYPE_2__ {int fd; } ;

/* Variables and functions */
 int ATTR_ATIME ; 
 int ATTR_ATIME_SET ; 
 int ATTR_CTIME ; 
 int ATTR_GID ; 
 int ATTR_MODE ; 
 int ATTR_MTIME ; 
 int ATTR_MTIME_SET ; 
 int ATTR_SIZE ; 
 int ATTR_UID ; 
 int ENOMEM ; 
 int /*<<< orphan*/  HOSTFS_ATTR_ATIME ; 
 int /*<<< orphan*/  HOSTFS_ATTR_ATIME_SET ; 
 int /*<<< orphan*/  HOSTFS_ATTR_CTIME ; 
 int /*<<< orphan*/  HOSTFS_ATTR_GID ; 
 int /*<<< orphan*/  HOSTFS_ATTR_MODE ; 
 int /*<<< orphan*/  HOSTFS_ATTR_MTIME ; 
 int /*<<< orphan*/  HOSTFS_ATTR_MTIME_SET ; 
 int /*<<< orphan*/  HOSTFS_ATTR_SIZE ; 
 int /*<<< orphan*/  HOSTFS_ATTR_UID ; 
 TYPE_1__* HOSTFS_I (int /*<<< orphan*/ ) ; 
 scalar_t__ append ; 
 char* dentry_name (struct dentry*,int /*<<< orphan*/ ) ; 
 int inode_change_ok (int /*<<< orphan*/ ,struct iattr*) ; 
 int inode_setattr (int /*<<< orphan*/ ,struct iattr*) ; 
 int /*<<< orphan*/  kfree (char*) ; 
 int set_attr (char*,struct hostfs_iattr*,int) ; 

int hostfs_setattr(struct dentry *dentry, struct iattr *attr)
{
	struct hostfs_iattr attrs;
	char *name;
	int err;

	int fd = HOSTFS_I(dentry->d_inode)->fd;

	err = inode_change_ok(dentry->d_inode, attr);
	if (err)
		return err;

	if (append)
		attr->ia_valid &= ~ATTR_SIZE;

	attrs.ia_valid = 0;
	if (attr->ia_valid & ATTR_MODE) {
		attrs.ia_valid |= HOSTFS_ATTR_MODE;
		attrs.ia_mode = attr->ia_mode;
	}
	if (attr->ia_valid & ATTR_UID) {
		attrs.ia_valid |= HOSTFS_ATTR_UID;
		attrs.ia_uid = attr->ia_uid;
	}
	if (attr->ia_valid & ATTR_GID) {
		attrs.ia_valid |= HOSTFS_ATTR_GID;
		attrs.ia_gid = attr->ia_gid;
	}
	if (attr->ia_valid & ATTR_SIZE) {
		attrs.ia_valid |= HOSTFS_ATTR_SIZE;
		attrs.ia_size = attr->ia_size;
	}
	if (attr->ia_valid & ATTR_ATIME) {
		attrs.ia_valid |= HOSTFS_ATTR_ATIME;
		attrs.ia_atime = attr->ia_atime;
	}
	if (attr->ia_valid & ATTR_MTIME) {
		attrs.ia_valid |= HOSTFS_ATTR_MTIME;
		attrs.ia_mtime = attr->ia_mtime;
	}
	if (attr->ia_valid & ATTR_CTIME) {
		attrs.ia_valid |= HOSTFS_ATTR_CTIME;
		attrs.ia_ctime = attr->ia_ctime;
	}
	if (attr->ia_valid & ATTR_ATIME_SET) {
		attrs.ia_valid |= HOSTFS_ATTR_ATIME_SET;
	}
	if (attr->ia_valid & ATTR_MTIME_SET) {
		attrs.ia_valid |= HOSTFS_ATTR_MTIME_SET;
	}
	name = dentry_name(dentry, 0);
	if (name == NULL)
		return -ENOMEM;
	err = set_attr(name, &attrs, fd);
	kfree(name);
	if (err)
		return err;

	return inode_setattr(dentry->d_inode, attr);
}