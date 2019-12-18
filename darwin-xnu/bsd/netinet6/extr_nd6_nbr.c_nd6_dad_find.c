#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct nd_opt_nonce {int nd_opt_nonce_len; int /*<<< orphan*/ * nd_opt_nonce; } ;
struct ifaddr {int /*<<< orphan*/  ifa_ifp; } ;
struct TYPE_4__ {struct dadq* tqe_next; } ;
struct dadq {int /*<<< orphan*/  dad_ns_lcount; int /*<<< orphan*/ * dad_nonce; struct ifaddr* dad_ifa; TYPE_1__ dad_list; } ;
struct TYPE_6__ {struct dadq* tqh_first; } ;
struct TYPE_5__ {int /*<<< orphan*/  ip6s_dad_loopcount; } ;

/* Variables and functions */
 int /*<<< orphan*/  DAD_ADDREF_LOCKED (struct dadq*) ; 
 int /*<<< orphan*/  DAD_LOCK_SPIN (struct dadq*) ; 
 int /*<<< orphan*/  DAD_UNLOCK (struct dadq*) ; 
 int /*<<< orphan*/  IFA_IN6 (struct ifaddr*) ; 
 int /*<<< orphan*/  LOG_ERR ; 
 int ND_OPT_NONCE_LEN ; 
 int /*<<< orphan*/  dad6_mutex ; 
 TYPE_3__ dadq ; 
 int /*<<< orphan*/  if_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ip6_sprintf (int /*<<< orphan*/ ) ; 
 TYPE_2__ ip6stat ; 
 int /*<<< orphan*/  lck_mtx_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lck_mtx_unlock (int /*<<< orphan*/ ) ; 
 scalar_t__ memcmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  nd6log (int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct dadq *
nd6_dad_find(struct ifaddr *ifa, struct nd_opt_nonce *nonce)
{
	struct dadq *dp;

	lck_mtx_lock(dad6_mutex);
	for (dp = dadq.tqh_first; dp; dp = dp->dad_list.tqe_next) {
		DAD_LOCK_SPIN(dp);
		if (dp->dad_ifa != ifa) {
			DAD_UNLOCK(dp);
			continue;
		}

		/*
		 * Skip if the nonce matches the received one.
		 * +2 in the length is required because of type and
		 * length fields are included in a header.
		 */
		if (nonce != NULL &&
		    nonce->nd_opt_nonce_len == (ND_OPT_NONCE_LEN + 2) / 8 &&
		    memcmp(&nonce->nd_opt_nonce[0], &dp->dad_nonce[0],
		    ND_OPT_NONCE_LEN) == 0) {
			nd6log((LOG_ERR, "%s: a looped back NS message is "
			    "detected during DAD for %s. Ignoring.\n",
			    if_name(ifa->ifa_ifp),
			    ip6_sprintf(IFA_IN6(ifa))));
			dp->dad_ns_lcount++;
			++ip6stat.ip6s_dad_loopcount;
			DAD_UNLOCK(dp);
			continue;
		}

		DAD_ADDREF_LOCKED(dp);
		DAD_UNLOCK(dp);
		break;
	}
	lck_mtx_unlock(dad6_mutex);
	return (dp);
}