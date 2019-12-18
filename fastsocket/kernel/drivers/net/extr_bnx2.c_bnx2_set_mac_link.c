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
struct bnx2 {int line_speed; scalar_t__ duplex; int rx_mode; int flow_ctrl; scalar_t__ link_up; } ;

/* Variables and functions */
 int /*<<< orphan*/  BNX2_CHIP (struct bnx2*) ; 
 int /*<<< orphan*/  BNX2_CHIP_5706 ; 
 int /*<<< orphan*/  BNX2_EMAC_MODE ; 
 int BNX2_EMAC_MODE_25G_MODE ; 
 int BNX2_EMAC_MODE_FORCE_LINK ; 
 int BNX2_EMAC_MODE_HALF_DUPLEX ; 
 int BNX2_EMAC_MODE_MAC_LOOP ; 
 int BNX2_EMAC_MODE_PORT ; 
 int BNX2_EMAC_MODE_PORT_GMII ; 
 int BNX2_EMAC_MODE_PORT_MII ; 
 int BNX2_EMAC_MODE_PORT_MII_10M ; 
 int /*<<< orphan*/  BNX2_EMAC_RX_MODE ; 
 int BNX2_EMAC_RX_MODE_FLOW_EN ; 
 int /*<<< orphan*/  BNX2_EMAC_STATUS ; 
 int BNX2_EMAC_STATUS_LINK_CHANGE ; 
 int /*<<< orphan*/  BNX2_EMAC_TX_LENGTHS ; 
 int /*<<< orphan*/  BNX2_EMAC_TX_MODE ; 
 int BNX2_EMAC_TX_MODE_FLOW_EN ; 
 int BNX2_RD (struct bnx2*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BNX2_WR (struct bnx2*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ DUPLEX_HALF ; 
 int FLOW_CTRL_RX ; 
 int FLOW_CTRL_TX ; 
#define  SPEED_10 131 
#define  SPEED_100 130 
#define  SPEED_1000 129 
#define  SPEED_2500 128 
 int /*<<< orphan*/  bnx2_init_all_rx_contexts (struct bnx2*) ; 

__attribute__((used)) static void
bnx2_set_mac_link(struct bnx2 *bp)
{
	u32 val;

	BNX2_WR(bp, BNX2_EMAC_TX_LENGTHS, 0x2620);
	if (bp->link_up && (bp->line_speed == SPEED_1000) &&
		(bp->duplex == DUPLEX_HALF)) {
		BNX2_WR(bp, BNX2_EMAC_TX_LENGTHS, 0x26ff);
	}

	/* Configure the EMAC mode register. */
	val = BNX2_RD(bp, BNX2_EMAC_MODE);

	val &= ~(BNX2_EMAC_MODE_PORT | BNX2_EMAC_MODE_HALF_DUPLEX |
		BNX2_EMAC_MODE_MAC_LOOP | BNX2_EMAC_MODE_FORCE_LINK |
		BNX2_EMAC_MODE_25G_MODE);

	if (bp->link_up) {
		switch (bp->line_speed) {
			case SPEED_10:
				if (BNX2_CHIP(bp) != BNX2_CHIP_5706) {
					val |= BNX2_EMAC_MODE_PORT_MII_10M;
					break;
				}
				/* fall through */
			case SPEED_100:
				val |= BNX2_EMAC_MODE_PORT_MII;
				break;
			case SPEED_2500:
				val |= BNX2_EMAC_MODE_25G_MODE;
				/* fall through */
			case SPEED_1000:
				val |= BNX2_EMAC_MODE_PORT_GMII;
				break;
		}
	}
	else {
		val |= BNX2_EMAC_MODE_PORT_GMII;
	}

	/* Set the MAC to operate in the appropriate duplex mode. */
	if (bp->duplex == DUPLEX_HALF)
		val |= BNX2_EMAC_MODE_HALF_DUPLEX;
	BNX2_WR(bp, BNX2_EMAC_MODE, val);

	/* Enable/disable rx PAUSE. */
	bp->rx_mode &= ~BNX2_EMAC_RX_MODE_FLOW_EN;

	if (bp->flow_ctrl & FLOW_CTRL_RX)
		bp->rx_mode |= BNX2_EMAC_RX_MODE_FLOW_EN;
	BNX2_WR(bp, BNX2_EMAC_RX_MODE, bp->rx_mode);

	/* Enable/disable tx PAUSE. */
	val = BNX2_RD(bp, BNX2_EMAC_TX_MODE);
	val &= ~BNX2_EMAC_TX_MODE_FLOW_EN;

	if (bp->flow_ctrl & FLOW_CTRL_TX)
		val |= BNX2_EMAC_TX_MODE_FLOW_EN;
	BNX2_WR(bp, BNX2_EMAC_TX_MODE, val);

	/* Acknowledge the interrupt. */
	BNX2_WR(bp, BNX2_EMAC_STATUS, BNX2_EMAC_STATUS_LINK_CHANGE);

	bnx2_init_all_rx_contexts(bp);
}