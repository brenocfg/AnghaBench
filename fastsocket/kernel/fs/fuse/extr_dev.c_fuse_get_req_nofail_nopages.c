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
struct fuse_req {int waiting; } ;
struct fuse_conn {int /*<<< orphan*/  blocked; int /*<<< orphan*/  blocked_waitq; int /*<<< orphan*/  num_waiting; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fuse_req_init_context (struct fuse_req*) ; 
 struct fuse_req* fuse_request_alloc (int /*<<< orphan*/ ) ; 
 struct fuse_req* get_reserved_req (struct fuse_conn*,struct file*) ; 
 int /*<<< orphan*/  wait_event (int /*<<< orphan*/ ,int) ; 

struct fuse_req *fuse_get_req_nofail_nopages(struct fuse_conn *fc,
					     struct file *file)
{
	struct fuse_req *req;

	atomic_inc(&fc->num_waiting);
	wait_event(fc->blocked_waitq, !fc->blocked);
	req = fuse_request_alloc(0);
	if (!req)
		req = get_reserved_req(fc, file);

	fuse_req_init_context(req);
	req->waiting = 1;
	return req;
}