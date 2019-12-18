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
struct sock {int dummy; } ;
struct l2cap_disconn_rsp {int /*<<< orphan*/  dcid; int /*<<< orphan*/  scid; } ;
struct l2cap_conn {int /*<<< orphan*/  chan_list; } ;
struct l2cap_cmd_hdr {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  monitor_timer; int /*<<< orphan*/  retrans_timer; } ;

/* Variables and functions */
 int /*<<< orphan*/  BT_DBG (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SREJ_QUEUE (struct sock*) ; 
 int /*<<< orphan*/  TX_QUEUE (struct sock*) ; 
 int /*<<< orphan*/  __le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bh_unlock_sock (struct sock*) ; 
 int /*<<< orphan*/  del_timer (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  l2cap_chan_del (struct sock*,int /*<<< orphan*/ ) ; 
 struct sock* l2cap_get_chan_by_scid (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_1__* l2cap_pi (struct sock*) ; 
 int /*<<< orphan*/  l2cap_sock_kill (struct sock*) ; 
 int /*<<< orphan*/  skb_queue_purge (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int l2cap_disconnect_rsp(struct l2cap_conn *conn, struct l2cap_cmd_hdr *cmd, u8 *data)
{
	struct l2cap_disconn_rsp *rsp = (struct l2cap_disconn_rsp *) data;
	u16 dcid, scid;
	struct sock *sk;

	scid = __le16_to_cpu(rsp->scid);
	dcid = __le16_to_cpu(rsp->dcid);

	BT_DBG("dcid 0x%4.4x scid 0x%4.4x", dcid, scid);

	sk = l2cap_get_chan_by_scid(&conn->chan_list, scid);
	if (!sk)
		return 0;

	skb_queue_purge(TX_QUEUE(sk));
	skb_queue_purge(SREJ_QUEUE(sk));
	del_timer(&l2cap_pi(sk)->retrans_timer);
	del_timer(&l2cap_pi(sk)->monitor_timer);

	l2cap_chan_del(sk, 0);
	bh_unlock_sock(sk);

	l2cap_sock_kill(sk);
	return 0;
}