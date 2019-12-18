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
struct phy_device {void (* adjust_state ) (struct net_device*) ;int /*<<< orphan*/  state_queue; } ;

/* Variables and functions */
 int /*<<< orphan*/  HZ ; 
 int /*<<< orphan*/  INIT_DELAYED_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  phy_state_machine ; 
 int /*<<< orphan*/  schedule_delayed_work (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void phy_start_machine(struct phy_device *phydev,
		void (*handler)(struct net_device *))
{
	phydev->adjust_state = handler;

	INIT_DELAYED_WORK(&phydev->state_queue, phy_state_machine);
	schedule_delayed_work(&phydev->state_queue, HZ);
}