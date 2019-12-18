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
struct net_device {int dummy; } ;
struct jme_adapter {int /*<<< orphan*/  pdev; } ;

/* Variables and functions */
 int JME_PHY_TIMEOUT ; 
 int /*<<< orphan*/  JME_SMI ; 
 int SMI_DATA_MASK ; 
 int SMI_DATA_SHIFT ; 
 int SMI_OP_REQ ; 
 int SMI_OP_WRITE ; 
 int /*<<< orphan*/  jeprintk (int /*<<< orphan*/ ,char*,int,int) ; 
 int jread32 (struct jme_adapter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jwrite32 (struct jme_adapter*,int /*<<< orphan*/ ,int) ; 
 struct jme_adapter* netdev_priv (struct net_device*) ; 
 int smi_phy_addr (int) ; 
 int smi_reg_addr (int) ; 
 int /*<<< orphan*/  udelay (int) ; 
 int /*<<< orphan*/  wmb () ; 

__attribute__((used)) static void
jme_mdio_write(struct net_device *netdev,
				int phy, int reg, int val)
{
	struct jme_adapter *jme = netdev_priv(netdev);
	int i;

	jwrite32(jme, JME_SMI, SMI_OP_WRITE | SMI_OP_REQ |
		((val << SMI_DATA_SHIFT) & SMI_DATA_MASK) |
		smi_phy_addr(phy) | smi_reg_addr(reg));

	wmb();
	for (i = JME_PHY_TIMEOUT * 50 ; i > 0 ; --i) {
		udelay(20);
		if ((jread32(jme, JME_SMI) & SMI_OP_REQ) == 0)
			break;
	}

	if (i == 0)
		jeprintk(jme->pdev, "phy(%d) write timeout : %d\n", phy, reg);

	return;
}