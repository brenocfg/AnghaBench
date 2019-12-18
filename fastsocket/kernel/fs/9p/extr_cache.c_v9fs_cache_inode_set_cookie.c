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
struct v9fs_cookie {int /*<<< orphan*/  lock; int /*<<< orphan*/  fscache; } ;
struct p9_fid {int dummy; } ;
struct inode {int dummy; } ;
struct file {int f_flags; struct p9_fid* private_data; } ;

/* Variables and functions */
 int O_ACCMODE ; 
 int O_RDONLY ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  v9fs_cache_inode_flush_cookie (struct inode*) ; 
 int /*<<< orphan*/  v9fs_cache_inode_get_cookie (struct inode*) ; 
 struct v9fs_cookie* v9fs_inode2cookie (struct inode*) ; 

void v9fs_cache_inode_set_cookie(struct inode *inode, struct file *filp)
{
	struct v9fs_cookie *vcookie = v9fs_inode2cookie(inode);
	struct p9_fid *fid;

	if (!vcookie->fscache)
		return;

	spin_lock(&vcookie->lock);
	fid = filp->private_data;
	if ((filp->f_flags & O_ACCMODE) != O_RDONLY)
		v9fs_cache_inode_flush_cookie(inode);
	else
		v9fs_cache_inode_get_cookie(inode);

	spin_unlock(&vcookie->lock);
}