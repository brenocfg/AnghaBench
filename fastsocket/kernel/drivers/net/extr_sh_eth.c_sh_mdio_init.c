#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_5__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct sh_eth_private {TYPE_1__* mii_bus; } ;
struct net_device {int /*<<< orphan*/  dev; scalar_t__ base_addr; } ;
struct TYPE_7__ {int /*<<< orphan*/ * ops; } ;
struct bb_info {int mdi_msk; int mdo_msk; int mmd_msk; int mdc_msk; TYPE_5__ ctrl; scalar_t__ addr; } ;
struct TYPE_6__ {char* name; struct bb_info* irq; int /*<<< orphan*/  id; int /*<<< orphan*/ * parent; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  MII_BUS_ID_SIZE ; 
 int PHY_MAX_ADDR ; 
 struct bb_info PHY_POLL ; 
 scalar_t__ PIR ; 
 TYPE_1__* alloc_mdio_bitbang (TYPE_5__*) ; 
 int /*<<< orphan*/  bb_ops ; 
 int /*<<< orphan*/  dev_set_drvdata (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  free_mdio_bitbang (TYPE_1__*) ; 
 int /*<<< orphan*/  kfree (struct bb_info*) ; 
 struct bb_info* kmalloc (int,int /*<<< orphan*/ ) ; 
 struct bb_info* kzalloc (int,int /*<<< orphan*/ ) ; 
 int mdiobus_register (TYPE_1__*) ; 
 struct sh_eth_private* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static int sh_mdio_init(struct net_device *ndev, int id)
{
	int ret, i;
	struct bb_info *bitbang;
	struct sh_eth_private *mdp = netdev_priv(ndev);

	/* create bit control struct for PHY */
	bitbang = kzalloc(sizeof(struct bb_info), GFP_KERNEL);
	if (!bitbang) {
		ret = -ENOMEM;
		goto out;
	}

	/* bitbang init */
	bitbang->addr = ndev->base_addr + PIR;
	bitbang->mdi_msk = 0x08;
	bitbang->mdo_msk = 0x04;
	bitbang->mmd_msk = 0x02;/* MMD */
	bitbang->mdc_msk = 0x01;
	bitbang->ctrl.ops = &bb_ops;

	/* MII contorller setting */
	mdp->mii_bus = alloc_mdio_bitbang(&bitbang->ctrl);
	if (!mdp->mii_bus) {
		ret = -ENOMEM;
		goto out_free_bitbang;
	}

	/* Hook up MII support for ethtool */
	mdp->mii_bus->name = "sh_mii";
	mdp->mii_bus->parent = &ndev->dev;
	snprintf(mdp->mii_bus->id, MII_BUS_ID_SIZE, "%x", id);

	/* PHY IRQ */
	mdp->mii_bus->irq = kmalloc(sizeof(int)*PHY_MAX_ADDR, GFP_KERNEL);
	if (!mdp->mii_bus->irq) {
		ret = -ENOMEM;
		goto out_free_bus;
	}

	for (i = 0; i < PHY_MAX_ADDR; i++)
		mdp->mii_bus->irq[i] = PHY_POLL;

	/* regist mdio bus */
	ret = mdiobus_register(mdp->mii_bus);
	if (ret)
		goto out_free_irq;

	dev_set_drvdata(&ndev->dev, mdp->mii_bus);

	return 0;

out_free_irq:
	kfree(mdp->mii_bus->irq);

out_free_bus:
	free_mdio_bitbang(mdp->mii_bus);

out_free_bitbang:
	kfree(bitbang);

out:
	return ret;
}