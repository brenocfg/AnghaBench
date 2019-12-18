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
typedef  int /*<<< orphan*/  u8 ;
typedef  int u16 ;
struct sock {void* sk_state; int /*<<< orphan*/  (* sk_data_ready ) (struct sock*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  sk_sndtimeo; int /*<<< orphan*/  sk_ack_backlog; } ;
struct l2cap_info_req {void* type; void* status; void* result; void* dcid; void* scid; } ;
struct l2cap_conn_rsp {void* type; void* status; void* result; void* dcid; void* scid; } ;
struct l2cap_conn_req {void* psm; int /*<<< orphan*/  scid; } ;
struct l2cap_chan_list {int /*<<< orphan*/  lock; } ;
struct l2cap_conn {int disc_reason; int info_state; int /*<<< orphan*/  info_ident; int /*<<< orphan*/  info_timer; int /*<<< orphan*/  dst; int /*<<< orphan*/  src; int /*<<< orphan*/  hcon; struct l2cap_chan_list chan_list; } ;
struct l2cap_cmd_hdr {int /*<<< orphan*/  ident; } ;
typedef  int /*<<< orphan*/  rsp ;
typedef  int /*<<< orphan*/  info ;
typedef  void* __le16 ;
struct TYPE_4__ {scalar_t__ defer_setup; int /*<<< orphan*/  dst; int /*<<< orphan*/  src; } ;
struct TYPE_3__ {int dcid; int scid; int /*<<< orphan*/  ident; void* psm; } ;

/* Variables and functions */
 int /*<<< orphan*/  BTPROTO_L2CAP ; 
 void* BT_CONFIG ; 
 void* BT_CONNECT2 ; 
 int /*<<< orphan*/  BT_DBG (char*,void*,...) ; 
 int /*<<< orphan*/  BT_LISTEN ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  L2CAP_CONN_RSP ; 
 int L2CAP_CR_BAD_PSM ; 
 int L2CAP_CR_NO_MEM ; 
 int L2CAP_CR_PEND ; 
 int L2CAP_CR_SEC_BLOCK ; 
 int L2CAP_CR_SUCCESS ; 
 int L2CAP_CS_AUTHEN_PEND ; 
 int L2CAP_CS_AUTHOR_PEND ; 
 int L2CAP_CS_NO_INFO ; 
 int L2CAP_INFO_FEAT_MASK_REQ_DONE ; 
 int L2CAP_INFO_FEAT_MASK_REQ_SENT ; 
 int /*<<< orphan*/  L2CAP_INFO_REQ ; 
 int /*<<< orphan*/  L2CAP_INFO_TIMEOUT ; 
 int L2CAP_IT_FEAT_MASK ; 
 int /*<<< orphan*/  SOCK_ZAPPED ; 
 int /*<<< orphan*/  __l2cap_chan_add (struct l2cap_conn*,struct sock*,struct sock*) ; 
 scalar_t__ __l2cap_get_chan_by_dcid (struct l2cap_chan_list*,int) ; 
 int __le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bacpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bh_unlock_sock (struct sock*) ; 
 TYPE_2__* bt_sk (struct sock*) ; 
 void* cpu_to_le16 (int) ; 
 int /*<<< orphan*/  hci_conn_check_link_mode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hci_conn_hold (int /*<<< orphan*/ ) ; 
 scalar_t__ jiffies ; 
 scalar_t__ l2cap_check_security (struct sock*) ; 
 int /*<<< orphan*/  l2cap_get_ident (struct l2cap_conn*) ; 
 struct sock* l2cap_get_sock_by_psm (int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ) ; 
 TYPE_1__* l2cap_pi (struct sock*) ; 
 int /*<<< orphan*/  l2cap_send_cmd (struct l2cap_conn*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,struct l2cap_info_req*) ; 
 struct sock* l2cap_sock_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  l2cap_sock_init (struct sock*,struct sock*) ; 
 int /*<<< orphan*/  l2cap_sock_kill (struct sock*) ; 
 int /*<<< orphan*/  l2cap_sock_set_timer (struct sock*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 scalar_t__ sk_acceptq_is_full (struct sock*) ; 
 int /*<<< orphan*/  sock_net (struct sock*) ; 
 int /*<<< orphan*/  sock_set_flag (struct sock*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct sock*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline int l2cap_connect_req(struct l2cap_conn *conn, struct l2cap_cmd_hdr *cmd, u8 *data)
{
	struct l2cap_chan_list *list = &conn->chan_list;
	struct l2cap_conn_req *req = (struct l2cap_conn_req *) data;
	struct l2cap_conn_rsp rsp;
	struct sock *sk, *parent;
	int result, status = L2CAP_CS_NO_INFO;

	u16 dcid = 0, scid = __le16_to_cpu(req->scid);
	__le16 psm = req->psm;

	BT_DBG("psm 0x%2.2x scid 0x%4.4x", psm, scid);

	/* Check if we have socket listening on psm */
	parent = l2cap_get_sock_by_psm(BT_LISTEN, psm, conn->src);
	if (!parent) {
		result = L2CAP_CR_BAD_PSM;
		goto sendresp;
	}

	/* Check if the ACL is secure enough (if not SDP) */
	if (psm != cpu_to_le16(0x0001) &&
				!hci_conn_check_link_mode(conn->hcon)) {
		conn->disc_reason = 0x05;
		result = L2CAP_CR_SEC_BLOCK;
		goto response;
	}

	result = L2CAP_CR_NO_MEM;

	/* Check for backlog size */
	if (sk_acceptq_is_full(parent)) {
		BT_DBG("backlog full %d", parent->sk_ack_backlog);
		goto response;
	}

	sk = l2cap_sock_alloc(sock_net(parent), NULL, BTPROTO_L2CAP, GFP_ATOMIC);
	if (!sk)
		goto response;

	write_lock_bh(&list->lock);

	/* Check if we already have channel with that dcid */
	if (__l2cap_get_chan_by_dcid(list, scid)) {
		write_unlock_bh(&list->lock);
		sock_set_flag(sk, SOCK_ZAPPED);
		l2cap_sock_kill(sk);
		goto response;
	}

	hci_conn_hold(conn->hcon);

	l2cap_sock_init(sk, parent);
	bacpy(&bt_sk(sk)->src, conn->src);
	bacpy(&bt_sk(sk)->dst, conn->dst);
	l2cap_pi(sk)->psm  = psm;
	l2cap_pi(sk)->dcid = scid;

	__l2cap_chan_add(conn, sk, parent);
	dcid = l2cap_pi(sk)->scid;

	l2cap_sock_set_timer(sk, sk->sk_sndtimeo);

	l2cap_pi(sk)->ident = cmd->ident;

	if (conn->info_state & L2CAP_INFO_FEAT_MASK_REQ_DONE) {
		if (l2cap_check_security(sk)) {
			if (bt_sk(sk)->defer_setup) {
				sk->sk_state = BT_CONNECT2;
				result = L2CAP_CR_PEND;
				status = L2CAP_CS_AUTHOR_PEND;
				parent->sk_data_ready(parent, 0);
			} else {
				sk->sk_state = BT_CONFIG;
				result = L2CAP_CR_SUCCESS;
				status = L2CAP_CS_NO_INFO;
			}
		} else {
			sk->sk_state = BT_CONNECT2;
			result = L2CAP_CR_PEND;
			status = L2CAP_CS_AUTHEN_PEND;
		}
	} else {
		sk->sk_state = BT_CONNECT2;
		result = L2CAP_CR_PEND;
		status = L2CAP_CS_NO_INFO;
	}

	write_unlock_bh(&list->lock);

response:
	bh_unlock_sock(parent);

sendresp:
	rsp.scid   = cpu_to_le16(scid);
	rsp.dcid   = cpu_to_le16(dcid);
	rsp.result = cpu_to_le16(result);
	rsp.status = cpu_to_le16(status);
	l2cap_send_cmd(conn, cmd->ident, L2CAP_CONN_RSP, sizeof(rsp), &rsp);

	if (result == L2CAP_CR_PEND && status == L2CAP_CS_NO_INFO) {
		struct l2cap_info_req info;
		info.type = cpu_to_le16(L2CAP_IT_FEAT_MASK);

		conn->info_state |= L2CAP_INFO_FEAT_MASK_REQ_SENT;
		conn->info_ident = l2cap_get_ident(conn);

		mod_timer(&conn->info_timer, jiffies +
					msecs_to_jiffies(L2CAP_INFO_TIMEOUT));

		l2cap_send_cmd(conn, conn->info_ident,
					L2CAP_INFO_REQ, sizeof(info), &info);
	}

	return 0;
}