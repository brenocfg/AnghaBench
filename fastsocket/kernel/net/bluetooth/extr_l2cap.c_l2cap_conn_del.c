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
struct sock {int dummy; } ;
struct TYPE_2__ {struct sock* head; } ;
struct l2cap_conn {int info_state; int /*<<< orphan*/  info_timer; TYPE_1__ chan_list; int /*<<< orphan*/  rx_skb; } ;
struct hci_conn {struct l2cap_conn* l2cap_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  BT_DBG (char*,struct hci_conn*,struct l2cap_conn*,int) ; 
 int L2CAP_INFO_FEAT_MASK_REQ_SENT ; 
 int /*<<< orphan*/  bh_lock_sock (struct sock*) ; 
 int /*<<< orphan*/  bh_unlock_sock (struct sock*) ; 
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct l2cap_conn*) ; 
 int /*<<< orphan*/  kfree_skb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  l2cap_chan_del (struct sock*,int) ; 
 int /*<<< orphan*/  l2cap_sock_kill (struct sock*) ; 

__attribute__((used)) static void l2cap_conn_del(struct hci_conn *hcon, int err)
{
	struct l2cap_conn *conn = hcon->l2cap_data;
	struct sock *sk;

	if (!conn)
		return;

	BT_DBG("hcon %p conn %p, err %d", hcon, conn, err);

	kfree_skb(conn->rx_skb);

	/* Kill channels */
	while ((sk = conn->chan_list.head)) {
		bh_lock_sock(sk);
		l2cap_chan_del(sk, err);
		bh_unlock_sock(sk);
		l2cap_sock_kill(sk);
	}

	if (conn->info_state & L2CAP_INFO_FEAT_MASK_REQ_SENT)
		del_timer_sync(&conn->info_timer);

	hcon->l2cap_data = NULL;
	kfree(conn);
}