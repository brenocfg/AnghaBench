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
struct tcpcb {int dummy; } ;
struct socket {int dummy; } ;
struct inpcb {scalar_t__ inp_state; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ INPCB_STATE_DEAD ; 
 int /*<<< orphan*/  PRU_DETACH ; 
 int /*<<< orphan*/  TCPDEBUG0 ; 
 int /*<<< orphan*/  TCPDEBUG1 () ; 
 int /*<<< orphan*/  TCPDEBUG2 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  calculate_tcp_clock () ; 
 struct tcpcb* intotcpcb (struct inpcb*) ; 
 int /*<<< orphan*/  socket_lock_assert_owned (struct socket*) ; 
 struct inpcb* sotoinpcb (struct socket*) ; 
 struct tcpcb* tcp_disconnect (struct tcpcb*) ; 

__attribute__((used)) static int
tcp_usr_detach(struct socket *so)
{
	int error = 0;
	struct inpcb *inp = sotoinpcb(so);
	struct tcpcb *tp;
	TCPDEBUG0;

	if (inp == 0 || (inp->inp_state == INPCB_STATE_DEAD)) {
		return EINVAL;	/* XXX */
	}
	socket_lock_assert_owned(so);
	tp = intotcpcb(inp);
	/* In case we got disconnected from the peer */
        if (tp == NULL)
		goto out;
	TCPDEBUG1();

	calculate_tcp_clock();

	tp = tcp_disconnect(tp);
out:
	TCPDEBUG2(PRU_DETACH);
	return error;
}