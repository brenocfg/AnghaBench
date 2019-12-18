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
typedef  int /*<<< orphan*/  u32 ;
struct phy_device {scalar_t__ irq; } ;
struct net_device {int dummy; } ;
typedef  int /*<<< orphan*/  phy_interface_t ;

/* Variables and functions */
 int phy_attach_direct (struct net_device*,struct phy_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  phy_prepare_link (struct phy_device*,void (*) (struct net_device*)) ; 
 int /*<<< orphan*/  phy_start_interrupts (struct phy_device*) ; 
 int /*<<< orphan*/  phy_start_machine (struct phy_device*,int /*<<< orphan*/ *) ; 

int phy_connect_direct(struct net_device *dev, struct phy_device *phydev,
		       void (*handler)(struct net_device *), u32 flags,
		       phy_interface_t interface)
{
	int rc;

	rc = phy_attach_direct(dev, phydev, flags, interface);
	if (rc)
		return rc;

	phy_prepare_link(phydev, handler);
	phy_start_machine(phydev, NULL);
	if (phydev->irq > 0)
		phy_start_interrupts(phydev);

	return 0;
}