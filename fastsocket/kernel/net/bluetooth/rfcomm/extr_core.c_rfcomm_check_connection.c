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
struct sock {int sk_state; int /*<<< orphan*/  sk_err; } ;
struct rfcomm_session {int state; int /*<<< orphan*/  mtu; TYPE_1__* sock; } ;
struct TYPE_4__ {int /*<<< orphan*/  imtu; int /*<<< orphan*/  omtu; } ;
struct TYPE_3__ {struct sock* sk; } ;

/* Variables and functions */
#define  BT_CLOSED 129 
 int BT_CONNECT ; 
#define  BT_CONNECTED 128 
 int /*<<< orphan*/  BT_DBG (char*,struct rfcomm_session*,int) ; 
 TYPE_2__* l2cap_pi (struct sock*) ; 
 int /*<<< orphan*/  min (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rfcomm_send_sabm (struct rfcomm_session*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rfcomm_session_close (struct rfcomm_session*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void rfcomm_check_connection(struct rfcomm_session *s)
{
	struct sock *sk = s->sock->sk;

	BT_DBG("%p state %ld", s, s->state);

	switch(sk->sk_state) {
	case BT_CONNECTED:
		s->state = BT_CONNECT;

		/* We can adjust MTU on outgoing sessions.
		 * L2CAP MTU minus UIH header and FCS. */
		s->mtu = min(l2cap_pi(sk)->omtu, l2cap_pi(sk)->imtu) - 5;

		rfcomm_send_sabm(s, 0);
		break;

	case BT_CLOSED:
		s->state = BT_CLOSED;
		rfcomm_session_close(s, sk->sk_err);
		break;
	}
}