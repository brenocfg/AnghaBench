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
struct ifnet {int dummy; } ;
typedef  struct ifnet* ifnet_t ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  LCK_MTX_ASSERT (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LCK_MTX_ASSERT_NOTOWNED ; 
 int /*<<< orphan*/  LOG_INFO ; 
 int /*<<< orphan*/  defrouter_select (struct ifnet*) ; 
 int if_index ; 
 char* if_name (struct ifnet*) ; 
 struct ifnet** ifindex2ifnet ; 
 int /*<<< orphan*/  ifnet_head_done () ; 
 int /*<<< orphan*/  ifnet_head_lock_shared () ; 
 int /*<<< orphan*/  lck_mtx_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lck_mtx_unlock (int /*<<< orphan*/ ) ; 
 int nd6_defifindex ; 
 struct ifnet* nd6_defifp ; 
 int /*<<< orphan*/  nd6_mutex ; 
 int /*<<< orphan*/  nd6_prefix_sync (struct ifnet*) ; 
 int /*<<< orphan*/  nd6log (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scope6_setdefault (struct ifnet*) ; 

int
nd6_setdefaultiface(
	int ifindex)
{
	int error = 0;
	ifnet_t def_ifp = NULL;

	LCK_MTX_ASSERT(nd6_mutex, LCK_MTX_ASSERT_NOTOWNED);

	ifnet_head_lock_shared();
	if (ifindex < 0 || if_index < ifindex) {
		ifnet_head_done();
		return (EINVAL);
	}
	def_ifp = ifindex2ifnet[ifindex];
	ifnet_head_done();

	lck_mtx_lock(nd6_mutex);
	if (nd6_defifindex != ifindex) {
		struct ifnet *odef_ifp = nd6_defifp;

		nd6_defifindex = ifindex;
		if (nd6_defifindex > 0)
			nd6_defifp = def_ifp;
		else
			nd6_defifp = NULL;

		if (nd6_defifp != NULL)
			nd6log((LOG_INFO, "%s: is now the default "
			    "interface (was %s)\n", if_name(nd6_defifp),
			    odef_ifp != NULL ? if_name(odef_ifp) : "NONE"));
		else
			nd6log((LOG_INFO, "No default interface set\n"));

		/*
		 * If the Default Router List is empty, install a route
		 * to the specified interface as default or remove the default
		 * route when the default interface becomes canceled.
		 * The check for the queue is actually redundant, but
		 * we do this here to avoid re-install the default route
		 * if the list is NOT empty.
		 */
		if (odef_ifp != NULL) {
			defrouter_select(odef_ifp);
		}

		if (nd6_defifp != NULL) {
			defrouter_select(nd6_defifp);
			nd6_prefix_sync(nd6_defifp);
		}

		/*
		 * Our current implementation assumes one-to-one mapping between
		 * interfaces and links, so it would be natural to use the
		 * default interface as the default link.
		 */
		scope6_setdefault(nd6_defifp);
	}
	lck_mtx_unlock(nd6_mutex);
	return (error);
}