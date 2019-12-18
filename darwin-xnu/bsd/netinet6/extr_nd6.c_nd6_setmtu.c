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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  scalar_t__ u_int32_t ;
struct nd_ifinfo {scalar_t__ initialized; scalar_t__ maxmtu; scalar_t__ linkmtu; int /*<<< orphan*/  lock; } ;
struct ifnet {scalar_t__ if_mtu; } ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 scalar_t__ IPV6_MMTU ; 
 int /*<<< orphan*/  LOG_NOTICE ; 
 struct nd_ifinfo* ND_IFINFO (struct ifnet*) ; 
 int /*<<< orphan*/  if_name (struct ifnet*) ; 
 scalar_t__ in6_maxmtu ; 
 int /*<<< orphan*/  in6_setmaxmtu () ; 
 int /*<<< orphan*/  lck_mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lck_mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  log (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
nd6_setmtu(struct ifnet *ifp)
{
	struct nd_ifinfo *ndi = ND_IFINFO(ifp);
	u_int32_t oldmaxmtu, maxmtu;

	if ((NULL == ndi) || (FALSE == ndi->initialized)) {
		return;
	}

	lck_mtx_lock(&ndi->lock);
	oldmaxmtu = ndi->maxmtu;

	/*
	 * The ND level maxmtu is somewhat redundant to the interface MTU
	 * and is an implementation artifact of KAME.  Instead of hard-
	 * limiting the maxmtu based on the interface type here, we simply
	 * take the if_mtu value since SIOCSIFMTU would have taken care of
	 * the sanity checks related to the maximum MTU allowed for the
	 * interface (a value that is known only by the interface layer),
	 * by sending the request down via ifnet_ioctl().  The use of the
	 * ND level maxmtu and linkmtu are done via IN6_LINKMTU() which
	 * does further checking against if_mtu.
	 */
	maxmtu = ndi->maxmtu = ifp->if_mtu;

	/*
	 * Decreasing the interface MTU under IPV6 minimum MTU may cause
	 * undesirable situation.  We thus notify the operator of the change
	 * explicitly.  The check for oldmaxmtu is necessary to restrict the
	 * log to the case of changing the MTU, not initializing it.
	 */
	if (oldmaxmtu >= IPV6_MMTU && ndi->maxmtu < IPV6_MMTU) {
		log(LOG_NOTICE, "nd6_setmtu: "
		    "new link MTU on %s (%u) is too small for IPv6\n",
		    if_name(ifp), (uint32_t)ndi->maxmtu);
	}
	ndi->linkmtu = ifp->if_mtu;
	lck_mtx_unlock(&ndi->lock);

	/* also adjust in6_maxmtu if necessary. */
	if (maxmtu > in6_maxmtu) {
		in6_setmaxmtu();
	}
}