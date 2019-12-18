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
struct TYPE_3__ {int /*<<< orphan*/  sin6_addr; } ;
struct nd_prefix {scalar_t__ ndpr_ifp; scalar_t__ ndpr_plen; int ndpr_expire; TYPE_1__ ndpr_prefix; struct nd_prefix* ndpr_next; } ;
struct TYPE_4__ {struct nd_prefix* lh_first; } ;

/* Variables and functions */
 int ND6_PREFIX_EXPIRY_UNSPEC ; 
 int /*<<< orphan*/  NDPR_ADDREF_LOCKED (struct nd_prefix*) ; 
 int /*<<< orphan*/  NDPR_LOCK (struct nd_prefix*) ; 
 int /*<<< orphan*/  NDPR_UNLOCK (struct nd_prefix*) ; 
 scalar_t__ in6_are_prefix_equal (int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  lck_mtx_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lck_mtx_unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nd6_mutex ; 
 TYPE_2__ nd_prefix ; 

struct nd_prefix *
nd6_prefix_lookup(struct nd_prefix *pr, int nd6_prefix_expiry)
{
	struct nd_prefix *search;

	lck_mtx_lock(nd6_mutex);
	for (search = nd_prefix.lh_first; search; search = search->ndpr_next) {
		NDPR_LOCK(search);
		if (pr->ndpr_ifp == search->ndpr_ifp &&
		    pr->ndpr_plen == search->ndpr_plen &&
		    in6_are_prefix_equal(&pr->ndpr_prefix.sin6_addr,
		    &search->ndpr_prefix.sin6_addr, pr->ndpr_plen)) {
			if (nd6_prefix_expiry != ND6_PREFIX_EXPIRY_UNSPEC) {
				search->ndpr_expire = nd6_prefix_expiry;
			}
			NDPR_ADDREF_LOCKED(search);
			NDPR_UNLOCK(search);
			break;
		}
		NDPR_UNLOCK(search);
	}
	lck_mtx_unlock(nd6_mutex);

	return (search);
}