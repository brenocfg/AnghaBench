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
struct plat_cpmac_data {int /*<<< orphan*/  reset_bit; } ;
struct net_device {int dummy; } ;
struct cpmac_priv {int /*<<< orphan*/  regs; TYPE_2__* pdev; } ;
struct TYPE_3__ {struct plat_cpmac_data* platform_data; } ;
struct TYPE_4__ {TYPE_1__ dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  CPMAC_MAC_CONTROL ; 
 int /*<<< orphan*/  CPMAC_MAC_INT_CLEAR ; 
 int /*<<< orphan*/  CPMAC_RX_CONTROL ; 
 int /*<<< orphan*/  CPMAC_RX_INT_CLEAR ; 
 int /*<<< orphan*/  CPMAC_RX_PTR (int) ; 
 int /*<<< orphan*/  CPMAC_TX_CONTROL ; 
 int /*<<< orphan*/  CPMAC_TX_INT_CLEAR ; 
 int /*<<< orphan*/  CPMAC_TX_PTR (int) ; 
 int /*<<< orphan*/  CPMAC_UNICAST_CLEAR ; 
 int MAC_MII ; 
 int /*<<< orphan*/  ar7_device_reset (int /*<<< orphan*/ ) ; 
 int cpmac_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpmac_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct cpmac_priv* netdev_priv (struct net_device*) ; 

__attribute__((used)) static void cpmac_hw_stop(struct net_device *dev)
{
	int i;
	struct cpmac_priv *priv = netdev_priv(dev);
	struct plat_cpmac_data *pdata = priv->pdev->dev.platform_data;

	ar7_device_reset(pdata->reset_bit);
	cpmac_write(priv->regs, CPMAC_RX_CONTROL,
		    cpmac_read(priv->regs, CPMAC_RX_CONTROL) & ~1);
	cpmac_write(priv->regs, CPMAC_TX_CONTROL,
		    cpmac_read(priv->regs, CPMAC_TX_CONTROL) & ~1);
	for (i = 0; i < 8; i++) {
		cpmac_write(priv->regs, CPMAC_TX_PTR(i), 0);
		cpmac_write(priv->regs, CPMAC_RX_PTR(i), 0);
	}
	cpmac_write(priv->regs, CPMAC_UNICAST_CLEAR, 0xff);
	cpmac_write(priv->regs, CPMAC_RX_INT_CLEAR, 0xff);
	cpmac_write(priv->regs, CPMAC_TX_INT_CLEAR, 0xff);
	cpmac_write(priv->regs, CPMAC_MAC_INT_CLEAR, 0xff);
	cpmac_write(priv->regs, CPMAC_MAC_CONTROL,
		    cpmac_read(priv->regs, CPMAC_MAC_CONTROL) & ~MAC_MII);
}