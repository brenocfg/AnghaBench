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
struct dmfe_board_info {int cr6_data; scalar_t__ wait_reset; scalar_t__ rx_avail_cnt; scalar_t__ tx_queue_cnt; scalar_t__ tx_packet_cnt; } ;
struct DEVICE {scalar_t__ base_addr; } ;

/* Variables and functions */
 int CR6_RXSC ; 
 int CR6_TXSC ; 
 scalar_t__ DCR5 ; 
 scalar_t__ DCR7 ; 
 int /*<<< orphan*/  DMFE_DBUG (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dmfe_free_rxbuffer (struct dmfe_board_info*) ; 
 int /*<<< orphan*/  dmfe_init_dm910x (struct DEVICE*) ; 
 int /*<<< orphan*/  inl (scalar_t__) ; 
 struct dmfe_board_info* netdev_priv (struct DEVICE*) ; 
 int /*<<< orphan*/  netif_carrier_off (struct DEVICE*) ; 
 int /*<<< orphan*/  netif_stop_queue (struct DEVICE*) ; 
 int /*<<< orphan*/  netif_wake_queue (struct DEVICE*) ; 
 int /*<<< orphan*/  outl (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  update_cr6 (int,scalar_t__) ; 

__attribute__((used)) static void dmfe_dynamic_reset(struct DEVICE *dev)
{
	struct dmfe_board_info *db = netdev_priv(dev);

	DMFE_DBUG(0, "dmfe_dynamic_reset()", 0);

	/* Sopt MAC controller */
	db->cr6_data &= ~(CR6_RXSC | CR6_TXSC);	/* Disable Tx/Rx */
	update_cr6(db->cr6_data, dev->base_addr);
	outl(0, dev->base_addr + DCR7);		/* Disable Interrupt */
	outl(inl(dev->base_addr + DCR5), dev->base_addr + DCR5);

	/* Disable upper layer interface */
	netif_stop_queue(dev);

	/* Free Rx Allocate buffer */
	dmfe_free_rxbuffer(db);

	/* system variable init */
	db->tx_packet_cnt = 0;
	db->tx_queue_cnt = 0;
	db->rx_avail_cnt = 0;
	netif_carrier_off(dev);
	db->wait_reset = 0;

	/* Re-initilize DM910X board */
	dmfe_init_dm910x(dev);

	/* Restart upper layer interface */
	netif_wake_queue(dev);
}