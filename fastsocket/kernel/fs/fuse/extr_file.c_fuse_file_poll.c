#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int error; } ;
struct TYPE_12__ {int numargs; TYPE_5__ h; TYPE_4__* args; } ;
struct TYPE_7__ {int /*<<< orphan*/  nodeid; int /*<<< orphan*/  opcode; } ;
struct TYPE_9__ {int numargs; TYPE_2__* args; TYPE_1__ h; } ;
struct fuse_req {TYPE_6__ out; TYPE_3__ in; } ;
struct fuse_poll_out {int revents; } ;
struct fuse_poll_in {int /*<<< orphan*/  flags; int /*<<< orphan*/  kh; int /*<<< orphan*/  fh; } ;
struct fuse_file {int /*<<< orphan*/  nodeid; int /*<<< orphan*/  poll_wait; int /*<<< orphan*/  kh; int /*<<< orphan*/  fh; struct fuse_conn* fc; } ;
struct fuse_conn {int no_poll; } ;
struct file {struct fuse_file* private_data; } ;
typedef  int /*<<< orphan*/  poll_table ;
typedef  int /*<<< orphan*/  outarg ;
typedef  int /*<<< orphan*/  inarg ;
struct TYPE_10__ {int size; struct fuse_poll_out* value; } ;
struct TYPE_8__ {int size; struct fuse_poll_in* value; } ;

/* Variables and functions */
 int DEFAULT_POLLMASK ; 
 int ENOSYS ; 
 int /*<<< orphan*/  FUSE_POLL ; 
 int /*<<< orphan*/  FUSE_POLL_SCHEDULE_NOTIFY ; 
 scalar_t__ IS_ERR (struct fuse_req*) ; 
 int POLLERR ; 
 struct fuse_req* fuse_get_req_nopages (struct fuse_conn*) ; 
 int /*<<< orphan*/  fuse_put_request (struct fuse_conn*,struct fuse_req*) ; 
 int /*<<< orphan*/  fuse_register_polled_file (struct fuse_conn*,struct fuse_file*) ; 
 int /*<<< orphan*/  fuse_request_send (struct fuse_conn*,struct fuse_req*) ; 
 int /*<<< orphan*/  poll_wait (struct file*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ waitqueue_active (int /*<<< orphan*/ *) ; 

unsigned fuse_file_poll(struct file *file, poll_table *wait)
{
	struct fuse_file *ff = file->private_data;
	struct fuse_conn *fc = ff->fc;
	struct fuse_poll_in inarg = { .fh = ff->fh, .kh = ff->kh };
	struct fuse_poll_out outarg;
	struct fuse_req *req;
	int err;

	if (fc->no_poll)
		return DEFAULT_POLLMASK;

	poll_wait(file, &ff->poll_wait, wait);

	/*
	 * Ask for notification iff there's someone waiting for it.
	 * The client may ignore the flag and always notify.
	 */
	if (waitqueue_active(&ff->poll_wait)) {
		inarg.flags |= FUSE_POLL_SCHEDULE_NOTIFY;
		fuse_register_polled_file(fc, ff);
	}

	req = fuse_get_req_nopages(fc);
	if (IS_ERR(req))
		return POLLERR;

	req->in.h.opcode = FUSE_POLL;
	req->in.h.nodeid = ff->nodeid;
	req->in.numargs = 1;
	req->in.args[0].size = sizeof(inarg);
	req->in.args[0].value = &inarg;
	req->out.numargs = 1;
	req->out.args[0].size = sizeof(outarg);
	req->out.args[0].value = &outarg;
	fuse_request_send(fc, req);
	err = req->out.h.error;
	fuse_put_request(fc, req);

	if (!err)
		return outarg.revents;
	if (err == -ENOSYS) {
		fc->no_poll = 1;
		return DEFAULT_POLLMASK;
	}
	return POLLERR;
}