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
struct sock {scalar_t__ sk_type; } ;
struct l2cap_chan_list {int dummy; } ;
struct l2cap_conn {int disc_reason; struct l2cap_chan_list chan_list; } ;
struct TYPE_2__ {void* omtu; void* dcid; void* scid; struct l2cap_conn* conn; int /*<<< orphan*/  psm; } ;

/* Variables and functions */
 int /*<<< orphan*/  BT_DBG (char*,struct l2cap_conn*,int /*<<< orphan*/ ,void*) ; 
 void* L2CAP_CID_CONN_LESS ; 
 void* L2CAP_CID_SIGNALING ; 
 void* L2CAP_DEFAULT_MTU ; 
 scalar_t__ SOCK_DGRAM ; 
 scalar_t__ SOCK_SEQPACKET ; 
 int /*<<< orphan*/  __l2cap_chan_link (struct l2cap_chan_list*,struct sock*) ; 
 int /*<<< orphan*/  bt_accept_enqueue (struct sock*,struct sock*) ; 
 void* l2cap_alloc_cid (struct l2cap_chan_list*) ; 
 TYPE_1__* l2cap_pi (struct sock*) ; 

__attribute__((used)) static void __l2cap_chan_add(struct l2cap_conn *conn, struct sock *sk, struct sock *parent)
{
	struct l2cap_chan_list *l = &conn->chan_list;

	BT_DBG("conn %p, psm 0x%2.2x, dcid 0x%4.4x", conn,
			l2cap_pi(sk)->psm, l2cap_pi(sk)->dcid);

	conn->disc_reason = 0x13;

	l2cap_pi(sk)->conn = conn;

	if (sk->sk_type == SOCK_SEQPACKET) {
		/* Alloc CID for connection-oriented socket */
		l2cap_pi(sk)->scid = l2cap_alloc_cid(l);
	} else if (sk->sk_type == SOCK_DGRAM) {
		/* Connectionless socket */
		l2cap_pi(sk)->scid = L2CAP_CID_CONN_LESS;
		l2cap_pi(sk)->dcid = L2CAP_CID_CONN_LESS;
		l2cap_pi(sk)->omtu = L2CAP_DEFAULT_MTU;
	} else {
		/* Raw socket can send/recv signalling messages only */
		l2cap_pi(sk)->scid = L2CAP_CID_SIGNALING;
		l2cap_pi(sk)->dcid = L2CAP_CID_SIGNALING;
		l2cap_pi(sk)->omtu = L2CAP_DEFAULT_MTU;
	}

	__l2cap_chan_link(l, sk);

	if (parent)
		bt_accept_enqueue(parent, sk);
}