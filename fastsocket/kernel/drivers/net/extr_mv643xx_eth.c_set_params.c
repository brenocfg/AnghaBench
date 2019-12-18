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
struct net_device {int /*<<< orphan*/  dev_addr; } ;
struct mv643xx_eth_private {int rxq_count; int txq_count; int /*<<< orphan*/  tx_desc_sram_size; int /*<<< orphan*/  tx_desc_sram_addr; scalar_t__ tx_ring_size; int /*<<< orphan*/  rx_desc_sram_size; int /*<<< orphan*/  rx_desc_sram_addr; scalar_t__ rx_ring_size; struct net_device* dev; } ;
struct mv643xx_eth_platform_data {scalar_t__ tx_queue_count; int /*<<< orphan*/  tx_sram_size; int /*<<< orphan*/  tx_sram_addr; scalar_t__ tx_queue_size; scalar_t__ rx_queue_count; int /*<<< orphan*/  rx_sram_size; int /*<<< orphan*/  rx_sram_addr; scalar_t__ rx_queue_size; int /*<<< orphan*/  mac_addr; } ;

/* Variables and functions */
 scalar_t__ DEFAULT_RX_QUEUE_SIZE ; 
 scalar_t__ DEFAULT_TX_QUEUE_SIZE ; 
 scalar_t__ is_valid_ether_addr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  uc_addr_get (struct mv643xx_eth_private*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void set_params(struct mv643xx_eth_private *mp,
		       struct mv643xx_eth_platform_data *pd)
{
	struct net_device *dev = mp->dev;

	if (is_valid_ether_addr(pd->mac_addr))
		memcpy(dev->dev_addr, pd->mac_addr, 6);
	else
		uc_addr_get(mp, dev->dev_addr);

	mp->rx_ring_size = DEFAULT_RX_QUEUE_SIZE;
	if (pd->rx_queue_size)
		mp->rx_ring_size = pd->rx_queue_size;
	mp->rx_desc_sram_addr = pd->rx_sram_addr;
	mp->rx_desc_sram_size = pd->rx_sram_size;

	mp->rxq_count = pd->rx_queue_count ? : 1;

	mp->tx_ring_size = DEFAULT_TX_QUEUE_SIZE;
	if (pd->tx_queue_size)
		mp->tx_ring_size = pd->tx_queue_size;
	mp->tx_desc_sram_addr = pd->tx_sram_addr;
	mp->tx_desc_sram_size = pd->tx_sram_size;

	mp->txq_count = pd->tx_queue_count ? : 1;
}