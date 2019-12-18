#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct socket {TYPE_2__* sk; } ;
struct rfcomm_session {scalar_t__ mtu; struct socket* sock; } ;
struct TYPE_7__ {int /*<<< orphan*/  accept_q; } ;
struct TYPE_6__ {int /*<<< orphan*/  sk_state_change; int /*<<< orphan*/  sk_data_ready; } ;
struct TYPE_5__ {int /*<<< orphan*/  imtu; int /*<<< orphan*/  omtu; } ;

/* Variables and functions */
 int /*<<< orphan*/  BT_DBG (char*,struct rfcomm_session*) ; 
 int /*<<< orphan*/  BT_OPEN ; 
 int /*<<< orphan*/  O_NONBLOCK ; 
 int /*<<< orphan*/  RFCOMM_SCHED_RX ; 
 TYPE_3__* bt_sk (TYPE_2__*) ; 
 int kernel_accept (struct socket*,struct socket**,int /*<<< orphan*/ ) ; 
 TYPE_1__* l2cap_pi (TYPE_2__*) ; 
 scalar_t__ list_empty (int /*<<< orphan*/ *) ; 
 scalar_t__ min (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rfcomm_l2data_ready ; 
 int /*<<< orphan*/  rfcomm_l2state_change ; 
 int /*<<< orphan*/  rfcomm_schedule (int /*<<< orphan*/ ) ; 
 struct rfcomm_session* rfcomm_session_add (struct socket*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rfcomm_session_hold (struct rfcomm_session*) ; 
 int /*<<< orphan*/  sock_release (struct socket*) ; 

__attribute__((used)) static inline void rfcomm_accept_connection(struct rfcomm_session *s)
{
	struct socket *sock = s->sock, *nsock;
	int err;

	/* Fast check for a new connection.
	 * Avoids unnesesary socket allocations. */
	if (list_empty(&bt_sk(sock->sk)->accept_q))
		return;

	BT_DBG("session %p", s);

	err = kernel_accept(sock, &nsock, O_NONBLOCK);
	if (err < 0)
		return;

	/* Set our callbacks */
	nsock->sk->sk_data_ready   = rfcomm_l2data_ready;
	nsock->sk->sk_state_change = rfcomm_l2state_change;

	s = rfcomm_session_add(nsock, BT_OPEN);
	if (s) {
		rfcomm_session_hold(s);

		/* We should adjust MTU on incoming sessions.
		 * L2CAP MTU minus UIH header and FCS. */
		s->mtu = min(l2cap_pi(nsock->sk)->omtu, l2cap_pi(nsock->sk)->imtu) - 5;

		rfcomm_schedule(RFCOMM_SCHED_RX);
	} else
		sock_release(nsock);
}