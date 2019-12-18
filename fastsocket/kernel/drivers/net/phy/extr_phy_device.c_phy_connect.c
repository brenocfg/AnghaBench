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
struct phy_device {int dummy; } ;
struct net_device {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  phy_interface_t ;

/* Variables and functions */
 int ENODEV ; 
 struct phy_device* ERR_PTR (int) ; 
 struct device* bus_find_device_by_name (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  mdio_bus_type ; 
 int phy_connect_direct (struct net_device*,struct phy_device*,void (*) (struct net_device*),int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*,char const*) ; 
 struct phy_device* to_phy_device (struct device*) ; 

struct phy_device * phy_connect(struct net_device *dev, const char *bus_id,
		void (*handler)(struct net_device *), u32 flags,
		phy_interface_t interface)
{
	struct phy_device *phydev;
	struct device *d;
	int rc;

	/* Search the list of PHY devices on the mdio bus for the
	 * PHY with the requested name */
	d = bus_find_device_by_name(&mdio_bus_type, NULL, bus_id);
	if (!d) {
		pr_err("PHY %s not found\n", bus_id);
		return ERR_PTR(-ENODEV);
	}
	phydev = to_phy_device(d);

	rc = phy_connect_direct(dev, phydev, handler, flags, interface);
	if (rc)
		return ERR_PTR(rc);

	return phydev;
}