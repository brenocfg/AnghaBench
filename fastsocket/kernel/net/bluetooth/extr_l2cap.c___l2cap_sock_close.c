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
struct sock {int sk_state; int /*<<< orphan*/  sk_type; int /*<<< orphan*/  sk_sndtimeo; int /*<<< orphan*/  sk_socket; } ;
struct l2cap_conn_rsp {void* status; void* result; void* dcid; void* scid; } ;
struct l2cap_conn {int dummy; } ;
typedef  int /*<<< orphan*/  rsp ;
typedef  int /*<<< orphan*/  __u16 ;
struct TYPE_4__ {int /*<<< orphan*/  defer_setup; } ;
struct TYPE_3__ {int /*<<< orphan*/  ident; int /*<<< orphan*/  scid; int /*<<< orphan*/  dcid; struct l2cap_conn* conn; } ;

/* Variables and functions */
#define  BT_CONFIG 133 
#define  BT_CONNECT 132 
#define  BT_CONNECT2 131 
#define  BT_CONNECTED 130 
 int /*<<< orphan*/  BT_DBG (char*,struct sock*,int,int /*<<< orphan*/ ) ; 
#define  BT_DISCONN 129 
#define  BT_LISTEN 128 
 int /*<<< orphan*/  L2CAP_CONN_RSP ; 
 int /*<<< orphan*/  L2CAP_CR_BAD_PSM ; 
 int /*<<< orphan*/  L2CAP_CR_SEC_BLOCK ; 
 int /*<<< orphan*/  L2CAP_CS_NO_INFO ; 
 int /*<<< orphan*/  SOCK_SEQPACKET ; 
 int /*<<< orphan*/  SOCK_ZAPPED ; 
 TYPE_2__* bt_sk (struct sock*) ; 
 void* cpu_to_le16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  l2cap_chan_del (struct sock*,int) ; 
 TYPE_1__* l2cap_pi (struct sock*) ; 
 int /*<<< orphan*/  l2cap_send_cmd (struct l2cap_conn*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,struct l2cap_conn_rsp*) ; 
 int /*<<< orphan*/  l2cap_send_disconn_req (struct l2cap_conn*,struct sock*) ; 
 int /*<<< orphan*/  l2cap_sock_cleanup_listen (struct sock*) ; 
 int /*<<< orphan*/  l2cap_sock_set_timer (struct sock*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sock_set_flag (struct sock*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void __l2cap_sock_close(struct sock *sk, int reason)
{
	BT_DBG("sk %p state %d socket %p", sk, sk->sk_state, sk->sk_socket);

	switch (sk->sk_state) {
	case BT_LISTEN:
		l2cap_sock_cleanup_listen(sk);
		break;

	case BT_CONNECTED:
	case BT_CONFIG:
		if (sk->sk_type == SOCK_SEQPACKET) {
			struct l2cap_conn *conn = l2cap_pi(sk)->conn;

			sk->sk_state = BT_DISCONN;
			l2cap_sock_set_timer(sk, sk->sk_sndtimeo);
			l2cap_send_disconn_req(conn, sk);
		} else
			l2cap_chan_del(sk, reason);
		break;

	case BT_CONNECT2:
		if (sk->sk_type == SOCK_SEQPACKET) {
			struct l2cap_conn *conn = l2cap_pi(sk)->conn;
			struct l2cap_conn_rsp rsp;
			__u16 result;

			if (bt_sk(sk)->defer_setup)
				result = L2CAP_CR_SEC_BLOCK;
			else
				result = L2CAP_CR_BAD_PSM;

			rsp.scid   = cpu_to_le16(l2cap_pi(sk)->dcid);
			rsp.dcid   = cpu_to_le16(l2cap_pi(sk)->scid);
			rsp.result = cpu_to_le16(result);
			rsp.status = cpu_to_le16(L2CAP_CS_NO_INFO);
			l2cap_send_cmd(conn, l2cap_pi(sk)->ident,
					L2CAP_CONN_RSP, sizeof(rsp), &rsp);
		} else
			l2cap_chan_del(sk, reason);
		break;

	case BT_CONNECT:
	case BT_DISCONN:
		l2cap_chan_del(sk, reason);
		break;

	default:
		sock_set_flag(sk, SOCK_ZAPPED);
		break;
	}
}