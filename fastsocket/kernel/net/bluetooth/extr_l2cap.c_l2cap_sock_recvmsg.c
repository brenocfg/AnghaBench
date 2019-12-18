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
struct socket {struct sock* sk; } ;
struct sock {scalar_t__ sk_state; } ;
struct msghdr {scalar_t__ msg_namelen; } ;
struct l2cap_conn_rsp {void* status; void* result; void* dcid; void* scid; } ;
struct kiocb {int dummy; } ;
typedef  int /*<<< orphan*/  rsp ;
struct TYPE_4__ {scalar_t__ defer_setup; } ;
struct TYPE_3__ {int /*<<< orphan*/  ident; int /*<<< orphan*/  conn; int /*<<< orphan*/  scid; int /*<<< orphan*/  dcid; } ;

/* Variables and functions */
 scalar_t__ BT_CONFIG ; 
 scalar_t__ BT_CONNECT2 ; 
 int /*<<< orphan*/  L2CAP_CONN_RSP ; 
 int /*<<< orphan*/  L2CAP_CR_SUCCESS ; 
 int /*<<< orphan*/  L2CAP_CS_NO_INFO ; 
 TYPE_2__* bt_sk (struct sock*) ; 
 int bt_sock_recvmsg (struct kiocb*,struct socket*,struct msghdr*,size_t,int) ; 
 void* cpu_to_le16 (int /*<<< orphan*/ ) ; 
 TYPE_1__* l2cap_pi (struct sock*) ; 
 int /*<<< orphan*/  l2cap_send_cmd (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,struct l2cap_conn_rsp*) ; 
 int /*<<< orphan*/  lock_sock (struct sock*) ; 
 int /*<<< orphan*/  release_sock (struct sock*) ; 

__attribute__((used)) static int l2cap_sock_recvmsg(struct kiocb *iocb, struct socket *sock, struct msghdr *msg, size_t len, int flags)
{
	struct sock *sk = sock->sk;

	lock_sock(sk);

	msg->msg_namelen = 0;

	if (sk->sk_state == BT_CONNECT2 && bt_sk(sk)->defer_setup) {
		struct l2cap_conn_rsp rsp;

		sk->sk_state = BT_CONFIG;

		rsp.scid   = cpu_to_le16(l2cap_pi(sk)->dcid);
		rsp.dcid   = cpu_to_le16(l2cap_pi(sk)->scid);
		rsp.result = cpu_to_le16(L2CAP_CR_SUCCESS);
		rsp.status = cpu_to_le16(L2CAP_CS_NO_INFO);
		l2cap_send_cmd(l2cap_pi(sk)->conn, l2cap_pi(sk)->ident,
					L2CAP_CONN_RSP, sizeof(rsp), &rsp);

		release_sock(sk);
		return 0;
	}

	release_sock(sk);

	return bt_sock_recvmsg(iocb, sock, msg, len, flags);
}