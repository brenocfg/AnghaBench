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
struct fuse_req {struct file* stolen_file; } ;
struct fuse_file {struct fuse_req* reserved_req; } ;
struct fuse_conn {int /*<<< orphan*/  lock; int /*<<< orphan*/  reserved_req_waitq; } ;
struct file {struct fuse_file* private_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  get_file (struct file*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wait_event (int /*<<< orphan*/ ,struct fuse_req*) ; 

__attribute__((used)) static struct fuse_req *get_reserved_req(struct fuse_conn *fc,
					 struct file *file)
{
	struct fuse_req *req = NULL;
	struct fuse_file *ff = file->private_data;

	do {
		wait_event(fc->reserved_req_waitq, ff->reserved_req);
		spin_lock(&fc->lock);
		if (ff->reserved_req) {
			req = ff->reserved_req;
			ff->reserved_req = NULL;
			get_file(file);
			req->stolen_file = file;
		}
		spin_unlock(&fc->lock);
	} while (!req);

	return req;
}