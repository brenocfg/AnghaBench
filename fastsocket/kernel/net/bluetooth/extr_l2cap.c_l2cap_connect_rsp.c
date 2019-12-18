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
typedef  int u16 ;
struct sock {int /*<<< orphan*/  sk_state; } ;
struct l2cap_conn_rsp {int /*<<< orphan*/  status; int /*<<< orphan*/  result; int /*<<< orphan*/  dcid; int /*<<< orphan*/  scid; } ;
struct l2cap_conn {int /*<<< orphan*/  chan_list; } ;
struct l2cap_cmd_hdr {int /*<<< orphan*/  ident; } ;
struct TYPE_2__ {int dcid; int /*<<< orphan*/  conf_state; int /*<<< orphan*/  num_conf_req; int /*<<< orphan*/  ident; } ;

/* Variables and functions */
 int /*<<< orphan*/  BT_CONFIG ; 
 int /*<<< orphan*/  BT_DBG (char*,int,int,int,int) ; 
 int /*<<< orphan*/  ECONNREFUSED ; 
 int /*<<< orphan*/  L2CAP_CONF_CONNECT_PEND ; 
 int /*<<< orphan*/  L2CAP_CONF_REQ ; 
 int /*<<< orphan*/  L2CAP_CONF_REQ_SENT ; 
#define  L2CAP_CR_PEND 129 
#define  L2CAP_CR_SUCCESS 128 
 int __le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bh_unlock_sock (struct sock*) ; 
 int /*<<< orphan*/  l2cap_build_conf_req (struct sock*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  l2cap_chan_del (struct sock*,int /*<<< orphan*/ ) ; 
 struct sock* l2cap_get_chan_by_ident (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct sock* l2cap_get_chan_by_scid (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  l2cap_get_ident (struct l2cap_conn*) ; 
 TYPE_1__* l2cap_pi (struct sock*) ; 
 int /*<<< orphan*/  l2cap_send_cmd (struct l2cap_conn*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline int l2cap_connect_rsp(struct l2cap_conn *conn, struct l2cap_cmd_hdr *cmd, u8 *data)
{
	struct l2cap_conn_rsp *rsp = (struct l2cap_conn_rsp *) data;
	u16 scid, dcid, result, status;
	struct sock *sk;
	u8 req[128];

	scid   = __le16_to_cpu(rsp->scid);
	dcid   = __le16_to_cpu(rsp->dcid);
	result = __le16_to_cpu(rsp->result);
	status = __le16_to_cpu(rsp->status);

	BT_DBG("dcid 0x%4.4x scid 0x%4.4x result 0x%2.2x status 0x%2.2x", dcid, scid, result, status);

	if (scid) {
		sk = l2cap_get_chan_by_scid(&conn->chan_list, scid);
		if (!sk)
			return 0;
	} else {
		sk = l2cap_get_chan_by_ident(&conn->chan_list, cmd->ident);
		if (!sk)
			return 0;
	}

	switch (result) {
	case L2CAP_CR_SUCCESS:
		sk->sk_state = BT_CONFIG;
		l2cap_pi(sk)->ident = 0;
		l2cap_pi(sk)->dcid = dcid;
		l2cap_pi(sk)->conf_state |= L2CAP_CONF_REQ_SENT;

		l2cap_pi(sk)->conf_state &= ~L2CAP_CONF_CONNECT_PEND;

		l2cap_send_cmd(conn, l2cap_get_ident(conn), L2CAP_CONF_REQ,
					l2cap_build_conf_req(sk, req), req);
		l2cap_pi(sk)->num_conf_req++;
		break;

	case L2CAP_CR_PEND:
		l2cap_pi(sk)->conf_state |= L2CAP_CONF_CONNECT_PEND;
		break;

	default:
		l2cap_chan_del(sk, ECONNREFUSED);
		break;
	}

	bh_unlock_sock(sk);
	return 0;
}