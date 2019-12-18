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
struct sockaddr {int /*<<< orphan*/  sa_data; } ;
struct sky2_port {unsigned int port; struct sky2_hw* hw; } ;
struct sky2_hw {scalar_t__ regs; } ;
struct net_device {int /*<<< orphan*/  dev_addr; } ;

/* Variables and functions */
 scalar_t__ B2_MAC_1 ; 
 scalar_t__ B2_MAC_2 ; 
 int EADDRNOTAVAIL ; 
 int /*<<< orphan*/  ETH_ALEN ; 
 int /*<<< orphan*/  GM_SRC_ADDR_1L ; 
 int /*<<< orphan*/  GM_SRC_ADDR_2L ; 
 int /*<<< orphan*/  gma_set_addr (struct sky2_hw*,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  is_valid_ether_addr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy_toio (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct sky2_port* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int sky2_set_mac_address(struct net_device *dev, void *p)
{
	struct sky2_port *sky2 = netdev_priv(dev);
	struct sky2_hw *hw = sky2->hw;
	unsigned port = sky2->port;
	const struct sockaddr *addr = p;

	if (!is_valid_ether_addr(addr->sa_data))
		return -EADDRNOTAVAIL;

	memcpy(dev->dev_addr, addr->sa_data, ETH_ALEN);
	memcpy_toio(hw->regs + B2_MAC_1 + port * 8,
		    dev->dev_addr, ETH_ALEN);
	memcpy_toio(hw->regs + B2_MAC_2 + port * 8,
		    dev->dev_addr, ETH_ALEN);

	/* virtual address for data */
	gma_set_addr(hw, port, GM_SRC_ADDR_2L, dev->dev_addr);

	/* physical address: used for pause frames */
	gma_set_addr(hw, port, GM_SRC_ADDR_1L, dev->dev_addr);

	return 0;
}