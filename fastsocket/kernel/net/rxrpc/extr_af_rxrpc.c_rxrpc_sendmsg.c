#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct socket {int /*<<< orphan*/  sk; } ;
struct rxrpc_transport {int /*<<< orphan*/  usage; } ;
struct TYPE_3__ {int sk_state; } ;
struct rxrpc_sock {TYPE_1__ sk; struct rxrpc_transport* trans; } ;
struct msghdr {int msg_flags; int /*<<< orphan*/  msg_name; int /*<<< orphan*/  msg_namelen; } ;
struct kiocb {int dummy; } ;

/* Variables and functions */
 int EISCONN ; 
 int ENOTCONN ; 
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (struct rxrpc_transport*) ; 
 int MSG_OOB ; 
 int PTR_ERR (struct rxrpc_transport*) ; 
#define  RXRPC_CLIENT_BOUND 131 
#define  RXRPC_CLIENT_CONNECTED 130 
#define  RXRPC_SERVER_BOUND 129 
#define  RXRPC_SERVER_LISTENING 128 
 int /*<<< orphan*/  _enter (char*,int,size_t) ; 
 int /*<<< orphan*/  _leave (char*,int) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lock_sock (TYPE_1__*) ; 
 int /*<<< orphan*/  release_sock (TYPE_1__*) ; 
 int rxrpc_client_sendmsg (struct kiocb*,struct rxrpc_sock*,struct rxrpc_transport*,struct msghdr*,size_t) ; 
 struct rxrpc_transport* rxrpc_name_to_transport (struct socket*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rxrpc_put_transport (struct rxrpc_transport*) ; 
 int rxrpc_server_sendmsg (struct kiocb*,struct rxrpc_sock*,struct msghdr*,size_t) ; 
 struct rxrpc_sock* rxrpc_sk (int /*<<< orphan*/ ) ; 
 int rxrpc_validate_address (struct rxrpc_sock*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int rxrpc_sendmsg(struct kiocb *iocb, struct socket *sock,
			 struct msghdr *m, size_t len)
{
	struct rxrpc_transport *trans;
	struct rxrpc_sock *rx = rxrpc_sk(sock->sk);
	int ret;

	_enter(",{%d},,%zu", rx->sk.sk_state, len);

	if (m->msg_flags & MSG_OOB)
		return -EOPNOTSUPP;

	if (m->msg_name) {
		ret = rxrpc_validate_address(rx, m->msg_name, m->msg_namelen);
		if (ret < 0) {
			_leave(" = %d [bad addr]", ret);
			return ret;
		}
	}

	trans = NULL;
	lock_sock(&rx->sk);

	if (m->msg_name) {
		ret = -EISCONN;
		trans = rxrpc_name_to_transport(sock, m->msg_name,
						m->msg_namelen, 0, GFP_KERNEL);
		if (IS_ERR(trans)) {
			ret = PTR_ERR(trans);
			trans = NULL;
			goto out;
		}
	} else {
		trans = rx->trans;
		if (trans)
			atomic_inc(&trans->usage);
	}

	switch (rx->sk.sk_state) {
	case RXRPC_SERVER_LISTENING:
		if (!m->msg_name) {
			ret = rxrpc_server_sendmsg(iocb, rx, m, len);
			break;
		}
	case RXRPC_SERVER_BOUND:
	case RXRPC_CLIENT_BOUND:
		if (!m->msg_name) {
			ret = -ENOTCONN;
			break;
		}
	case RXRPC_CLIENT_CONNECTED:
		ret = rxrpc_client_sendmsg(iocb, rx, trans, m, len);
		break;
	default:
		ret = -ENOTCONN;
		break;
	}

out:
	release_sock(&rx->sk);
	if (trans)
		rxrpc_put_transport(trans);
	_leave(" = %d", ret);
	return ret;
}