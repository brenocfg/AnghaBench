#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct ifnet {int dummy; } ;
typedef  TYPE_1__* ifbond_ref ;
struct TYPE_9__ {int ifb_altmtu; } ;

/* Variables and functions */
 int EBUSY ; 
 int EINVAL ; 
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  bond_get_mtu_values (TYPE_1__*,int*,int*) ; 
 int /*<<< orphan*/  bond_lock () ; 
 int bond_set_mtu_on_ports (TYPE_1__*,int) ; 
 int /*<<< orphan*/  bond_unlock () ; 
 scalar_t__ ifbond_flags_if_detaching (TYPE_1__*) ; 
 int /*<<< orphan*/  ifbond_release (TYPE_1__*) ; 
 int /*<<< orphan*/  ifbond_retain (TYPE_1__*) ; 
 int /*<<< orphan*/  ifbond_signal (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  ifbond_wait (TYPE_1__*,char*) ; 
 scalar_t__ ifnet_mtu (struct ifnet*) ; 
 int /*<<< orphan*/  ifnet_set_mtu (struct ifnet*,int) ; 
 int /*<<< orphan*/ * ifnet_softc (struct ifnet*) ; 

__attribute__((used)) static int
bond_set_mtu(struct ifnet * ifp, int mtu, int isdevmtu)
{
    int			error = 0;
    ifbond_ref		ifb;
    int			mtu_min;
    int			mtu_max;
    int			new_max;
    int			old_max;

    bond_lock();
    ifb = (ifbond_ref)ifnet_softc(ifp);
    if (ifb == NULL || ifbond_flags_if_detaching(ifb)) {
	error = (ifb == NULL) ? EOPNOTSUPP : EBUSY;
	goto done;
    }
    ifbond_retain(ifb);
    ifbond_wait(ifb, "bond_set_mtu");

    /* check again */
    if (ifnet_softc(ifp) == NULL || ifbond_flags_if_detaching(ifb)) {
	error = EBUSY;
	goto signal_done;
    }
    bond_get_mtu_values(ifb, &mtu_min, &mtu_max);
    if (mtu > mtu_max) {
	error = EINVAL;
	goto signal_done;
    }
    if (mtu < mtu_min && (isdevmtu == 0 || mtu != 0)) {
	/* allow SIOCSIFALTMTU to set the mtu to 0 */
	error = EINVAL;
	goto signal_done;
    }
    if (isdevmtu) {
	new_max = (mtu > (int)ifnet_mtu(ifp)) ? mtu : (int)ifnet_mtu(ifp);
    }
    else {
	new_max = (mtu > ifb->ifb_altmtu) ? mtu : ifb->ifb_altmtu;
    }
    old_max = ((int)ifnet_mtu(ifp) > ifb->ifb_altmtu) 
	? (int)ifnet_mtu(ifp) : ifb->ifb_altmtu;
    if (new_max != old_max) {
	/* we can safely walk the list of port without the lock held */
	bond_unlock();
	error = bond_set_mtu_on_ports(ifb, new_max);
	if (error != 0) {
	    /* try our best to back out of it */
	    (void)bond_set_mtu_on_ports(ifb, old_max);
	}
	bond_lock();
    }
    if (error == 0) {
	if (isdevmtu) {
	    ifb->ifb_altmtu = mtu;
	}
	else {
		ifnet_set_mtu(ifp, mtu);
	}
    }

 signal_done:
    ifbond_signal(ifb, "bond_set_mtu");
    ifbond_release(ifb);
    
 done:
    bond_unlock();
    return (error);
}