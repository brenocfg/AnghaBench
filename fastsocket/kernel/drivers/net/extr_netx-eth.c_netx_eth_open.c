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
struct netx_eth_priv {int /*<<< orphan*/  mii; scalar_t__ xpec_base; } ;
struct net_device {int* dev_addr; int /*<<< orphan*/  name; int /*<<< orphan*/  irq; } ;

/* Variables and functions */
 int EAGAIN ; 
 scalar_t__ ETH_MAC_4321 ; 
 scalar_t__ ETH_MAC_65 ; 
 scalar_t__ ETH_MAC_LOCAL_CONFIG ; 
 int /*<<< orphan*/  IRQF_SHARED ; 
 int LOCAL_CONFIG_CON_HI_IRQ_EN ; 
 int LOCAL_CONFIG_CON_LO_IRQ_EN ; 
 int LOCAL_CONFIG_IND_HI_IRQ_EN ; 
 int LOCAL_CONFIG_IND_LO_IRQ_EN ; 
 int LOCAL_CONFIG_LINK_STATUS_IRQ_EN ; 
 scalar_t__ NETX_XPEC_RAM_START_OFS ; 
 int /*<<< orphan*/  mii_check_media (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 struct netx_eth_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_msg_link (struct netx_eth_priv*) ; 
 int /*<<< orphan*/  netif_start_queue (struct net_device*) ; 
 int /*<<< orphan*/  netx_eth_interrupt ; 
 scalar_t__ request_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct net_device*) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static int netx_eth_open(struct net_device *ndev)
{
	struct netx_eth_priv *priv = netdev_priv(ndev);

	if (request_irq
	    (ndev->irq, &netx_eth_interrupt, IRQF_SHARED, ndev->name, ndev))
		return -EAGAIN;

	writel(ndev->dev_addr[0] |
	       ndev->dev_addr[1]<<8 |
	       ndev->dev_addr[2]<<16 |
	       ndev->dev_addr[3]<<24,
	       priv->xpec_base + NETX_XPEC_RAM_START_OFS + ETH_MAC_4321);
	writel(ndev->dev_addr[4] |
	       ndev->dev_addr[5]<<8,
	       priv->xpec_base + NETX_XPEC_RAM_START_OFS + ETH_MAC_65);

	writel(LOCAL_CONFIG_LINK_STATUS_IRQ_EN |
		LOCAL_CONFIG_CON_LO_IRQ_EN |
		LOCAL_CONFIG_CON_HI_IRQ_EN |
		LOCAL_CONFIG_IND_LO_IRQ_EN |
		LOCAL_CONFIG_IND_HI_IRQ_EN,
		priv->xpec_base + NETX_XPEC_RAM_START_OFS +
		ETH_MAC_LOCAL_CONFIG);

	mii_check_media(&priv->mii, netif_msg_link(priv), 1);
	netif_start_queue(ndev);

	return 0;
}