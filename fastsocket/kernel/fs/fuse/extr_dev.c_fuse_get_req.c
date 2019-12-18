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
struct fuse_conn {int /*<<< orphan*/  num_waiting; int /*<<< orphan*/  connected; int /*<<< orphan*/  blocked; int /*<<< orphan*/  blocked_waitq; } ;
typedef  int /*<<< orphan*/  sigset_t ;

/* Variables and functions */
 int EINTR ; 
 int ENOMEM ; 
 int ENOTCONN ; 
 struct fuse_req* ERR_PTR (int) ; 
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  block_sigs (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fuse_req_init_context (struct fuse_req*) ; 
 struct fuse_req* fuse_request_alloc (unsigned int) ; 
 int /*<<< orphan*/  restore_sigs (int /*<<< orphan*/ *) ; 
 int wait_event_interruptible (int /*<<< orphan*/ ,int) ; 

struct fuse_req *fuse_get_req(struct fuse_conn *fc, unsigned npages)
{
	struct fuse_req *req;
	sigset_t oldset;
	int intr;
	int err;

	atomic_inc(&fc->num_waiting);
	block_sigs(&oldset);
	intr = wait_event_interruptible(fc->blocked_waitq, !fc->blocked);
	restore_sigs(&oldset);
	err = -EINTR;
	if (intr)
		goto out;

	err = -ENOTCONN;
	if (!fc->connected)
		goto out;

	req = fuse_request_alloc(npages);
	err = -ENOMEM;
	if (!req)
		goto out;

	fuse_req_init_context(req);
	req->waiting = 1;
	return req;

 out:
	atomic_dec(&fc->num_waiting);
	return ERR_PTR(err);
}