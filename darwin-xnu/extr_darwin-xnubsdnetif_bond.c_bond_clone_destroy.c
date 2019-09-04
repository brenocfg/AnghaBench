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
 scalar_t__ IFT_IEEE8023ADLAG ; 
 int /*<<< orphan*/  bond_if_detach (struct ifnet*) ; 
 int /*<<< orphan*/  bond_lock () ; 
 int /*<<< orphan*/  bond_remove (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bond_unlock () ; 
 scalar_t__ ifbond_flags_if_detaching (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ifnet_softc (struct ifnet*) ; 
 scalar_t__ ifnet_type (struct ifnet*) ; 

__attribute__((used)) static int
bond_clone_destroy(struct ifnet * ifp)
{
    ifbond_ref ifb;

    bond_lock();
    ifb = ifnet_softc(ifp);
    if (ifb == NULL || ifnet_type(ifp) != IFT_IEEE8023ADLAG) {
	bond_unlock();
	return 0;
    }
    if (ifbond_flags_if_detaching(ifb)) {
	bond_unlock();
	return 0;
    }
    bond_remove(ifb);
    bond_unlock();
    bond_if_detach(ifp);
    return 0;
}