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
typedef  int /*<<< orphan*/  u8 ;
struct sock {scalar_t__ sk_state; } ;
struct l2cap_conn_rsp {void* status; void* result; void* dcid; void* scid; int /*<<< orphan*/  psm; } ;
struct l2cap_conn_req {void* status; void* result; void* dcid; void* scid; int /*<<< orphan*/  psm; } ;
struct l2cap_chan_list {int /*<<< orphan*/  lock; struct sock* head; } ;
struct l2cap_conn {struct l2cap_chan_list chan_list; } ;
struct hci_conn {struct l2cap_conn* l2cap_data; } ;
typedef  int /*<<< orphan*/  rsp ;
typedef  int /*<<< orphan*/  req ;
typedef  int /*<<< orphan*/  __u16 ;
struct TYPE_2__ {int conf_state; int /*<<< orphan*/  ident; int /*<<< orphan*/  scid; int /*<<< orphan*/  dcid; int /*<<< orphan*/  psm; struct sock* next_c; } ;

/* Variables and functions */
 scalar_t__ BT_CONFIG ; 
 scalar_t__ BT_CONNECT ; 
 scalar_t__ BT_CONNECT2 ; 
 scalar_t__ BT_CONNECTED ; 
 int /*<<< orphan*/  BT_DBG (char*,struct l2cap_conn*) ; 
 scalar_t__ BT_DISCONN ; 
 int HZ ; 
 int L2CAP_CONF_CONNECT_PEND ; 
 int /*<<< orphan*/  L2CAP_CONN_REQ ; 
 int /*<<< orphan*/  L2CAP_CONN_RSP ; 
 int /*<<< orphan*/  L2CAP_CR_SEC_BLOCK ; 
 int /*<<< orphan*/  L2CAP_CR_SUCCESS ; 
 int /*<<< orphan*/  L2CAP_CS_NO_INFO ; 
 int /*<<< orphan*/  bh_lock_sock (struct sock*) ; 
 int /*<<< orphan*/  bh_unlock_sock (struct sock*) ; 
 void* cpu_to_le16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  l2cap_check_encryption (struct sock*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  l2cap_get_ident (struct l2cap_conn*) ; 
 TYPE_1__* l2cap_pi (struct sock*) ; 
 int /*<<< orphan*/  l2cap_send_cmd (struct l2cap_conn*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,struct l2cap_conn_rsp*) ; 
 int /*<<< orphan*/  l2cap_sock_clear_timer (struct sock*) ; 
 int /*<<< orphan*/  l2cap_sock_set_timer (struct sock*,int) ; 
 int /*<<< orphan*/  read_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int l2cap_security_cfm(struct hci_conn *hcon, u8 status, u8 encrypt)
{
	struct l2cap_chan_list *l;
	struct l2cap_conn *conn = hcon->l2cap_data;
	struct sock *sk;

	if (!conn)
		return 0;

	l = &conn->chan_list;

	BT_DBG("conn %p", conn);

	read_lock(&l->lock);

	for (sk = l->head; sk; sk = l2cap_pi(sk)->next_c) {
		bh_lock_sock(sk);

		if (l2cap_pi(sk)->conf_state & L2CAP_CONF_CONNECT_PEND) {
			bh_unlock_sock(sk);
			continue;
		}

		if (!status && (sk->sk_state == BT_CONNECTED ||
						sk->sk_state == BT_CONFIG)) {
			l2cap_check_encryption(sk, encrypt);
			bh_unlock_sock(sk);
			continue;
		}

		if (sk->sk_state == BT_CONNECT) {
			if (!status) {
				struct l2cap_conn_req req;
				req.scid = cpu_to_le16(l2cap_pi(sk)->scid);
				req.psm  = l2cap_pi(sk)->psm;

				l2cap_pi(sk)->ident = l2cap_get_ident(conn);

				l2cap_send_cmd(conn, l2cap_pi(sk)->ident,
					L2CAP_CONN_REQ, sizeof(req), &req);
			} else {
				l2cap_sock_clear_timer(sk);
				l2cap_sock_set_timer(sk, HZ / 10);
			}
		} else if (sk->sk_state == BT_CONNECT2) {
			struct l2cap_conn_rsp rsp;
			__u16 result;

			if (!status) {
				sk->sk_state = BT_CONFIG;
				result = L2CAP_CR_SUCCESS;
			} else {
				sk->sk_state = BT_DISCONN;
				l2cap_sock_set_timer(sk, HZ / 10);
				result = L2CAP_CR_SEC_BLOCK;
			}

			rsp.scid   = cpu_to_le16(l2cap_pi(sk)->dcid);
			rsp.dcid   = cpu_to_le16(l2cap_pi(sk)->scid);
			rsp.result = cpu_to_le16(result);
			rsp.status = cpu_to_le16(L2CAP_CS_NO_INFO);
			l2cap_send_cmd(conn, l2cap_pi(sk)->ident,
					L2CAP_CONN_RSP, sizeof(rsp), &rsp);
		}

		bh_unlock_sock(sk);
	}

	read_unlock(&l->lock);

	return 0;
}