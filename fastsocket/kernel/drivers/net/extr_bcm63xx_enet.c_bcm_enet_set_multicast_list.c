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
typedef  int u8 ;
typedef  int u32 ;
struct net_device {int flags; int mc_count; struct dev_mc_list* mc_list; } ;
struct dev_mc_list {int dmi_addrlen; int* dmi_addr; struct dev_mc_list* next; } ;
struct bcm_enet_priv {int dummy; } ;

/* Variables and functions */
 int ENET_PMH_DATAVALID_MASK ; 
 int /*<<< orphan*/  ENET_PMH_REG (int) ; 
 int /*<<< orphan*/  ENET_PML_REG (int) ; 
 int ENET_RXCFG_ALLMCAST_MASK ; 
 int ENET_RXCFG_PROMISC_MASK ; 
 int /*<<< orphan*/  ENET_RXCFG_REG ; 
 int IFF_ALLMULTI ; 
 int IFF_PROMISC ; 
 int enet_readl (struct bcm_enet_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  enet_writel (struct bcm_enet_priv*,int,int /*<<< orphan*/ ) ; 
 struct bcm_enet_priv* netdev_priv (struct net_device*) ; 

__attribute__((used)) static void bcm_enet_set_multicast_list(struct net_device *dev)
{
	struct bcm_enet_priv *priv;
	struct dev_mc_list *mc_list;
	u32 val;
	int i;

	priv = netdev_priv(dev);

	val = enet_readl(priv, ENET_RXCFG_REG);

	if (dev->flags & IFF_PROMISC)
		val |= ENET_RXCFG_PROMISC_MASK;
	else
		val &= ~ENET_RXCFG_PROMISC_MASK;

	/* only 3 perfect match registers left, first one is used for
	 * own mac address */
	if ((dev->flags & IFF_ALLMULTI) || dev->mc_count > 3)
		val |= ENET_RXCFG_ALLMCAST_MASK;
	else
		val &= ~ENET_RXCFG_ALLMCAST_MASK;

	/* no need to set perfect match registers if we catch all
	 * multicast */
	if (val & ENET_RXCFG_ALLMCAST_MASK) {
		enet_writel(priv, val, ENET_RXCFG_REG);
		return;
	}

	for (i = 0, mc_list = dev->mc_list;
	     (mc_list != NULL) && (i < dev->mc_count) && (i < 3);
	     i++, mc_list = mc_list->next) {
		u8 *dmi_addr;
		u32 tmp;

		/* filter non ethernet address */
		if (mc_list->dmi_addrlen != 6)
			continue;

		/* update perfect match registers */
		dmi_addr = mc_list->dmi_addr;
		tmp = (dmi_addr[2] << 24) | (dmi_addr[3] << 16) |
			(dmi_addr[4] << 8) | dmi_addr[5];
		enet_writel(priv, tmp, ENET_PML_REG(i + 1));

		tmp = (dmi_addr[0] << 8 | dmi_addr[1]);
		tmp |= ENET_PMH_DATAVALID_MASK;
		enet_writel(priv, tmp, ENET_PMH_REG(i + 1));
	}

	for (; i < 3; i++) {
		enet_writel(priv, 0, ENET_PML_REG(i + 1));
		enet_writel(priv, 0, ENET_PMH_REG(i + 1));
	}

	enet_writel(priv, val, ENET_RXCFG_REG);
}