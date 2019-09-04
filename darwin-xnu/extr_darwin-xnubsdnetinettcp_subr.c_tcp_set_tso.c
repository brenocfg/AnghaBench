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
struct tcpcb {scalar_t__ tso_max_segment_size; int /*<<< orphan*/  t_flags; } ;
struct ifnet {int if_hwassist; scalar_t__ if_tso_v4_mtu; } ;

/* Variables and functions */
 int IFNET_TSO_IPV4 ; 
 scalar_t__ TCP_MAXWIN ; 
 int /*<<< orphan*/  TF_TSO ; 

void
tcp_set_tso(struct tcpcb *tp, struct ifnet *ifp)
{
#if INET6
	struct inpcb *inp;
	int isipv6;
#endif /* INET6 */
#if MPTCP
	/*
	 * We can't use TSO if this tcpcb belongs to an MPTCP session.
	 */
	if (tp->t_mpflags & TMPF_MPTCP_TRUE) {
		tp->t_flags &= ~TF_TSO;
		return;
	}
#endif
#if INET6
	inp = tp->t_inpcb;
	isipv6 = (inp->inp_vflag & INP_IPV6) != 0;

	if (isipv6) {
		if (ifp && (ifp->if_hwassist & IFNET_TSO_IPV6)) {
			tp->t_flags |= TF_TSO;
			if (ifp->if_tso_v6_mtu != 0)
				tp->tso_max_segment_size = ifp->if_tso_v6_mtu;
			else
				tp->tso_max_segment_size = TCP_MAXWIN;
		} else
				tp->t_flags &= ~TF_TSO;

	} else
#endif /* INET6 */

	{
		if (ifp && (ifp->if_hwassist & IFNET_TSO_IPV4)) {
			tp->t_flags |= TF_TSO;
			if (ifp->if_tso_v4_mtu != 0)
				tp->tso_max_segment_size = ifp->if_tso_v4_mtu;
			else
				tp->tso_max_segment_size = TCP_MAXWIN;
		} else
				tp->t_flags &= ~TF_TSO;
	}
}