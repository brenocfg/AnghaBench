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
struct sock {int /*<<< orphan*/  (* sk_state_change ) (struct sock*) ;int /*<<< orphan*/  sk_state; int /*<<< orphan*/  sk_ack_backlog; } ;
struct rfcomm_session {int dummy; } ;
struct rfcomm_dlc {int dummy; } ;
typedef  int /*<<< orphan*/  bdaddr_t ;
struct TYPE_4__ {scalar_t__ defer_setup; int /*<<< orphan*/  dst; int /*<<< orphan*/  src; } ;
struct TYPE_3__ {struct rfcomm_dlc* dlc; int /*<<< orphan*/  channel; } ;

/* Variables and functions */
 int /*<<< orphan*/  BTPROTO_RFCOMM ; 
 int /*<<< orphan*/  BT_CONFIG ; 
 int /*<<< orphan*/  BT_DBG (char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  BT_LISTEN ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  bacpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bh_unlock_sock (struct sock*) ; 
 int /*<<< orphan*/  bt_accept_enqueue (struct sock*,struct sock*) ; 
 TYPE_2__* bt_sk (struct sock*) ; 
 struct sock* rfcomm_get_sock_by_channel (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_1__* rfcomm_pi (struct sock*) ; 
 int /*<<< orphan*/  rfcomm_session_getaddr (struct rfcomm_session*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct sock* rfcomm_sock_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rfcomm_sock_init (struct sock*,struct sock*) ; 
 scalar_t__ sk_acceptq_is_full (struct sock*) ; 
 int /*<<< orphan*/  sock_net (struct sock*) ; 
 int /*<<< orphan*/  stub1 (struct sock*) ; 

int rfcomm_connect_ind(struct rfcomm_session *s, u8 channel, struct rfcomm_dlc **d)
{
	struct sock *sk, *parent;
	bdaddr_t src, dst;
	int result = 0;

	BT_DBG("session %p channel %d", s, channel);

	rfcomm_session_getaddr(s, &src, &dst);

	/* Check if we have socket listening on channel */
	parent = rfcomm_get_sock_by_channel(BT_LISTEN, channel, &src);
	if (!parent)
		return 0;

	/* Check for backlog size */
	if (sk_acceptq_is_full(parent)) {
		BT_DBG("backlog full %d", parent->sk_ack_backlog);
		goto done;
	}

	sk = rfcomm_sock_alloc(sock_net(parent), NULL, BTPROTO_RFCOMM, GFP_ATOMIC);
	if (!sk)
		goto done;

	rfcomm_sock_init(sk, parent);
	bacpy(&bt_sk(sk)->src, &src);
	bacpy(&bt_sk(sk)->dst, &dst);
	rfcomm_pi(sk)->channel = channel;

	sk->sk_state = BT_CONFIG;
	bt_accept_enqueue(parent, sk);

	/* Accept connection and return socket DLC */
	*d = rfcomm_pi(sk)->dlc;
	result = 1;

done:
	bh_unlock_sock(parent);

	if (bt_sk(parent)->defer_setup)
		parent->sk_state_change(parent);

	return result;
}