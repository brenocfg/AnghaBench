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
struct sock {scalar_t__ sk_type; scalar_t__ sk_state; int /*<<< orphan*/  (* sk_data_ready ) (struct sock*,int /*<<< orphan*/ ) ;} ;
struct l2cap_conn_rsp {void* status; void* result; void* dcid; void* scid; int /*<<< orphan*/  psm; } ;
struct l2cap_conn_req {void* status; void* result; void* dcid; void* scid; int /*<<< orphan*/  psm; } ;
struct l2cap_chan_list {int /*<<< orphan*/  lock; struct sock* head; } ;
struct l2cap_conn {struct l2cap_chan_list chan_list; } ;
typedef  int /*<<< orphan*/  rsp ;
typedef  int /*<<< orphan*/  req ;
struct TYPE_4__ {struct sock* parent; scalar_t__ defer_setup; } ;
struct TYPE_3__ {int /*<<< orphan*/  ident; int /*<<< orphan*/  scid; int /*<<< orphan*/  dcid; int /*<<< orphan*/  psm; struct sock* next_c; } ;

/* Variables and functions */
 scalar_t__ BT_CONFIG ; 
 scalar_t__ BT_CONNECT ; 
 scalar_t__ BT_CONNECT2 ; 
 int /*<<< orphan*/  BT_DBG (char*,struct l2cap_conn*) ; 
 int /*<<< orphan*/  L2CAP_CONN_REQ ; 
 int /*<<< orphan*/  L2CAP_CONN_RSP ; 
 int /*<<< orphan*/  L2CAP_CR_PEND ; 
 int /*<<< orphan*/  L2CAP_CR_SUCCESS ; 
 int /*<<< orphan*/  L2CAP_CS_AUTHEN_PEND ; 
 int /*<<< orphan*/  L2CAP_CS_AUTHOR_PEND ; 
 int /*<<< orphan*/  L2CAP_CS_NO_INFO ; 
 scalar_t__ SOCK_SEQPACKET ; 
 int /*<<< orphan*/  bh_lock_sock (struct sock*) ; 
 int /*<<< orphan*/  bh_unlock_sock (struct sock*) ; 
 TYPE_2__* bt_sk (struct sock*) ; 
 void* cpu_to_le16 (int /*<<< orphan*/ ) ; 
 scalar_t__ l2cap_check_security (struct sock*) ; 
 int /*<<< orphan*/  l2cap_get_ident (struct l2cap_conn*) ; 
 TYPE_1__* l2cap_pi (struct sock*) ; 
 int /*<<< orphan*/  l2cap_send_cmd (struct l2cap_conn*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,struct l2cap_conn_rsp*) ; 
 int /*<<< orphan*/  read_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct sock*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void l2cap_conn_start(struct l2cap_conn *conn)
{
	struct l2cap_chan_list *l = &conn->chan_list;
	struct sock *sk;

	BT_DBG("conn %p", conn);

	read_lock(&l->lock);

	for (sk = l->head; sk; sk = l2cap_pi(sk)->next_c) {
		bh_lock_sock(sk);

		if (sk->sk_type != SOCK_SEQPACKET) {
			bh_unlock_sock(sk);
			continue;
		}

		if (sk->sk_state == BT_CONNECT) {
			if (l2cap_check_security(sk)) {
				struct l2cap_conn_req req;
				req.scid = cpu_to_le16(l2cap_pi(sk)->scid);
				req.psm  = l2cap_pi(sk)->psm;

				l2cap_pi(sk)->ident = l2cap_get_ident(conn);

				l2cap_send_cmd(conn, l2cap_pi(sk)->ident,
					L2CAP_CONN_REQ, sizeof(req), &req);
			}
		} else if (sk->sk_state == BT_CONNECT2) {
			struct l2cap_conn_rsp rsp;
			rsp.scid = cpu_to_le16(l2cap_pi(sk)->dcid);
			rsp.dcid = cpu_to_le16(l2cap_pi(sk)->scid);

			if (l2cap_check_security(sk)) {
				if (bt_sk(sk)->defer_setup) {
					struct sock *parent = bt_sk(sk)->parent;
					rsp.result = cpu_to_le16(L2CAP_CR_PEND);
					rsp.status = cpu_to_le16(L2CAP_CS_AUTHOR_PEND);
					parent->sk_data_ready(parent, 0);

				} else {
					sk->sk_state = BT_CONFIG;
					rsp.result = cpu_to_le16(L2CAP_CR_SUCCESS);
					rsp.status = cpu_to_le16(L2CAP_CS_NO_INFO);
				}
			} else {
				rsp.result = cpu_to_le16(L2CAP_CR_PEND);
				rsp.status = cpu_to_le16(L2CAP_CS_AUTHEN_PEND);
			}

			l2cap_send_cmd(conn, l2cap_pi(sk)->ident,
					L2CAP_CONN_RSP, sizeof(rsp), &rsp);
		}

		bh_unlock_sock(sk);
	}

	read_unlock(&l->lock);
}