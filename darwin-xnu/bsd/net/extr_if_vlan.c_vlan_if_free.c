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
 int /*<<< orphan*/  ifnet_release (struct ifnet*) ; 
 scalar_t__ ifnet_softc (struct ifnet*) ; 
 int /*<<< orphan*/  ifvlan_release (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void 
vlan_if_free(struct ifnet * ifp)
{
    ifvlan_ref	ifv;

    if (ifp == NULL) {
	return;
    }
    ifv = (ifvlan_ref)ifnet_softc(ifp);
    if (ifv == NULL) {
	return;
    }
    ifvlan_release(ifv);
    ifnet_release(ifp);
    return;
}