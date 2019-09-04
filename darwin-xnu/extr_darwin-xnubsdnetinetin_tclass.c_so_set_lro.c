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
struct tcpcb {int t_flagsext; } ;
struct socket {int so_flags; } ;
struct inpcb {int /*<<< orphan*/  inp_fport; int /*<<< orphan*/  inp_lport; int /*<<< orphan*/  inp_faddr; int /*<<< orphan*/  inp_laddr; } ;

/* Variables and functions */
 int SOF_USELRO ; 
 int SO_TC_AV ; 
 int TF_LRO_OFFLOADED ; 
 struct tcpcb* intotcpcb (struct inpcb*) ; 
 struct inpcb* sotoinpcb (struct socket*) ; 
 int /*<<< orphan*/  tcp_lro_remove_state (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
so_set_lro(struct socket *so, int optval)
{
	if (optval == SO_TC_AV) {
		so->so_flags |= SOF_USELRO;
	} else {
		if (so->so_flags & SOF_USELRO) {
			/* transition to non LRO class */
			so->so_flags &= ~SOF_USELRO;
			struct inpcb *inp = sotoinpcb(so);
			struct tcpcb *tp = NULL;
			if (inp) {
				tp = intotcpcb(inp);
				if (tp && (tp->t_flagsext & TF_LRO_OFFLOADED)) {
					tcp_lro_remove_state(inp->inp_laddr,
						inp->inp_faddr,
						inp->inp_lport,
						inp->inp_fport);
					tp->t_flagsext &= ~TF_LRO_OFFLOADED;
				}
			}
		}
	}
}