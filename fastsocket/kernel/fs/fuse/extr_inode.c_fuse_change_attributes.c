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
typedef  scalar_t__ u64 ;
struct timespec {int /*<<< orphan*/  tv_nsec; int /*<<< orphan*/  tv_sec; } ;
struct inode {int /*<<< orphan*/  i_mapping; int /*<<< orphan*/  i_mode; int /*<<< orphan*/  i_size; struct timespec i_mtime; } ;
struct fuse_inode {scalar_t__ attr_version; } ;
struct fuse_conn {scalar_t__ auto_inval_data; int /*<<< orphan*/  lock; } ;
struct fuse_attr {int /*<<< orphan*/  mtimensec; int /*<<< orphan*/  mtime; int /*<<< orphan*/  size; } ;
typedef  int /*<<< orphan*/  loff_t ;

/* Variables and functions */
 scalar_t__ S_ISREG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fuse_change_attributes_common (struct inode*,struct fuse_attr*,scalar_t__) ; 
 struct fuse_conn* get_fuse_conn (struct inode*) ; 
 struct fuse_inode* get_fuse_inode (struct inode*) ; 
 int /*<<< orphan*/  i_size_write (struct inode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  invalidate_inode_pages2 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  timespec_equal (struct timespec*,struct timespec*) ; 
 int /*<<< orphan*/  truncate_pagecache (struct inode*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void fuse_change_attributes(struct inode *inode, struct fuse_attr *attr,
			    u64 attr_valid, u64 attr_version)
{
	struct fuse_conn *fc = get_fuse_conn(inode);
	struct fuse_inode *fi = get_fuse_inode(inode);
	loff_t oldsize;
	struct timespec old_mtime;

	spin_lock(&fc->lock);
	if (attr_version != 0 && fi->attr_version > attr_version) {
		spin_unlock(&fc->lock);
		return;
	}

	old_mtime = inode->i_mtime;
	fuse_change_attributes_common(inode, attr, attr_valid);

	oldsize = inode->i_size;
	i_size_write(inode, attr->size);
	spin_unlock(&fc->lock);

	if (S_ISREG(inode->i_mode)) {
		bool inval = false;

		if (oldsize != attr->size) {
			truncate_pagecache(inode, oldsize, attr->size);
			inval = true;
		} else if (fc->auto_inval_data) {
			struct timespec new_mtime = {
				.tv_sec = attr->mtime,
				.tv_nsec = attr->mtimensec,
			};

			/*
			 * Auto inval mode also checks and invalidates if mtime
			 * has changed.
			 */
			if (!timespec_equal(&old_mtime, &new_mtime))
				inval = true;
		}

		if (inval)
			invalidate_inode_pages2(inode->i_mapping);
	}
}