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
typedef  scalar_t__ u8 ;
typedef  int u16 ;
struct skge_port {int port; scalar_t__ flow_status; struct skge_hw* hw; } ;
struct skge_hw {int dummy; } ;
struct net_device {int flags; scalar_t__ mc_count; struct dev_mc_list* mc_list; } ;
struct dev_mc_list {int /*<<< orphan*/  dmi_addr; struct dev_mc_list* next; } ;
typedef  int /*<<< orphan*/  filter ;

/* Variables and functions */
 scalar_t__ FLOW_STAT_REM_SEND ; 
 scalar_t__ FLOW_STAT_SYMMETRIC ; 
 int /*<<< orphan*/  GM_MC_ADDR_H1 ; 
 int /*<<< orphan*/  GM_MC_ADDR_H2 ; 
 int /*<<< orphan*/  GM_MC_ADDR_H3 ; 
 int /*<<< orphan*/  GM_MC_ADDR_H4 ; 
 int GM_RXCR_MCF_ENA ; 
 int GM_RXCR_UCF_ENA ; 
 int /*<<< orphan*/  GM_RX_CTRL ; 
 int IFF_ALLMULTI ; 
 int IFF_PROMISC ; 
 int gma_read16 (struct skge_hw*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gma_write16 (struct skge_hw*,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memset (scalar_t__*,int,int) ; 
 struct skge_port* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  pause_mc_addr ; 
 int /*<<< orphan*/  yukon_add_filter (scalar_t__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void yukon_set_multicast(struct net_device *dev)
{
	struct skge_port *skge = netdev_priv(dev);
	struct skge_hw *hw = skge->hw;
	int port = skge->port;
	struct dev_mc_list *list = dev->mc_list;
	int rx_pause = (skge->flow_status == FLOW_STAT_REM_SEND
			|| skge->flow_status == FLOW_STAT_SYMMETRIC);
	u16 reg;
	u8 filter[8];

	memset(filter, 0, sizeof(filter));

	reg = gma_read16(hw, port, GM_RX_CTRL);
	reg |= GM_RXCR_UCF_ENA;

	if (dev->flags & IFF_PROMISC) 		/* promiscuous */
		reg &= ~(GM_RXCR_UCF_ENA | GM_RXCR_MCF_ENA);
	else if (dev->flags & IFF_ALLMULTI)	/* all multicast */
		memset(filter, 0xff, sizeof(filter));
	else if (dev->mc_count == 0 && !rx_pause)/* no multicast */
		reg &= ~GM_RXCR_MCF_ENA;
	else {
		int i;
		reg |= GM_RXCR_MCF_ENA;

		if (rx_pause)
			yukon_add_filter(filter, pause_mc_addr);

		for (i = 0; list && i < dev->mc_count; i++, list = list->next)
			yukon_add_filter(filter, list->dmi_addr);
	}


	gma_write16(hw, port, GM_MC_ADDR_H1,
			 (u16)filter[0] | ((u16)filter[1] << 8));
	gma_write16(hw, port, GM_MC_ADDR_H2,
			 (u16)filter[2] | ((u16)filter[3] << 8));
	gma_write16(hw, port, GM_MC_ADDR_H3,
			 (u16)filter[4] | ((u16)filter[5] << 8));
	gma_write16(hw, port, GM_MC_ADDR_H4,
			 (u16)filter[6] | ((u16)filter[7] << 8));

	gma_write16(hw, port, GM_RX_CTRL, reg);
}