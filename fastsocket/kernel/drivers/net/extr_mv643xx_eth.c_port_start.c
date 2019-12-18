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
typedef  int u32 ;
struct tx_queue {int dummy; } ;
struct rx_queue {int rx_curr_desc; scalar_t__ rx_desc_dma; } ;
struct rx_desc {int dummy; } ;
struct mv643xx_eth_private {int txq_count; int rxq_count; struct rx_queue* rxq; int /*<<< orphan*/  dev; struct tx_queue* txq; int /*<<< orphan*/ * phy; } ;
struct ethtool_cmd {int dummy; } ;

/* Variables and functions */
 int DO_NOT_FORCE_LINK_FAIL ; 
 int FORCE_LINK_PASS ; 
 int /*<<< orphan*/  PORT_CONFIG ; 
 int /*<<< orphan*/  PORT_CONFIG_EXT ; 
 int /*<<< orphan*/  PORT_SERIAL_CONTROL ; 
 int /*<<< orphan*/  RXQ_CURRENT_DESC_PTR (int) ; 
 int SERIAL_PORT_ENABLE ; 
 int /*<<< orphan*/  mv643xx_eth_get_settings (int /*<<< orphan*/ ,struct ethtool_cmd*) ; 
 int /*<<< orphan*/  mv643xx_eth_program_unicast_filter (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mv643xx_eth_set_settings (int /*<<< orphan*/ ,struct ethtool_cmd*) ; 
 int /*<<< orphan*/  phy_reset (struct mv643xx_eth_private*) ; 
 int rdlp (struct mv643xx_eth_private*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rxq_enable (struct rx_queue*) ; 
 int /*<<< orphan*/  tx_set_rate (struct mv643xx_eth_private*,int,int) ; 
 int /*<<< orphan*/  txq_reset_hw_ptr (struct tx_queue*) ; 
 int /*<<< orphan*/  txq_set_fixed_prio_mode (struct tx_queue*) ; 
 int /*<<< orphan*/  txq_set_rate (struct tx_queue*,int,int) ; 
 int /*<<< orphan*/  wrlp (struct mv643xx_eth_private*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void port_start(struct mv643xx_eth_private *mp)
{
	u32 pscr;
	int i;

	/*
	 * Perform PHY reset, if there is a PHY.
	 */
	if (mp->phy != NULL) {
		struct ethtool_cmd cmd;

		mv643xx_eth_get_settings(mp->dev, &cmd);
		phy_reset(mp);
		mv643xx_eth_set_settings(mp->dev, &cmd);
	}

	/*
	 * Configure basic link parameters.
	 */
	pscr = rdlp(mp, PORT_SERIAL_CONTROL);

	pscr |= SERIAL_PORT_ENABLE;
	wrlp(mp, PORT_SERIAL_CONTROL, pscr);

	pscr |= DO_NOT_FORCE_LINK_FAIL;
	if (mp->phy == NULL)
		pscr |= FORCE_LINK_PASS;
	wrlp(mp, PORT_SERIAL_CONTROL, pscr);

	/*
	 * Configure TX path and queues.
	 */
	tx_set_rate(mp, 1000000000, 16777216);
	for (i = 0; i < mp->txq_count; i++) {
		struct tx_queue *txq = mp->txq + i;

		txq_reset_hw_ptr(txq);
		txq_set_rate(txq, 1000000000, 16777216);
		txq_set_fixed_prio_mode(txq);
	}

	/*
	 * Receive all unmatched unicast, TCP, UDP, BPDU and broadcast
	 * frames to RX queue #0, and include the pseudo-header when
	 * calculating receive checksums.
	 */
	wrlp(mp, PORT_CONFIG, 0x02000000);

	/*
	 * Treat BPDUs as normal multicasts, and disable partition mode.
	 */
	wrlp(mp, PORT_CONFIG_EXT, 0x00000000);

	/*
	 * Add configured unicast addresses to address filter table.
	 */
	mv643xx_eth_program_unicast_filter(mp->dev);

	/*
	 * Enable the receive queues.
	 */
	for (i = 0; i < mp->rxq_count; i++) {
		struct rx_queue *rxq = mp->rxq + i;
		u32 addr;

		addr = (u32)rxq->rx_desc_dma;
		addr += rxq->rx_curr_desc * sizeof(struct rx_desc);
		wrlp(mp, RXQ_CURRENT_DESC_PTR(i), addr);

		rxq_enable(rxq);
	}
}