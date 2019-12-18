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
typedef  int /*<<< orphan*/ * ifbond_ref ;

/* Variables and functions */
 int /*<<< orphan*/  bond_lock () ; 
 int /*<<< orphan*/  bond_unlock () ; 
 int /*<<< orphan*/  ifbond_release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ifnet_release (struct ifnet*) ; 
 scalar_t__ ifnet_softc (struct ifnet*) ; 

__attribute__((used)) static void 
bond_if_free(struct ifnet * ifp)
{
    ifbond_ref 	ifb;

    if (ifp == NULL) {
	return;
    }
    bond_lock();
    ifb = (ifbond_ref)ifnet_softc(ifp);
    if (ifb == NULL) {
	bond_unlock();
	return;
    }
    ifbond_release(ifb);
    bond_unlock();
    ifnet_release(ifp);
    return;
}