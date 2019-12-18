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
struct fuse_conn {int /*<<< orphan*/  lock; int /*<<< orphan*/  processing; int /*<<< orphan*/  pending; scalar_t__ connected; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  end_requests (struct fuse_conn*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fuse_conn_put (struct fuse_conn*) ; 
 struct fuse_conn* fuse_get_conn (struct file*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

int fuse_dev_release(struct inode *inode, struct file *file)
{
	struct fuse_conn *fc = fuse_get_conn(file);
	if (fc) {
		spin_lock(&fc->lock);
		fc->connected = 0;
		end_requests(fc, &fc->pending);
		end_requests(fc, &fc->processing);
		spin_unlock(&fc->lock);
		fuse_conn_put(fc);
	}

	return 0;
}