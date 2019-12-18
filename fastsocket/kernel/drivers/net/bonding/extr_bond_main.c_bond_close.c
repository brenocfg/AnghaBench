#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct net_device {int dummy; } ;
struct TYPE_2__ {int mode; scalar_t__ arp_interval; scalar_t__ miimon; scalar_t__ arp_validate; } ;
struct bonding {int kill_timers; int /*<<< orphan*/  mcast_work; int /*<<< orphan*/  alb_work; int /*<<< orphan*/  ad_work; TYPE_1__ params; int /*<<< orphan*/  arp_work; int /*<<< orphan*/  mii_work; int /*<<< orphan*/  lock; scalar_t__ send_unsol_na; scalar_t__ send_grat_arp; } ;

/* Variables and functions */
#define  BOND_MODE_8023AD 130 
#define  BOND_MODE_ALB 129 
#define  BOND_MODE_TLB 128 
 int /*<<< orphan*/  bond_alb_deinitialize (struct bonding*) ; 
 scalar_t__ bond_is_lb (struct bonding*) ; 
 int /*<<< orphan*/  bond_unregister_arp (struct bonding*) ; 
 int /*<<< orphan*/  bond_unregister_lacpdu (struct bonding*) ; 
 int /*<<< orphan*/  cancel_delayed_work (int /*<<< orphan*/ *) ; 
 scalar_t__ delayed_work_pending (int /*<<< orphan*/ *) ; 
 struct bonding* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  write_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int bond_close(struct net_device *bond_dev)
{
	struct bonding *bond = netdev_priv(bond_dev);

	if (bond->params.mode == BOND_MODE_8023AD) {
		/* Unregister the receive of LACPDUs */
		bond_unregister_lacpdu(bond);
	}

	if (bond->params.arp_interval && bond->params.arp_validate)
		bond_unregister_arp(bond);

	write_lock_bh(&bond->lock);

	bond->send_grat_arp = 0;
	bond->send_unsol_na = 0;

	/* signal timers not to re-arm */
	bond->kill_timers = 1;

	write_unlock_bh(&bond->lock);

	if (bond->params.miimon) {  /* link check interval, in milliseconds. */
		cancel_delayed_work(&bond->mii_work);
	}

	if (bond->params.arp_interval) {  /* arp interval, in milliseconds. */
		cancel_delayed_work(&bond->arp_work);
	}

	switch (bond->params.mode) {
	case BOND_MODE_8023AD:
		cancel_delayed_work(&bond->ad_work);
		break;
	case BOND_MODE_TLB:
	case BOND_MODE_ALB:
		cancel_delayed_work(&bond->alb_work);
		break;
	default:
		break;
	}

	if (delayed_work_pending(&bond->mcast_work))
		cancel_delayed_work(&bond->mcast_work);

	if (bond_is_lb(bond)) {
		/* Must be called only after all
		 * slaves have been released
		 */
		bond_alb_deinitialize(bond);
	}

	return 0;
}