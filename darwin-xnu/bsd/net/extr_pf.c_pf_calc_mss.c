#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u_int16_t ;
struct tcphdr {int dummy; } ;
struct sockaddr_in6 {int sin6_family; int sin6_len; int /*<<< orphan*/  sin6_addr; } ;
struct sockaddr_in {int sin_family; int sin_len; int /*<<< orphan*/  sin_addr; } ;
struct rtentry {TYPE_1__* rt_ifp; } ;
struct route_in6 {struct rtentry* ro_rt; int /*<<< orphan*/  ro_dst; } ;
struct route {struct rtentry* ro_rt; int /*<<< orphan*/  ro_dst; } ;
struct pf_addr {int /*<<< orphan*/  v6addr; int /*<<< orphan*/  v4addr; } ;
struct ip6_hdr {int dummy; } ;
struct ip {int dummy; } ;
typedef  int sa_family_t ;
typedef  int /*<<< orphan*/  ro6 ;
typedef  int /*<<< orphan*/  ro ;
struct TYPE_3__ {int if_mtu; } ;

/* Variables and functions */
#define  AF_INET 129 
#define  AF_INET6 128 
 scalar_t__ CLAT46_HDR_EXPANSION_OVERHD ; 
 int IN6_LINKMTU (TYPE_1__*) ; 
 scalar_t__ INTF_ADJUST_MTU_FOR_CLAT46 (TYPE_1__*) ; 
 int /*<<< orphan*/  bzero (struct route_in6*,int) ; 
 int max (int,int) ; 
 int min (int,int) ; 
 int /*<<< orphan*/  panic (char*) ; 
 int /*<<< orphan*/  rtalloc (struct route_in6*) ; 
 int /*<<< orphan*/  rtfree (struct rtentry*) ; 
 int tcp_mssdflt ; 

__attribute__((used)) static u_int16_t
pf_calc_mss(struct pf_addr *addr, sa_family_t af, u_int16_t offer)
{
#if INET
	struct sockaddr_in	*dst;
	struct route		 ro;
#endif /* INET */
#if INET6
	struct sockaddr_in6	*dst6;
	struct route_in6	 ro6;
#endif /* INET6 */
	struct rtentry		*rt = NULL;
	int			 hlen;
	u_int16_t		 mss = tcp_mssdflt;

	switch (af) {
#if INET
	case AF_INET:
		hlen = sizeof (struct ip);
		bzero(&ro, sizeof (ro));
		dst = (struct sockaddr_in *)(void *)&ro.ro_dst;
		dst->sin_family = AF_INET;
		dst->sin_len = sizeof (*dst);
		dst->sin_addr = addr->v4addr;
		rtalloc(&ro);
		rt = ro.ro_rt;
		break;
#endif /* INET */
#if INET6
	case AF_INET6:
		hlen = sizeof (struct ip6_hdr);
		bzero(&ro6, sizeof (ro6));
		dst6 = (struct sockaddr_in6 *)(void *)&ro6.ro_dst;
		dst6->sin6_family = AF_INET6;
		dst6->sin6_len = sizeof (*dst6);
		dst6->sin6_addr = addr->v6addr;
		rtalloc((struct route *)&ro);
		rt = ro6.ro_rt;
		break;
#endif /* INET6 */
	default:
		panic("pf_calc_mss: not AF_INET or AF_INET6!");
		return (0);
	}

	if (rt && rt->rt_ifp) {
		 /* This is relevant only for PF SYN Proxy */
		int interface_mtu = rt->rt_ifp->if_mtu;

		if (af == AF_INET &&
		    INTF_ADJUST_MTU_FOR_CLAT46(rt->rt_ifp)) {
			interface_mtu = IN6_LINKMTU(rt->rt_ifp);
			/* Further adjust the size for CLAT46 expansion */
			interface_mtu -= CLAT46_HDR_EXPANSION_OVERHD;
		}
		mss = interface_mtu - hlen - sizeof (struct tcphdr);
		mss = max(tcp_mssdflt, mss);
		rtfree(rt);
	}
	mss = min(mss, offer);
	mss = max(mss, 64);		/* sanity - at least max opt space */
	return (mss);
}