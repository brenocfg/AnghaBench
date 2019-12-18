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
struct inode {scalar_t__ i_uid; scalar_t__ i_gid; } ;
struct iattr {unsigned int ia_valid; scalar_t__ ia_uid; scalar_t__ ia_gid; int /*<<< orphan*/  ia_mode; int /*<<< orphan*/  ia_size; } ;

/* Variables and functions */
 unsigned int ATTR_ATIME_SET ; 
 unsigned int ATTR_FORCE ; 
 unsigned int ATTR_GID ; 
 unsigned int ATTR_MODE ; 
 unsigned int ATTR_MTIME_SET ; 
 unsigned int ATTR_SIZE ; 
 unsigned int ATTR_TIMES_SET ; 
 unsigned int ATTR_UID ; 
 int /*<<< orphan*/  CAP_CHOWN ; 
 int /*<<< orphan*/  CAP_FSETID ; 
 int EPERM ; 
 int /*<<< orphan*/  S_ISGID ; 
 int /*<<< orphan*/  capable (int /*<<< orphan*/ ) ; 
 scalar_t__ current_fsuid () ; 
 int /*<<< orphan*/  in_group_p (scalar_t__) ; 
 int inode_newsize_ok (struct inode const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  is_owner_or_cap (struct inode const*) ; 

int inode_change_ok(const struct inode *inode, struct iattr *attr)
{
	unsigned int ia_valid = attr->ia_valid;

	/*
	 * First check size constraints.  These can't be overriden using
	 * ATTR_FORCE.
	 */
	if (ia_valid & ATTR_SIZE) {
		int error = inode_newsize_ok(inode, attr->ia_size);
		if (error)
			return error;
	}

	/* If force is set do it anyway. */
	if (ia_valid & ATTR_FORCE)
		return 0;

	/* Make sure a caller can chown. */
	if ((ia_valid & ATTR_UID) &&
	    (current_fsuid() != inode->i_uid ||
	     attr->ia_uid != inode->i_uid) && !capable(CAP_CHOWN))
		return -EPERM;

	/* Make sure caller can chgrp. */
	if ((ia_valid & ATTR_GID) &&
	    (current_fsuid() != inode->i_uid ||
	    (!in_group_p(attr->ia_gid) && attr->ia_gid != inode->i_gid)) &&
	    !capable(CAP_CHOWN))
		return -EPERM;

	/* Make sure a caller can chmod. */
	if (ia_valid & ATTR_MODE) {
		if (!is_owner_or_cap(inode))
			return -EPERM;
		/* Also check the setgid bit! */
		if (!in_group_p((ia_valid & ATTR_GID) ? attr->ia_gid :
				inode->i_gid) && !capable(CAP_FSETID))
			attr->ia_mode &= ~S_ISGID;
	}

	/* Check for setting the inode time. */
	if (ia_valid & (ATTR_MTIME_SET | ATTR_ATIME_SET | ATTR_TIMES_SET)) {
		if (!is_owner_or_cap(inode))
			return -EPERM;
	}

	return 0;
}