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
typedef  int /*<<< orphan*/  u32 ;
struct rxrpc_sock {int dummy; } ;
struct rxrpc_call {scalar_t__ state; } ;
struct msghdr {int dummy; } ;
struct kiocb {int dummy; } ;
typedef  enum rxrpc_command { ____Placeholder_rxrpc_command } rxrpc_command ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 int EBADSLT ; 
 int EPROTO ; 
 int ESHUTDOWN ; 
 scalar_t__ IS_ERR (struct rxrpc_call*) ; 
 int PTR_ERR (struct rxrpc_call*) ; 
 scalar_t__ RXRPC_CALL_CLIENT_SEND_REQUEST ; 
 scalar_t__ RXRPC_CALL_COMPLETE ; 
 scalar_t__ RXRPC_CALL_SERVER_ACK_REQUEST ; 
 scalar_t__ RXRPC_CALL_SERVER_SEND_REPLY ; 
 int RXRPC_CMD_ACCEPT ; 
#define  RXRPC_CMD_SEND_ABORT 129 
#define  RXRPC_CMD_SEND_DATA 128 
 int /*<<< orphan*/  _enter (char*) ; 
 int /*<<< orphan*/  _leave (char*,int) ; 
 struct rxrpc_call* rxrpc_accept_call (struct rxrpc_sock*,unsigned long) ; 
 struct rxrpc_call* rxrpc_find_server_call (struct rxrpc_sock*,unsigned long) ; 
 int /*<<< orphan*/  rxrpc_put_call (struct rxrpc_call*) ; 
 int /*<<< orphan*/  rxrpc_send_abort (struct rxrpc_call*,int /*<<< orphan*/ ) ; 
 int rxrpc_send_data (struct kiocb*,struct rxrpc_sock*,struct rxrpc_call*,struct msghdr*,size_t) ; 
 int rxrpc_sendmsg_cmsg (struct rxrpc_sock*,struct msghdr*,unsigned long*,int*,int /*<<< orphan*/ *,int) ; 

int rxrpc_server_sendmsg(struct kiocb *iocb, struct rxrpc_sock *rx,
			 struct msghdr *msg, size_t len)
{
	enum rxrpc_command cmd;
	struct rxrpc_call *call;
	unsigned long user_call_ID = 0;
	u32 abort_code = 0;
	int ret;

	_enter("");

	ret = rxrpc_sendmsg_cmsg(rx, msg, &user_call_ID, &cmd, &abort_code,
				 true);
	if (ret < 0)
		return ret;

	if (cmd == RXRPC_CMD_ACCEPT) {
		call = rxrpc_accept_call(rx, user_call_ID);
		if (IS_ERR(call))
			return PTR_ERR(call);
		rxrpc_put_call(call);
		return 0;
	}

	call = rxrpc_find_server_call(rx, user_call_ID);
	if (!call)
		return -EBADSLT;
	if (call->state >= RXRPC_CALL_COMPLETE) {
		ret = -ESHUTDOWN;
		goto out;
	}

	switch (cmd) {
	case RXRPC_CMD_SEND_DATA:
		if (call->state != RXRPC_CALL_CLIENT_SEND_REQUEST &&
		    call->state != RXRPC_CALL_SERVER_ACK_REQUEST &&
		    call->state != RXRPC_CALL_SERVER_SEND_REPLY) {
			/* Tx phase not yet begun for this call */
			ret = -EPROTO;
			break;
		}

		ret = rxrpc_send_data(iocb, rx, call, msg, len);
		break;

	case RXRPC_CMD_SEND_ABORT:
		rxrpc_send_abort(call, abort_code);
		break;
	default:
		BUG();
	}

	out:
	rxrpc_put_call(call);
	_leave(" = %d", ret);
	return ret;
}