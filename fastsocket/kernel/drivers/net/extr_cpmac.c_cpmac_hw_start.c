#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct plat_cpmac_data {int /*<<< orphan*/  reset_bit; } ;
struct net_device {int* dev_addr; } ;
struct cpmac_priv {int /*<<< orphan*/  regs; TYPE_3__* rx_head; TYPE_2__* pdev; } ;
struct TYPE_6__ {int mapping; } ;
struct TYPE_4__ {struct plat_cpmac_data* platform_data; } ;
struct TYPE_5__ {TYPE_1__ dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  CPMAC_BUFFER_OFFSET ; 
 int /*<<< orphan*/  CPMAC_MAC_ADDR_HI ; 
 int /*<<< orphan*/  CPMAC_MAC_ADDR_LO (int) ; 
 int /*<<< orphan*/  CPMAC_MAC_ADDR_MID ; 
 int /*<<< orphan*/  CPMAC_MAC_CONTROL ; 
 int /*<<< orphan*/  CPMAC_MAC_INT_CLEAR ; 
 int /*<<< orphan*/  CPMAC_MAC_INT_ENABLE ; 
 int /*<<< orphan*/  CPMAC_MAX_LENGTH ; 
 int /*<<< orphan*/  CPMAC_MBP ; 
 int /*<<< orphan*/  CPMAC_RX_CONTROL ; 
 int /*<<< orphan*/  CPMAC_RX_INT_CLEAR ; 
 int /*<<< orphan*/  CPMAC_RX_INT_ENABLE ; 
 int /*<<< orphan*/  CPMAC_RX_PTR (int) ; 
 int CPMAC_SKB_SIZE ; 
 int /*<<< orphan*/  CPMAC_TX_CONTROL ; 
 int /*<<< orphan*/  CPMAC_TX_INT_CLEAR ; 
 int /*<<< orphan*/  CPMAC_TX_INT_ENABLE ; 
 int /*<<< orphan*/  CPMAC_TX_PTR (int) ; 
 int /*<<< orphan*/  CPMAC_UNICAST_CLEAR ; 
 int /*<<< orphan*/  CPMAC_UNICAST_ENABLE ; 
 int MAC_FDX ; 
 int MAC_MII ; 
 int MBP_RXBCAST ; 
 int MBP_RXMCAST ; 
 int MBP_RXSHORT ; 
 int /*<<< orphan*/  ar7_device_reset (int /*<<< orphan*/ ) ; 
 int cpmac_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpmac_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct cpmac_priv* netdev_priv (struct net_device*) ; 

__attribute__((used)) static void cpmac_hw_start(struct net_device *dev)
{
	int i;
	struct cpmac_priv *priv = netdev_priv(dev);
	struct plat_cpmac_data *pdata = priv->pdev->dev.platform_data;

	ar7_device_reset(pdata->reset_bit);
	for (i = 0; i < 8; i++) {
		cpmac_write(priv->regs, CPMAC_TX_PTR(i), 0);
		cpmac_write(priv->regs, CPMAC_RX_PTR(i), 0);
	}
	cpmac_write(priv->regs, CPMAC_RX_PTR(0), priv->rx_head->mapping);

	cpmac_write(priv->regs, CPMAC_MBP, MBP_RXSHORT | MBP_RXBCAST |
		    MBP_RXMCAST);
	cpmac_write(priv->regs, CPMAC_BUFFER_OFFSET, 0);
	for (i = 0; i < 8; i++)
		cpmac_write(priv->regs, CPMAC_MAC_ADDR_LO(i), dev->dev_addr[5]);
	cpmac_write(priv->regs, CPMAC_MAC_ADDR_MID, dev->dev_addr[4]);
	cpmac_write(priv->regs, CPMAC_MAC_ADDR_HI, dev->dev_addr[0] |
		    (dev->dev_addr[1] << 8) | (dev->dev_addr[2] << 16) |
		    (dev->dev_addr[3] << 24));
	cpmac_write(priv->regs, CPMAC_MAX_LENGTH, CPMAC_SKB_SIZE);
	cpmac_write(priv->regs, CPMAC_UNICAST_CLEAR, 0xff);
	cpmac_write(priv->regs, CPMAC_RX_INT_CLEAR, 0xff);
	cpmac_write(priv->regs, CPMAC_TX_INT_CLEAR, 0xff);
	cpmac_write(priv->regs, CPMAC_MAC_INT_CLEAR, 0xff);
	cpmac_write(priv->regs, CPMAC_UNICAST_ENABLE, 1);
	cpmac_write(priv->regs, CPMAC_RX_INT_ENABLE, 1);
	cpmac_write(priv->regs, CPMAC_TX_INT_ENABLE, 0xff);
	cpmac_write(priv->regs, CPMAC_MAC_INT_ENABLE, 3);

	cpmac_write(priv->regs, CPMAC_RX_CONTROL,
		    cpmac_read(priv->regs, CPMAC_RX_CONTROL) | 1);
	cpmac_write(priv->regs, CPMAC_TX_CONTROL,
		    cpmac_read(priv->regs, CPMAC_TX_CONTROL) | 1);
	cpmac_write(priv->regs, CPMAC_MAC_CONTROL,
		    cpmac_read(priv->regs, CPMAC_MAC_CONTROL) | MAC_MII |
		    MAC_FDX);
}