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
struct fuse_req {int locked; scalar_t__ aborted; } ;
struct fuse_conn {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int ENOENT ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int lock_request(struct fuse_conn *fc, struct fuse_req *req)
{
	int err = 0;
	if (req) {
		spin_lock(&fc->lock);
		if (req->aborted)
			err = -ENOENT;
		else
			req->locked = 1;
		spin_unlock(&fc->lock);
	}
	return err;
}