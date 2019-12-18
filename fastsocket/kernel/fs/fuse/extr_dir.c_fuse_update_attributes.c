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
struct kstat {int /*<<< orphan*/  ino; int /*<<< orphan*/  mode; } ;
struct inode {int dummy; } ;
struct fuse_inode {scalar_t__ i_time; int /*<<< orphan*/  orig_ino; int /*<<< orphan*/  orig_i_mode; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int fuse_do_getattr (struct inode*,struct kstat*,struct file*) ; 
 int /*<<< orphan*/  generic_fillattr (struct inode*,struct kstat*) ; 
 struct fuse_inode* get_fuse_inode (struct inode*) ; 
 scalar_t__ get_jiffies_64 () ; 

int fuse_update_attributes(struct inode *inode, struct kstat *stat,
			   struct file *file, bool *refreshed)
{
	struct fuse_inode *fi = get_fuse_inode(inode);
	int err;
	bool r;

	if (fi->i_time < get_jiffies_64()) {
		r = true;
		err = fuse_do_getattr(inode, stat, file);
	} else {
		r = false;
		err = 0;
		if (stat) {
			generic_fillattr(inode, stat);
			stat->mode = fi->orig_i_mode;
			stat->ino = fi->orig_ino;
		}
	}

	if (refreshed != NULL)
		*refreshed = r;

	return err;
}