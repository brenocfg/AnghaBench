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
typedef  int u32 ;
struct net_device {int dummy; } ;
struct mdio_ops {int dummy; } ;
struct cphy {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  MDIO_MMD_PCS ; 
 int /*<<< orphan*/  MDIO_MMD_PMAPMD ; 
 int MDIO_STAT2 ; 
 int /*<<< orphan*/  cphy_init (struct cphy*,struct net_device*,int,int /*<<< orphan*/ *,struct mdio_ops const*) ; 
 int /*<<< orphan*/  cphy_mdio_read (struct cphy*,int /*<<< orphan*/ ,int,int*) ; 
 int /*<<< orphan*/  cphy_mdio_write (struct cphy*,int /*<<< orphan*/ ,int,int) ; 
 struct cphy* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  led_init (struct cphy*) ; 
 int /*<<< orphan*/  mv88x201x_ops ; 

__attribute__((used)) static struct cphy *mv88x201x_phy_create(struct net_device *dev, int phy_addr,
					 const struct mdio_ops *mdio_ops)
{
	u32 val;
	struct cphy *cphy = kzalloc(sizeof(*cphy), GFP_KERNEL);

	if (!cphy)
		return NULL;

	cphy_init(cphy, dev, phy_addr, &mv88x201x_ops, mdio_ops);

	/* Commands the PHY to enable XFP's clock. */
	cphy_mdio_read(cphy, MDIO_MMD_PCS, 0x8300, &val);
	cphy_mdio_write(cphy, MDIO_MMD_PCS, 0x8300, val | 1);

	/* Clear link status. Required because of a bug in the PHY.  */
	cphy_mdio_read(cphy, MDIO_MMD_PMAPMD, MDIO_STAT2, &val);
	cphy_mdio_read(cphy, MDIO_MMD_PCS, MDIO_STAT2, &val);

	/* Allows for Link,Ack LED turn on/off */
	led_init(cphy);
	return cphy;
}