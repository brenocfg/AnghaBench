#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct phy_device {int dummy; } ;
struct TYPE_4__ {TYPE_1__* parent; } ;
struct net_device {TYPE_2__ dev; } ;
struct device_node {int dummy; } ;
typedef  int /*<<< orphan*/  phy_interface_t ;
struct TYPE_3__ {int /*<<< orphan*/  archdata; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct phy_device*) ; 
 int /*<<< orphan*/  MII_BUS_ID_SIZE ; 
 char* PHY_ID_FMT ; 
 struct device_node* dev_archdata_get_node (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * of_get_property (struct device_node*,char*,int*) ; 
 struct phy_device* phy_connect (struct net_device*,char*,void (*) (struct net_device*),int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*,int /*<<< orphan*/  const) ; 

struct phy_device *of_phy_connect_fixed_link(struct net_device *dev,
					     void (*hndlr)(struct net_device *),
					     phy_interface_t iface)
{
	struct device_node *net_np;
	char bus_id[MII_BUS_ID_SIZE + 3];
	struct phy_device *phy;
	const u32 *phy_id;
	int sz;

	if (!dev->dev.parent)
		return NULL;

	net_np = dev_archdata_get_node(&dev->dev.parent->archdata);
	if (!net_np)
		return NULL;

	phy_id = of_get_property(net_np, "fixed-link", &sz);
	if (!phy_id || sz < sizeof(*phy_id))
		return NULL;

	sprintf(bus_id, PHY_ID_FMT, "0", phy_id[0]);

	phy = phy_connect(dev, bus_id, hndlr, 0, iface);
	return IS_ERR(phy) ? NULL : phy;
}