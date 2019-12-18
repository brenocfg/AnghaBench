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
struct rtentry {int rt_flags; int /*<<< orphan*/  rt_rmx; } ;
struct rmxp_tao {int dummy; } ;
struct inpcb {int inp_vflag; } ;

/* Variables and functions */
 int /*<<< orphan*/  IFSCOPE_NONE ; 
 int INP_IPV6 ; 
 int RTF_HOST ; 
 int RTF_UP ; 
 int /*<<< orphan*/  RT_UNLOCK (struct rtentry*) ; 
 struct rmxp_tao* rmx_taop (int /*<<< orphan*/ ) ; 
 struct rtentry* tcp_rtlookup (struct inpcb*,int /*<<< orphan*/ ) ; 
 struct rtentry* tcp_rtlookup6 (struct inpcb*,int /*<<< orphan*/ ) ; 

struct rmxp_tao *
tcp_gettaocache(struct inpcb *inp)
{
	struct rtentry *rt;
	struct rmxp_tao *taop;

#if INET6
	if ((inp->inp_vflag & INP_IPV6) != 0)
		rt = tcp_rtlookup6(inp, IFSCOPE_NONE);
	else
#endif /* INET6 */
	rt = tcp_rtlookup(inp, IFSCOPE_NONE);

	/* Make sure this is a host route and is up. */
	if (rt == NULL ||
	    (rt->rt_flags & (RTF_UP|RTF_HOST)) != (RTF_UP|RTF_HOST)) {
		/* Route locked during lookup above */
		if (rt != NULL)
			RT_UNLOCK(rt);
		return (NULL);
	}

	taop = rmx_taop(rt->rt_rmx);
	/* Route locked during lookup above */
	RT_UNLOCK(rt);
	return (taop);
}