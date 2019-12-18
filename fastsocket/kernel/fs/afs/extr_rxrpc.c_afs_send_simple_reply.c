#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct msghdr {int msg_iovlen; scalar_t__ msg_flags; scalar_t__ msg_controllen; int /*<<< orphan*/ * msg_control; struct iovec* msg_iov; scalar_t__ msg_namelen; int /*<<< orphan*/ * msg_name; } ;
struct iovec {size_t iov_len; void* iov_base; } ;
struct afs_call {TYPE_1__* type; int /*<<< orphan*/ * rxcall; int /*<<< orphan*/  state; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* destructor ) (struct afs_call*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  AFS_CALL_AWAIT_ACK ; 
 int ENOMEM ; 
 int /*<<< orphan*/  RX_USER_ABORT ; 
 int /*<<< orphan*/  _debug (char*) ; 
 int /*<<< orphan*/  _enter (char*) ; 
 int /*<<< orphan*/  _leave (char*) ; 
 int /*<<< orphan*/  afs_free_call (struct afs_call*) ; 
 int /*<<< orphan*/  rxrpc_kernel_abort_call (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rxrpc_kernel_end_call (int /*<<< orphan*/ *) ; 
 int rxrpc_kernel_send_data (int /*<<< orphan*/ *,struct msghdr*,size_t) ; 
 int /*<<< orphan*/  stub1 (struct afs_call*) ; 

void afs_send_simple_reply(struct afs_call *call, const void *buf, size_t len)
{
	struct msghdr msg;
	struct iovec iov[1];
	int n;

	_enter("");

	iov[0].iov_base		= (void *) buf;
	iov[0].iov_len		= len;
	msg.msg_name		= NULL;
	msg.msg_namelen		= 0;
	msg.msg_iov		= iov;
	msg.msg_iovlen		= 1;
	msg.msg_control		= NULL;
	msg.msg_controllen	= 0;
	msg.msg_flags		= 0;

	call->state = AFS_CALL_AWAIT_ACK;
	n = rxrpc_kernel_send_data(call->rxcall, &msg, len);
	if (n >= 0) {
		_leave(" [replied]");
		return;
	}
	if (n == -ENOMEM) {
		_debug("oom");
		rxrpc_kernel_abort_call(call->rxcall, RX_USER_ABORT);
	}
	rxrpc_kernel_end_call(call->rxcall);
	call->rxcall = NULL;
	call->type->destructor(call);
	afs_free_call(call);
	_leave(" [error]");
}