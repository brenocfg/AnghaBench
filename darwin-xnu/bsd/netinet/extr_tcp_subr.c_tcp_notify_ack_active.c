#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct tcpcb {int /*<<< orphan*/  snd_una; int /*<<< orphan*/  t_notify_ack; } ;
struct tcp_notify_ack_marker {int /*<<< orphan*/  notify_snd_una; } ;
struct socket {int dummy; } ;

/* Variables and functions */
 scalar_t__ PF_INET ; 
 scalar_t__ PF_INET6 ; 
 scalar_t__ SEQ_GEQ (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SLIST_EMPTY (int /*<<< orphan*/ *) ; 
 struct tcp_notify_ack_marker* SLIST_FIRST (int /*<<< orphan*/ *) ; 
 scalar_t__ SOCK_DOM (struct socket*) ; 
 scalar_t__ SOCK_STREAM ; 
 scalar_t__ SOCK_TYPE (struct socket*) ; 
 struct tcpcb* intotcpcb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sotoinpcb (struct socket*) ; 

bool
tcp_notify_ack_active(struct socket *so)
{
	if ((SOCK_DOM(so) == PF_INET || SOCK_DOM(so) == PF_INET6) &&
	    SOCK_TYPE(so) == SOCK_STREAM) {
		struct tcpcb *tp = intotcpcb(sotoinpcb(so));

		if (!SLIST_EMPTY(&tp->t_notify_ack)) {
			struct tcp_notify_ack_marker *elm;
			elm = SLIST_FIRST(&tp->t_notify_ack);
			if (SEQ_GEQ(tp->snd_una, elm->notify_snd_una))
				return (true);
		}
	}
	return (false);
}