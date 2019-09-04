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
struct ifnet {int if_amcount; int /*<<< orphan*/  if_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  IFF_ALLMULTI ; 
 int /*<<< orphan*/  SIOCSIFFLAGS ; 
 int ifnet_ioctl (struct ifnet*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ifnet_lock_done (struct ifnet*) ; 
 int /*<<< orphan*/  ifnet_lock_exclusive (struct ifnet*) ; 
 int /*<<< orphan*/  rt_ifmsg (struct ifnet*) ; 

int
if_allmulti(struct ifnet *ifp, int onswitch)
{
	int error = 0;
	int	modified = 0;

	ifnet_lock_exclusive(ifp);

	if (onswitch) {
		if (ifp->if_amcount++ == 0) {
			ifp->if_flags |= IFF_ALLMULTI;
			modified = 1;
		}
	} else {
		if (ifp->if_amcount > 1) {
			ifp->if_amcount--;
		} else {
			ifp->if_amcount = 0;
			ifp->if_flags &= ~IFF_ALLMULTI;
			modified = 1;
		}
	}
	ifnet_lock_done(ifp);

	if (modified)
		error = ifnet_ioctl(ifp, 0, SIOCSIFFLAGS, NULL);

	if (error == 0)
		rt_ifmsg(ifp);
	return (error);
}