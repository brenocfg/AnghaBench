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
struct fuse_req {int /*<<< orphan*/  max_pages; int /*<<< orphan*/  page_descs; int /*<<< orphan*/  pages; struct file* stolen_file; } ;
struct fuse_file {struct fuse_req* reserved_req; } ;
struct fuse_conn {int /*<<< orphan*/  lock; int /*<<< orphan*/  reserved_req_waitq; } ;
struct file {struct fuse_file* private_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (struct fuse_req*) ; 
 int /*<<< orphan*/  fput (struct file*) ; 
 int /*<<< orphan*/  fuse_request_init (struct fuse_req*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up_all (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void put_reserved_req(struct fuse_conn *fc, struct fuse_req *req)
{
	struct file *file = req->stolen_file;
	struct fuse_file *ff = file->private_data;

	spin_lock(&fc->lock);
	fuse_request_init(req, req->pages, req->page_descs, req->max_pages);
	BUG_ON(ff->reserved_req);
	ff->reserved_req = req;
	wake_up_all(&fc->reserved_req_waitq);
	spin_unlock(&fc->lock);
	fput(file);
}