#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_int32_t ;
struct TYPE_7__ {int /*<<< orphan*/  sin6_addr; } ;
struct nd_prefix {int ndpr_stateflags; TYPE_3__ ndpr_prefix; struct nd_prefix* ndpr_next; } ;
struct TYPE_6__ {int /*<<< orphan*/  sin6_addr; } ;
struct TYPE_5__ {int /*<<< orphan*/  sin6_addr; } ;
struct in6_ifaddr {int /*<<< orphan*/  ia_ifa; int /*<<< orphan*/  ia_plen; TYPE_2__ ia_prefixmask; TYPE_1__ ia_addr; } ;
struct in6_addr {int dummy; } ;
typedef  int /*<<< orphan*/  pr_mask ;
typedef  int /*<<< orphan*/  boolean_t ;
typedef  int /*<<< orphan*/  addr ;
struct TYPE_8__ {struct nd_prefix* lh_first; } ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  IFA_LOCK (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IFA_UNLOCK (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LCK_MTX_ASSERT (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LCK_MTX_ASSERT_NOTOWNED ; 
 int NDPRF_ONLINK ; 
 int NDPRF_PRPROXY ; 
 int /*<<< orphan*/  NDPR_LOCK (struct nd_prefix*) ; 
 int /*<<< orphan*/  NDPR_UNLOCK (struct nd_prefix*) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  bcopy (int /*<<< orphan*/ *,struct in6_addr*,int) ; 
 scalar_t__ in6_are_prefix_equal (int /*<<< orphan*/ *,struct in6_addr*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lck_mtx_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lck_mtx_unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nd6_mutex ; 
 TYPE_4__ nd_prefix ; 

boolean_t
nd6_prproxy_ifaddr(struct in6_ifaddr *ia)
{
	struct nd_prefix *pr;
	struct in6_addr addr, pr_mask;
	u_int32_t pr_len;
	boolean_t proxied = FALSE;

	LCK_MTX_ASSERT(nd6_mutex, LCK_MTX_ASSERT_NOTOWNED);

	IFA_LOCK(&ia->ia_ifa);
	bcopy(&ia->ia_addr.sin6_addr, &addr, sizeof (addr));
	bcopy(&ia->ia_prefixmask.sin6_addr, &pr_mask, sizeof (pr_mask));
	pr_len = ia->ia_plen;
	IFA_UNLOCK(&ia->ia_ifa);

	lck_mtx_lock(nd6_mutex);
	for (pr = nd_prefix.lh_first; pr; pr = pr->ndpr_next) {
		NDPR_LOCK(pr);
		if ((pr->ndpr_stateflags & NDPRF_ONLINK) &&
		    (pr->ndpr_stateflags & NDPRF_PRPROXY) &&
		    in6_are_prefix_equal(&pr->ndpr_prefix.sin6_addr,
		    &addr, pr_len)) {
			NDPR_UNLOCK(pr);
			proxied = TRUE;
			break;
		}
		NDPR_UNLOCK(pr);
	}
	lck_mtx_unlock(nd6_mutex);

	return (proxied);
}