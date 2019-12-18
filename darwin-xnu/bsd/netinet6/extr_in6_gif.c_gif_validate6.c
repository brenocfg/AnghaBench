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
struct sockaddr_in6 {int sin6_len; int /*<<< orphan*/  sin6_addr; int /*<<< orphan*/  sin6_family; } ;
struct sockaddr {int dummy; } ;
struct rtentry {struct ifnet* rt_ifp; } ;
struct ip6_hdr {int /*<<< orphan*/  ip6_src; int /*<<< orphan*/  ip6_dst; } ;
struct ifnet {int dummy; } ;
struct gif_softc {int /*<<< orphan*/  gif_if; scalar_t__ gif_pdst; scalar_t__ gif_psrc; } ;
typedef  int /*<<< orphan*/  sin6 ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET6 ; 
 int IFF_LINK2 ; 
 int /*<<< orphan*/  IN6_ARE_ADDR_EQUAL (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LOG_WARNING ; 
 int /*<<< orphan*/  RT_LOCK (struct rtentry*) ; 
 int /*<<< orphan*/  RT_UNLOCK (struct rtentry*) ; 
 int /*<<< orphan*/  bzero (struct sockaddr_in6*,int) ; 
 int /*<<< orphan*/  if_name (int /*<<< orphan*/ *) ; 
 int ifnet_flags (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ip6_sprintf (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  log (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct rtentry* rtalloc1 (struct sockaddr*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtfree (struct rtentry*) ; 

__attribute__((used)) static int
gif_validate6(
	const struct ip6_hdr *ip6,
	struct gif_softc *sc,
	struct ifnet *ifp)
{
	struct sockaddr_in6 *src, *dst;

	src = (struct sockaddr_in6 *)(void *)sc->gif_psrc;
	dst = (struct sockaddr_in6 *)(void *)sc->gif_pdst;

	/*
	 * Check for address match.  Note that the check is for an incoming
	 * packet.  We should compare the *source* address in our configuration
	 * and the *destination* address of the packet, and vice versa.
	 */
	if (!IN6_ARE_ADDR_EQUAL(&src->sin6_addr, &ip6->ip6_dst) ||
	    !IN6_ARE_ADDR_EQUAL(&dst->sin6_addr, &ip6->ip6_src))
		return (0);

	/* martian filters on outer source - done in ip6_input */

	/* ingress filters on outer source */
	if ((ifnet_flags(sc->gif_if) & IFF_LINK2) == 0 && ifp) {
		struct sockaddr_in6 sin6;
		struct rtentry *rt;

		bzero(&sin6, sizeof (sin6));
		sin6.sin6_family = AF_INET6;
		sin6.sin6_len = sizeof (struct sockaddr_in6);
		sin6.sin6_addr = ip6->ip6_src;

		rt = rtalloc1((struct sockaddr *)&sin6, 0, 0);
		if (rt != NULL)
			RT_LOCK(rt);
		if (!rt || rt->rt_ifp != ifp) {
#if 0
			log(LOG_WARNING, "%s: packet from %s dropped "
			    "due to ingress filter\n", if_name(&sc->gif_if),
			    ip6_sprintf(&sin6.sin6_addr));
#endif
			if (rt != NULL) {
				RT_UNLOCK(rt);
				rtfree(rt);
			}
			return (0);
		}
		RT_UNLOCK(rt);
		rtfree(rt);
	}

	return (128 * 2);
}