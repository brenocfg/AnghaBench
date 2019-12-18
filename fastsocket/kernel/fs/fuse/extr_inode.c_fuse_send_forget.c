#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  void* u64 ;
struct TYPE_5__ {void* nodeid; int /*<<< orphan*/  opcode; } ;
struct TYPE_7__ {int numargs; TYPE_2__* args; TYPE_1__ h; } ;
struct fuse_forget_in {void* nlookup; } ;
struct TYPE_8__ {struct fuse_forget_in forget_in; } ;
struct fuse_req {TYPE_3__ in; TYPE_4__ misc; } ;
struct fuse_conn {int dummy; } ;
struct TYPE_6__ {int size; struct fuse_forget_in* value; } ;

/* Variables and functions */
 int /*<<< orphan*/  FUSE_FORGET ; 
 int /*<<< orphan*/  fuse_request_send_noreply (struct fuse_conn*,struct fuse_req*) ; 

void fuse_send_forget(struct fuse_conn *fc, struct fuse_req *req,
		      u64 nodeid, u64 nlookup)
{
	struct fuse_forget_in *inarg = &req->misc.forget_in;
	inarg->nlookup = nlookup;
	req->in.h.opcode = FUSE_FORGET;
	req->in.h.nodeid = nodeid;
	req->in.numargs = 1;
	req->in.args[0].size = sizeof(struct fuse_forget_in);
	req->in.args[0].value = inarg;
	fuse_request_send_noreply(fc, req);
}