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
struct in_ifaddr {int ia_flags; int /*<<< orphan*/  ia_ifa; } ;
struct ifnet {int if_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  IFA_LOCK (int /*<<< orphan*/ *) ; 
 int IFA_ROUTE ; 
 int /*<<< orphan*/  IFA_UNLOCK (int /*<<< orphan*/ *) ; 
 int IFF_LOOPBACK ; 
 int IFF_POINTOPOINT ; 
 int /*<<< orphan*/  RTF_HOST ; 
 scalar_t__ RTM_DELETE ; 
 int /*<<< orphan*/  lck_mtx_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lck_mtx_unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rnh_lock ; 
 int /*<<< orphan*/  rtinit_locked (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 

void
in_ifscrub(struct ifnet *ifp, struct in_ifaddr *ia, int locked)
{
	IFA_LOCK(&ia->ia_ifa);
	if ((ia->ia_flags & IFA_ROUTE) == 0) {
		IFA_UNLOCK(&ia->ia_ifa);
		return;
	}
	IFA_UNLOCK(&ia->ia_ifa);
	if (!locked)
		lck_mtx_lock(rnh_lock);
	if (ifp->if_flags & (IFF_LOOPBACK|IFF_POINTOPOINT))
		rtinit_locked(&(ia->ia_ifa), (int)RTM_DELETE, RTF_HOST);
	else
		rtinit_locked(&(ia->ia_ifa), (int)RTM_DELETE, 0);
	IFA_LOCK(&ia->ia_ifa);
	ia->ia_flags &= ~IFA_ROUTE;
	IFA_UNLOCK(&ia->ia_ifa);
	if (!locked)
		lck_mtx_unlock(rnh_lock);
}