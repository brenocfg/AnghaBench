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
struct tcpcb {int ecn_flags; int iss; TYPE_2__* t_inpcb; } ;
struct ifnet {int if_eflags; } ;
typedef  int /*<<< orphan*/  boolean_t ;
struct TYPE_4__ {TYPE_1__* inp_socket; } ;
struct TYPE_3__ {int /*<<< orphan*/ * so_head; } ;

/* Variables and functions */
 int IFEF_ECN_DISABLE ; 
 int IFEF_ECN_ENABLE ; 
 int TE_ECN_MODE_DISABLE ; 
 int TE_ECN_MODE_ENABLE ; 
 int TE_ENABLE_ECN ; 
 int tcp_ecn_inbound ; 
 int tcp_ecn_outbound ; 
 int tcp_ecn_setup_percentage ; 
 int /*<<< orphan*/  tcp_heuristic_do_ecn (struct tcpcb*) ; 

void
tcp_set_ecn(struct tcpcb *tp, struct ifnet *ifp)
{
	boolean_t inbound;

	/*
	 * Socket option has precedence
	 */
	if (tp->ecn_flags & TE_ECN_MODE_ENABLE) {
		tp->ecn_flags |= TE_ENABLE_ECN;
		goto check_heuristic;
	}

	if (tp->ecn_flags & TE_ECN_MODE_DISABLE) {
		tp->ecn_flags &= ~TE_ENABLE_ECN;
		return;
	}
	/*
	 * Per interface setting comes next
	 */
	if (ifp != NULL) {
		if (ifp->if_eflags & IFEF_ECN_ENABLE) {
			tp->ecn_flags |= TE_ENABLE_ECN;
			goto check_heuristic;
		}

		if (ifp->if_eflags & IFEF_ECN_DISABLE) {
			tp->ecn_flags &= ~TE_ENABLE_ECN;
			return;
		}
	}
	/*
	 * System wide settings come last
	 */
	inbound = (tp->t_inpcb->inp_socket->so_head != NULL);
	if ((inbound && tcp_ecn_inbound == 1) ||
	    (!inbound && tcp_ecn_outbound == 1)) {
		tp->ecn_flags |= TE_ENABLE_ECN;
		goto check_heuristic;
	} else {
		tp->ecn_flags &= ~TE_ENABLE_ECN;
	}

	return;

check_heuristic:
	if (!tcp_heuristic_do_ecn(tp))
		tp->ecn_flags &= ~TE_ENABLE_ECN;

	/*
	 * If the interface setting, system-level setting and heuristics
	 * allow to enable ECN, randomly select 5% of connections to
	 * enable it
	 */
	if ((tp->ecn_flags & (TE_ECN_MODE_ENABLE | TE_ECN_MODE_DISABLE
	    | TE_ENABLE_ECN)) == TE_ENABLE_ECN) {
		/*
		 * Use the random value in iss for randomizing
		 * this selection
		 */
		if ((tp->iss % 100) >= tcp_ecn_setup_percentage)
			tp->ecn_flags &= ~TE_ENABLE_ECN;
	}
}