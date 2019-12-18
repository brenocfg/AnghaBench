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
struct TYPE_2__ {scalar_t__ mode; scalar_t__ arp_interval; scalar_t__ miimon; } ;
struct bonding {int kill_timers; int /*<<< orphan*/  mcast_work; int /*<<< orphan*/  ad_work; TYPE_1__ params; int /*<<< orphan*/  alb_work; int /*<<< orphan*/  arp_work; int /*<<< orphan*/  mii_work; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 scalar_t__ BOND_MODE_8023AD ; 
 scalar_t__ BOND_MODE_ALB ; 
 int /*<<< orphan*/  cancel_delayed_work (int /*<<< orphan*/ *) ; 
 scalar_t__ delayed_work_pending (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void bond_work_cancel_all(struct bonding *bond)
{
	write_lock_bh(&bond->lock);
	bond->kill_timers = 1;
	write_unlock_bh(&bond->lock);

	if (bond->params.miimon && delayed_work_pending(&bond->mii_work))
		cancel_delayed_work(&bond->mii_work);

	if (bond->params.arp_interval && delayed_work_pending(&bond->arp_work))
		cancel_delayed_work(&bond->arp_work);

	if (bond->params.mode == BOND_MODE_ALB &&
	    delayed_work_pending(&bond->alb_work))
		cancel_delayed_work(&bond->alb_work);

	if (bond->params.mode == BOND_MODE_8023AD &&
	    delayed_work_pending(&bond->ad_work))
		cancel_delayed_work(&bond->ad_work);

	if (delayed_work_pending(&bond->mcast_work))
		cancel_delayed_work(&bond->mcast_work);
}