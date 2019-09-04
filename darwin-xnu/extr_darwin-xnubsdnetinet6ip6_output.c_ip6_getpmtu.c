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
typedef  scalar_t__ u_int32_t ;
struct in6_addr {int dummy; } ;
struct sockaddr_in6 {int sin6_len; struct in6_addr sin6_addr; int /*<<< orphan*/  sin6_family; } ;
struct route_in6 {TYPE_2__* ro_rt; int /*<<< orphan*/  ro_dst; } ;
struct route {int dummy; } ;
struct ifnet {int /*<<< orphan*/  if_index; } ;
typedef  int /*<<< orphan*/  boolean_t ;
struct TYPE_3__ {scalar_t__ rmx_mtu; int rmx_locks; } ;
struct TYPE_4__ {TYPE_1__ rt_rmx; struct ifnet* rt_ifp; } ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET6 ; 
 int EHOSTUNREACH ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  IFSCOPE_NONE ; 
 int /*<<< orphan*/  IN6_ARE_ADDR_EQUAL (struct in6_addr*,struct in6_addr*) ; 
 scalar_t__ IN6_IS_SCOPE_LINKLOCAL (struct in6_addr*) ; 
 scalar_t__ IN6_LINKMTU (struct ifnet*) ; 
 scalar_t__ IPV6_MMTU ; 
 int /*<<< orphan*/  ROUTE_RELEASE (struct route_in6*) ; 
 scalar_t__ ROUTE_UNUSABLE (struct route_in6*) ; 
 int RTV_MTU ; 
 struct sockaddr_in6* SIN6 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  bzero (struct sockaddr_in6*,int) ; 
 int /*<<< orphan*/  rtalloc_scoped (struct route*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ip6_getpmtu(struct route_in6 *ro_pmtu, struct route_in6 *ro,
    struct ifnet *ifp, struct in6_addr *dst, u_int32_t *mtup,
    boolean_t *alwaysfragp)
{
	u_int32_t mtu = 0;
	boolean_t alwaysfrag = FALSE;
	int error = 0;
	boolean_t is_local = FALSE;

	if (IN6_IS_SCOPE_LINKLOCAL(dst))
		is_local = TRUE;

	if (ro_pmtu != ro) {
		/* The first hop and the final destination may differ. */
		struct sockaddr_in6 *sa6_dst = SIN6(&ro_pmtu->ro_dst);
		if (ROUTE_UNUSABLE(ro_pmtu) ||
		    !IN6_ARE_ADDR_EQUAL(&sa6_dst->sin6_addr, dst))
			ROUTE_RELEASE(ro_pmtu);

		if (ro_pmtu->ro_rt == NULL) {
			bzero(sa6_dst, sizeof (*sa6_dst));
			sa6_dst->sin6_family = AF_INET6;
			sa6_dst->sin6_len = sizeof (struct sockaddr_in6);
			sa6_dst->sin6_addr = *dst;

			rtalloc_scoped((struct route *)ro_pmtu,
			    ifp != NULL ? ifp->if_index : IFSCOPE_NONE);
		}
	}

	if (ro_pmtu->ro_rt != NULL) {
		u_int32_t ifmtu;

		if (ifp == NULL)
			ifp = ro_pmtu->ro_rt->rt_ifp;
		/* Access without acquiring nd_ifinfo lock for performance */
		ifmtu = IN6_LINKMTU(ifp);

		/*
		 * Access rmx_mtu without holding the route entry lock,
		 * for performance; this isn't something that changes
		 * often, so optimize.
		 */
		mtu = ro_pmtu->ro_rt->rt_rmx.rmx_mtu;
		if (mtu > ifmtu || mtu == 0) {
			/*
			 * The MTU on the route is larger than the MTU on
			 * the interface!  This shouldn't happen, unless the
			 * MTU of the interface has been changed after the
			 * interface was brought up.  Change the MTU in the
			 * route to match the interface MTU (as long as the
			 * field isn't locked).
			 *
			 * if MTU on the route is 0, we need to fix the MTU.
			 * this case happens with path MTU discovery timeouts.
			 */
			mtu = ifmtu;
			if (!(ro_pmtu->ro_rt->rt_rmx.rmx_locks & RTV_MTU))
				ro_pmtu->ro_rt->rt_rmx.rmx_mtu = mtu; /* XXX */
		} else if (mtu < IPV6_MMTU) {
			/*
			 * RFC2460 section 5, last paragraph:
			 * if we record ICMPv6 too big message with
			 * mtu < IPV6_MMTU, transmit packets sized IPV6_MMTU
			 * or smaller, with framgent header attached.
			 * (fragment header is needed regardless from the
			 * packet size, for translators to identify packets)
			 */
			alwaysfrag = TRUE;
			mtu = IPV6_MMTU;
		}
	} else {
		if (ifp) {
			/* Don't hold nd_ifinfo lock for performance */
			mtu = IN6_LINKMTU(ifp);
		} else {
			error = EHOSTUNREACH; /* XXX */
		}
	}

	*mtup = mtu;
	if ((alwaysfragp != NULL) && !is_local)
		*alwaysfragp = alwaysfrag;
	return (error);
}