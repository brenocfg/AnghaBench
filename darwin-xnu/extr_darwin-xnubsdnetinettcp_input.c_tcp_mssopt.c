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
struct tcpiphdr {int dummy; } ;
struct tcpcb {int /*<<< orphan*/  t_flags; int /*<<< orphan*/  t_inpcb; } ;
struct rtentry {TYPE_1__* rt_ifp; } ;
struct TYPE_2__ {scalar_t__ if_type; int if_baudrate; } ;

/* Variables and functions */
 int /*<<< orphan*/  IFSCOPE_NONE ; 
 scalar_t__ IFT_PPP ; 
 int /*<<< orphan*/  RT_UNLOCK (struct rtentry*) ; 
 int /*<<< orphan*/  TF_SLOWLINK ; 
 scalar_t__ slowlink_wsize ; 
 int tcp_maxmtu (struct rtentry*) ; 
 int tcp_mssdflt ; 
 struct rtentry* tcp_rtlookup (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
tcp_mssopt(struct tcpcb *tp)
{
	struct rtentry *rt;
	int mss;
#if INET6
	int isipv6;
	int min_protoh;
#endif

#if INET6
	isipv6 = ((tp->t_inpcb->inp_vflag & INP_IPV6) != 0) ? 1 : 0;
	min_protoh = isipv6 ? sizeof (struct ip6_hdr) + sizeof (struct tcphdr)
			    : sizeof (struct tcpiphdr);
#else
#define min_protoh  (sizeof (struct tcpiphdr))
#endif

#if INET6
	if (isipv6)
		rt = tcp_rtlookup6(tp->t_inpcb, IFSCOPE_NONE);
	else
#endif /* INET6 */
	rt = tcp_rtlookup(tp->t_inpcb, IFSCOPE_NONE);
	if (rt == NULL) {
		return (
#if INET6
			isipv6 ? tcp_v6mssdflt :
#endif /* INET6 */
			tcp_mssdflt);
	}
	/*
	 * Slower link window correction:
	 * If a value is specificied for slowlink_wsize use it for PPP links
	 * believed to be on a serial modem (speed <128Kbps). Excludes 9600bps as
	 * it is the default value adversized by pseudo-devices over ppp.
	 */
	if (rt->rt_ifp->if_type == IFT_PPP && slowlink_wsize > 0 &&
	    rt->rt_ifp->if_baudrate > 9600 && rt->rt_ifp->if_baudrate <= 128000) {
		tp->t_flags |= TF_SLOWLINK;
	}

#if INET6
	mss = (isipv6 ? tcp_maxmtu6(rt) : tcp_maxmtu(rt));
#else
	mss = tcp_maxmtu(rt);
#endif
	/* Route locked during lookup above */
	RT_UNLOCK(rt);

#if NECP
	// At this point, the mss is just the MTU. Adjust if necessary.
	mss = necp_socket_get_effective_mtu(tp->t_inpcb, mss);
#endif /* NECP */

	return (mss - min_protoh);
}