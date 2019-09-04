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
typedef  int /*<<< orphan*/ * ifvlan_ref ;

/* Variables and functions */
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  ifnet_detach (struct ifnet*) ; 
 int /*<<< orphan*/ * ifnet_get_ifvlan_retained (struct ifnet*) ; 
 int /*<<< orphan*/  ifvlan_release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlan_lock () ; 
 scalar_t__ vlan_remove (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlan_unlock () ; 

__attribute__((used)) static int
vlan_clone_destroy(struct ifnet *ifp)
{
    ifvlan_ref ifv;

    vlan_lock();
    ifv = ifnet_get_ifvlan_retained(ifp);
    if (ifv == NULL) {
	vlan_unlock();
	return 0;
    }
    if (vlan_remove(ifv, TRUE) == 0) {
	vlan_unlock();
	ifvlan_release(ifv);
	return 0;
    }
    vlan_unlock();
    ifvlan_release(ifv);
    ifnet_detach(ifp);

    return 0;
}