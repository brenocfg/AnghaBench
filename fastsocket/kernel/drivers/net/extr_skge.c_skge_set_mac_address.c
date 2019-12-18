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
typedef  int u16 ;
struct sockaddr {int /*<<< orphan*/  sa_data; } ;
struct skge_port {unsigned int port; struct skge_hw* hw; } ;
struct skge_hw {scalar_t__ chip_id; int /*<<< orphan*/  phy_lock; scalar_t__ regs; } ;
struct net_device {int /*<<< orphan*/  dev_addr; } ;

/* Variables and functions */
 scalar_t__ B2_MAC_1 ; 
 scalar_t__ B2_MAC_2 ; 
 scalar_t__ CHIP_ID_GENESIS ; 
 int EADDRNOTAVAIL ; 
 int /*<<< orphan*/  ETH_ALEN ; 
 int GM_GPCR_RX_ENA ; 
 int /*<<< orphan*/  GM_GP_CTRL ; 
 int /*<<< orphan*/  GM_SRC_ADDR_1L ; 
 int /*<<< orphan*/  GM_SRC_ADDR_2L ; 
 int /*<<< orphan*/  XM_SA ; 
 int gma_read16 (struct skge_hw*,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gma_set_addr (struct skge_hw*,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gma_write16 (struct skge_hw*,unsigned int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  is_valid_ether_addr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy_toio (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct skge_port* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_running (struct net_device*) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xm_outaddr (struct skge_hw*,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int skge_set_mac_address(struct net_device *dev, void *p)
{
	struct skge_port *skge = netdev_priv(dev);
	struct skge_hw *hw = skge->hw;
	unsigned port = skge->port;
	const struct sockaddr *addr = p;
	u16 ctrl;

	if (!is_valid_ether_addr(addr->sa_data))
		return -EADDRNOTAVAIL;

	memcpy(dev->dev_addr, addr->sa_data, ETH_ALEN);

	if (!netif_running(dev)) {
		memcpy_toio(hw->regs + B2_MAC_1 + port*8, dev->dev_addr, ETH_ALEN);
		memcpy_toio(hw->regs + B2_MAC_2 + port*8, dev->dev_addr, ETH_ALEN);
	} else {
		/* disable Rx */
		spin_lock_bh(&hw->phy_lock);
		ctrl = gma_read16(hw, port, GM_GP_CTRL);
		gma_write16(hw, port, GM_GP_CTRL, ctrl & ~GM_GPCR_RX_ENA);

		memcpy_toio(hw->regs + B2_MAC_1 + port*8, dev->dev_addr, ETH_ALEN);
		memcpy_toio(hw->regs + B2_MAC_2 + port*8, dev->dev_addr, ETH_ALEN);

		if (hw->chip_id == CHIP_ID_GENESIS)
			xm_outaddr(hw, port, XM_SA, dev->dev_addr);
		else {
			gma_set_addr(hw, port, GM_SRC_ADDR_1L, dev->dev_addr);
			gma_set_addr(hw, port, GM_SRC_ADDR_2L, dev->dev_addr);
		}

		gma_write16(hw, port, GM_GP_CTRL, ctrl);
		spin_unlock_bh(&hw->phy_lock);
	}

	return 0;
}