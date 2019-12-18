#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  sin_addr; int /*<<< orphan*/  sin_port; int /*<<< orphan*/  sin_family; } ;
struct TYPE_5__ {TYPE_1__ sin; } ;
struct sockaddr_rxrpc {int transport_len; TYPE_2__ transport; int /*<<< orphan*/  transport_type; int /*<<< orphan*/  srx_service; int /*<<< orphan*/  srx_family; } ;
struct rxrpc_call {int dummy; } ;
struct msghdr {int msg_iovlen; int /*<<< orphan*/  msg_flags; scalar_t__ msg_controllen; int /*<<< orphan*/ * msg_control; struct iovec* msg_iov; scalar_t__ msg_namelen; int /*<<< orphan*/ * msg_name; } ;
struct kvec {int /*<<< orphan*/  iov_len; int /*<<< orphan*/  iov_base; } ;
struct iovec {int dummy; } ;
struct in_addr {int /*<<< orphan*/  s_addr; } ;
struct afs_wait_mode {int (* wait ) (struct afs_call*) ;} ;
struct afs_call {TYPE_3__* type; struct rxrpc_call* rxcall; scalar_t__ send_pages; int /*<<< orphan*/  request_size; int /*<<< orphan*/  state; int /*<<< orphan*/  request; int /*<<< orphan*/ * key; int /*<<< orphan*/  port; int /*<<< orphan*/  service_id; int /*<<< orphan*/  async_work; struct afs_wait_mode const* wait_mode; } ;
typedef  int /*<<< orphan*/  srx ;
typedef  int /*<<< orphan*/  gfp_t ;
struct TYPE_6__ {int /*<<< orphan*/  (* destructor ) (struct afs_call*) ;int /*<<< orphan*/ * name; } ;

/* Variables and functions */
 int /*<<< orphan*/  AFS_CALL_AWAIT_REPLY ; 
 int /*<<< orphan*/  AF_INET ; 
 int /*<<< orphan*/  AF_RXRPC ; 
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ IS_ERR (struct rxrpc_call*) ; 
 int /*<<< orphan*/  MSG_MORE ; 
 int PTR_ERR (struct rxrpc_call*) ; 
 int /*<<< orphan*/  RX_USER_ABORT ; 
 int /*<<< orphan*/  SOCK_DGRAM ; 
 int /*<<< orphan*/  _debug (char*,struct afs_call*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _enter (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _leave (char*,int) ; 
 int /*<<< orphan*/  afs_free_call (struct afs_call*) ; 
 int /*<<< orphan*/  afs_outstanding_calls ; 
 int /*<<< orphan*/  afs_process_async_call ; 
 int afs_send_pages (struct afs_call*,struct msghdr*,struct kvec*) ; 
 int /*<<< orphan*/  afs_socket ; 
 int /*<<< orphan*/  atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  key_serial (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,struct in_addr*,int) ; 
 int /*<<< orphan*/  memset (struct sockaddr_rxrpc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ntohs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rxrpc_kernel_abort_call (struct rxrpc_call*,int /*<<< orphan*/ ) ; 
 struct rxrpc_call* rxrpc_kernel_begin_call (int /*<<< orphan*/ ,struct sockaddr_rxrpc*,int /*<<< orphan*/ *,unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rxrpc_kernel_end_call (struct rxrpc_call*) ; 
 int rxrpc_kernel_send_data (struct rxrpc_call*,struct msghdr*,int /*<<< orphan*/ ) ; 
 int stub1 (struct afs_call*) ; 
 int /*<<< orphan*/  stub2 (struct afs_call*) ; 

int afs_make_call(struct in_addr *addr, struct afs_call *call, gfp_t gfp,
		  const struct afs_wait_mode *wait_mode)
{
	struct sockaddr_rxrpc srx;
	struct rxrpc_call *rxcall;
	struct msghdr msg;
	struct kvec iov[1];
	int ret;

	_enter("%x,{%d},", addr->s_addr, ntohs(call->port));

	ASSERT(call->type != NULL);
	ASSERT(call->type->name != NULL);

	_debug("____MAKE %p{%s,%x} [%d]____",
	       call, call->type->name, key_serial(call->key),
	       atomic_read(&afs_outstanding_calls));

	call->wait_mode = wait_mode;
	INIT_WORK(&call->async_work, afs_process_async_call);

	memset(&srx, 0, sizeof(srx));
	srx.srx_family = AF_RXRPC;
	srx.srx_service = call->service_id;
	srx.transport_type = SOCK_DGRAM;
	srx.transport_len = sizeof(srx.transport.sin);
	srx.transport.sin.sin_family = AF_INET;
	srx.transport.sin.sin_port = call->port;
	memcpy(&srx.transport.sin.sin_addr, addr, 4);

	/* create a call */
	rxcall = rxrpc_kernel_begin_call(afs_socket, &srx, call->key,
					 (unsigned long) call, gfp);
	call->key = NULL;
	if (IS_ERR(rxcall)) {
		ret = PTR_ERR(rxcall);
		goto error_kill_call;
	}

	call->rxcall = rxcall;

	/* send the request */
	iov[0].iov_base	= call->request;
	iov[0].iov_len	= call->request_size;

	msg.msg_name		= NULL;
	msg.msg_namelen		= 0;
	msg.msg_iov		= (struct iovec *) iov;
	msg.msg_iovlen		= 1;
	msg.msg_control		= NULL;
	msg.msg_controllen	= 0;
	msg.msg_flags		= (call->send_pages ? MSG_MORE : 0);

	/* have to change the state *before* sending the last packet as RxRPC
	 * might give us the reply before it returns from sending the
	 * request */
	if (!call->send_pages)
		call->state = AFS_CALL_AWAIT_REPLY;
	ret = rxrpc_kernel_send_data(rxcall, &msg, call->request_size);
	if (ret < 0)
		goto error_do_abort;

	if (call->send_pages) {
		ret = afs_send_pages(call, &msg, iov);
		if (ret < 0)
			goto error_do_abort;
	}

	/* at this point, an async call may no longer exist as it may have
	 * already completed */
	return wait_mode->wait(call);

error_do_abort:
	rxrpc_kernel_abort_call(rxcall, RX_USER_ABORT);
	rxrpc_kernel_end_call(rxcall);
	call->rxcall = NULL;
error_kill_call:
	call->type->destructor(call);
	afs_free_call(call);
	_leave(" = %d", ret);
	return ret;
}