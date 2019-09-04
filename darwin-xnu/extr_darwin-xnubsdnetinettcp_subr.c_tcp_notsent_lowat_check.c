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
struct tcpcb {int snd_nxt; int snd_una; int t_notsent_lowat; int t_flags; int t_maxseg; } ;
struct TYPE_2__ {int sb_cc; } ;
struct socket {TYPE_1__ so_snd; } ;
struct inpcb {int dummy; } ;

/* Variables and functions */
 int TF_NODELAY ; 
 struct tcpcb* intotcpcb (struct inpcb*) ; 
 struct inpcb* sotoinpcb (struct socket*) ; 

int
tcp_notsent_lowat_check(struct socket *so)
{
	struct inpcb *inp = sotoinpcb(so);
	struct tcpcb *tp = NULL;
	int notsent = 0;

	if (inp != NULL) {
		tp = intotcpcb(inp);
	}

	if (tp == NULL) {
		return (0);
	}

	notsent = so->so_snd.sb_cc -
		(tp->snd_nxt - tp->snd_una);

	/*
	 * When we send a FIN or SYN, not_sent can be negative.
	 * In that case also we need to send a write event to the
	 * process if it is waiting. In the FIN case, it will
	 * get an error from send because cantsendmore will be set.
	 */
	if (notsent <= tp->t_notsent_lowat) {
		return (1);
	}

	/*
	 * When Nagle's algorithm is not disabled, it is better
	 * to wakeup the client until there is atleast one
	 * maxseg of data to write.
	 */
	if ((tp->t_flags & TF_NODELAY) == 0 &&
		notsent > 0 && notsent < tp->t_maxseg) {
		return (1);
	}
	return (0);
}