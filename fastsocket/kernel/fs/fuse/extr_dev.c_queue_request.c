#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ len; int /*<<< orphan*/  unique; } ;
struct TYPE_4__ {scalar_t__ args; int /*<<< orphan*/  numargs; TYPE_1__ h; } ;
struct fuse_req {int waiting; int /*<<< orphan*/  state; int /*<<< orphan*/  list; TYPE_2__ in; } ;
struct fuse_in_header {int dummy; } ;
struct fuse_conn {int /*<<< orphan*/  fasync; int /*<<< orphan*/  waitq; int /*<<< orphan*/  num_waiting; int /*<<< orphan*/  pending; } ;
struct fuse_arg {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  FUSE_REQ_PENDING ; 
 int /*<<< orphan*/  POLL_IN ; 
 int /*<<< orphan*/  SIGIO ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fuse_get_unique (struct fuse_conn*) ; 
 int /*<<< orphan*/  kill_fasync (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ len_args (int /*<<< orphan*/ ,struct fuse_arg*) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void queue_request(struct fuse_conn *fc, struct fuse_req *req)
{
	req->in.h.unique = fuse_get_unique(fc);
	req->in.h.len = sizeof(struct fuse_in_header) +
		len_args(req->in.numargs, (struct fuse_arg *) req->in.args);
	list_add_tail(&req->list, &fc->pending);
	req->state = FUSE_REQ_PENDING;
	if (!req->waiting) {
		req->waiting = 1;
		atomic_inc(&fc->num_waiting);
	}
	wake_up(&fc->waitq);
	kill_fasync(&fc->fasync, SIGIO, POLL_IN);
}