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
typedef  int /*<<< orphan*/  u16 ;
struct sock {int /*<<< orphan*/  sk_shutdown; } ;
struct l2cap_disconn_rsp {void* scid; void* dcid; } ;
struct l2cap_disconn_req {int /*<<< orphan*/  dcid; int /*<<< orphan*/  scid; } ;
struct l2cap_conn {int /*<<< orphan*/  chan_list; } ;
struct l2cap_cmd_hdr {int /*<<< orphan*/  ident; } ;
typedef  int /*<<< orphan*/  rsp ;
struct TYPE_2__ {int /*<<< orphan*/  monitor_timer; int /*<<< orphan*/  retrans_timer; int /*<<< orphan*/  dcid; int /*<<< orphan*/  scid; } ;

/* Variables and functions */
 int /*<<< orphan*/  BT_DBG (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ECONNRESET ; 
 int /*<<< orphan*/  L2CAP_DISCONN_RSP ; 
 int /*<<< orphan*/  SHUTDOWN_MASK ; 
 int /*<<< orphan*/  SREJ_QUEUE (struct sock*) ; 
 int /*<<< orphan*/  TX_QUEUE (struct sock*) ; 
 int /*<<< orphan*/  __le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bh_unlock_sock (struct sock*) ; 
 void* cpu_to_le16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  del_timer (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  l2cap_chan_del (struct sock*,int /*<<< orphan*/ ) ; 
 struct sock* l2cap_get_chan_by_scid (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_1__* l2cap_pi (struct sock*) ; 
 int /*<<< orphan*/  l2cap_send_cmd (struct l2cap_conn*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,struct l2cap_disconn_rsp*) ; 
 int /*<<< orphan*/  l2cap_sock_kill (struct sock*) ; 
 int /*<<< orphan*/  skb_queue_purge (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int l2cap_disconnect_req(struct l2cap_conn *conn, struct l2cap_cmd_hdr *cmd, u8 *data)
{
	struct l2cap_disconn_req *req = (struct l2cap_disconn_req *) data;
	struct l2cap_disconn_rsp rsp;
	u16 dcid, scid;
	struct sock *sk;

	scid = __le16_to_cpu(req->scid);
	dcid = __le16_to_cpu(req->dcid);

	BT_DBG("scid 0x%4.4x dcid 0x%4.4x", scid, dcid);

	sk = l2cap_get_chan_by_scid(&conn->chan_list, dcid);
	if (!sk)
		return 0;

	rsp.dcid = cpu_to_le16(l2cap_pi(sk)->scid);
	rsp.scid = cpu_to_le16(l2cap_pi(sk)->dcid);
	l2cap_send_cmd(conn, cmd->ident, L2CAP_DISCONN_RSP, sizeof(rsp), &rsp);

	sk->sk_shutdown = SHUTDOWN_MASK;

	skb_queue_purge(TX_QUEUE(sk));
	skb_queue_purge(SREJ_QUEUE(sk));
	del_timer(&l2cap_pi(sk)->retrans_timer);
	del_timer(&l2cap_pi(sk)->monitor_timer);

	l2cap_chan_del(sk, ECONNRESET);
	bh_unlock_sock(sk);

	l2cap_sock_kill(sk);
	return 0;
}