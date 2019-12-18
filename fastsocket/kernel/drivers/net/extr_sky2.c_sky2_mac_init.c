#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;
typedef  int u16 ;
struct sky2_port {int /*<<< orphan*/  phy_lock; } ;
struct sky2_hw {scalar_t__ chip_id; scalar_t__ chip_rev; int flags; TYPE_1__** dev; } ;
struct TYPE_2__ {scalar_t__ mtu; int /*<<< orphan*/ * dev_addr; } ;

/* Variables and functions */
 scalar_t__ CHIP_ID_YUKON_EX ; 
 scalar_t__ CHIP_ID_YUKON_FE_P ; 
 scalar_t__ CHIP_ID_YUKON_XL ; 
 scalar_t__ CHIP_REV_YU_FE2_A0 ; 
 int /*<<< orphan*/  DATA_BLIND_DEF ; 
 int DATA_BLIND_VAL (int /*<<< orphan*/ ) ; 
 scalar_t__ ETH_DATA_LEN ; 
 int /*<<< orphan*/  GMAC_CTRL ; 
 int GMAC_DEF_MSK ; 
 int /*<<< orphan*/  GMAC_IRQ_MSK ; 
 int /*<<< orphan*/  GMAC_IRQ_SRC ; 
 int GMC_RST_CLR ; 
 int GMC_RST_SET ; 
 int GMF_OPER_ON ; 
 int GMF_RST_CLR ; 
 int GMF_RX_F_FL_ON ; 
 int GMF_RX_OVER_ON ; 
 int GMR_FS_ANY_ERR ; 
 int GM_MIB_CNT_BASE ; 
 int GM_MIB_CNT_END ; 
 int GM_PAR_MIB_CLR ; 
 int GM_PHY_ADDR ; 
 int GM_RXCR_CRC_DIS ; 
 int GM_RXCR_MCF_ENA ; 
 int GM_RXCR_UCF_ENA ; 
 int GM_RX_CTRL ; 
 int GM_RX_IRQ_MSK ; 
 int GM_SERIAL_MODE ; 
 int GM_SMOD_JUMBO_ENA ; 
 int GM_SMOD_VLAN_ENA ; 
 int /*<<< orphan*/  GM_SRC_ADDR_1L ; 
 int /*<<< orphan*/  GM_SRC_ADDR_2L ; 
 int GM_TR_IRQ_MSK ; 
 int GM_TX_CTRL ; 
 int GM_TX_FLOW_CTRL ; 
 int GM_TX_IRQ_MSK ; 
 int GM_TX_PARAM ; 
 int GPC_RST_CLR ; 
 int GPC_RST_SET ; 
 int /*<<< orphan*/  GPHY_CTRL ; 
 int /*<<< orphan*/  IPG_DATA_DEF ; 
 int IPG_DATA_VAL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PHY_MARV_ID0 ; 
 scalar_t__ PHY_MARV_ID0_VAL ; 
 int /*<<< orphan*/  PHY_MARV_ID1 ; 
 scalar_t__ PHY_MARV_ID1_Y2 ; 
 int /*<<< orphan*/  PHY_MARV_INT_MASK ; 
 int /*<<< orphan*/  RX_GMF_CTRL_T ; 
 int /*<<< orphan*/  RX_GMF_FL_MSK ; 
 int /*<<< orphan*/  RX_GMF_FL_THR ; 
 int RX_GMF_FL_THR_DEF ; 
 int /*<<< orphan*/  RX_GMF_LP_THR ; 
 int /*<<< orphan*/  RX_GMF_UP_THR ; 
 int SKY2_HW_RAM_BUFFER ; 
 int /*<<< orphan*/  SK_REG (unsigned int,int /*<<< orphan*/ ) ; 
 int TX_BACK_OFF_LIM (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TX_BOF_LIM_DEF ; 
 int /*<<< orphan*/  TX_COL_DEF ; 
 int TX_COL_THR (int /*<<< orphan*/ ) ; 
 int TX_DYN_WM_ENA ; 
 int /*<<< orphan*/  TX_GMF_CTRL_T ; 
 int /*<<< orphan*/  TX_GMF_EA ; 
 int TX_IPG_JAM_DATA (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TX_IPG_JAM_DEF ; 
 int /*<<< orphan*/  TX_JAM_IPG_DEF ; 
 int TX_JAM_IPG_VAL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TX_JAM_LEN_DEF ; 
 int TX_JAM_LEN_VAL (int /*<<< orphan*/ ) ; 
 scalar_t__ gm_phy_read (struct sky2_hw*,int,int /*<<< orphan*/ ) ; 
 int gma_read16 (struct sky2_hw*,unsigned int,int) ; 
 int /*<<< orphan*/  gma_set_addr (struct sky2_hw*,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  gma_write16 (struct sky2_hw*,unsigned int,int,int) ; 
 struct sky2_port* netdev_priv (TYPE_1__*) ; 
 int /*<<< orphan*/  sky2_phy_init (struct sky2_hw*,unsigned int) ; 
 int /*<<< orphan*/  sky2_phy_power_up (struct sky2_hw*,unsigned int) ; 
 int sky2_read16 (struct sky2_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sky2_set_tx_stfwd (struct sky2_hw*,unsigned int) ; 
 int /*<<< orphan*/  sky2_write16 (struct sky2_hw*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sky2_write32 (struct sky2_hw*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sky2_write8 (struct sky2_hw*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void sky2_mac_init(struct sky2_hw *hw, unsigned port)
{
	struct sky2_port *sky2 = netdev_priv(hw->dev[port]);
	u16 reg;
	u32 rx_reg;
	int i;
	const u8 *addr = hw->dev[port]->dev_addr;

	sky2_write8(hw, SK_REG(port, GPHY_CTRL), GPC_RST_SET);
	sky2_write8(hw, SK_REG(port, GPHY_CTRL), GPC_RST_CLR);

	sky2_write8(hw, SK_REG(port, GMAC_CTRL), GMC_RST_CLR);

	if (hw->chip_id == CHIP_ID_YUKON_XL && hw->chip_rev == 0 && port == 1) {
		/* WA DEV_472 -- looks like crossed wires on port 2 */
		/* clear GMAC 1 Control reset */
		sky2_write8(hw, SK_REG(0, GMAC_CTRL), GMC_RST_CLR);
		do {
			sky2_write8(hw, SK_REG(1, GMAC_CTRL), GMC_RST_SET);
			sky2_write8(hw, SK_REG(1, GMAC_CTRL), GMC_RST_CLR);
		} while (gm_phy_read(hw, 1, PHY_MARV_ID0) != PHY_MARV_ID0_VAL ||
			 gm_phy_read(hw, 1, PHY_MARV_ID1) != PHY_MARV_ID1_Y2 ||
			 gm_phy_read(hw, 1, PHY_MARV_INT_MASK) != 0);
	}

	sky2_read16(hw, SK_REG(port, GMAC_IRQ_SRC));

	/* Enable Transmit FIFO Underrun */
	sky2_write8(hw, SK_REG(port, GMAC_IRQ_MSK), GMAC_DEF_MSK);

	spin_lock_bh(&sky2->phy_lock);
	sky2_phy_power_up(hw, port);
	sky2_phy_init(hw, port);
	spin_unlock_bh(&sky2->phy_lock);

	/* MIB clear */
	reg = gma_read16(hw, port, GM_PHY_ADDR);
	gma_write16(hw, port, GM_PHY_ADDR, reg | GM_PAR_MIB_CLR);

	for (i = GM_MIB_CNT_BASE; i <= GM_MIB_CNT_END; i += 4)
		gma_read16(hw, port, i);
	gma_write16(hw, port, GM_PHY_ADDR, reg);

	/* transmit control */
	gma_write16(hw, port, GM_TX_CTRL, TX_COL_THR(TX_COL_DEF));

	/* receive control reg: unicast + multicast + no FCS  */
	gma_write16(hw, port, GM_RX_CTRL,
		    GM_RXCR_UCF_ENA | GM_RXCR_CRC_DIS | GM_RXCR_MCF_ENA);

	/* transmit flow control */
	gma_write16(hw, port, GM_TX_FLOW_CTRL, 0xffff);

	/* transmit parameter */
	gma_write16(hw, port, GM_TX_PARAM,
		    TX_JAM_LEN_VAL(TX_JAM_LEN_DEF) |
		    TX_JAM_IPG_VAL(TX_JAM_IPG_DEF) |
		    TX_IPG_JAM_DATA(TX_IPG_JAM_DEF) |
		    TX_BACK_OFF_LIM(TX_BOF_LIM_DEF));

	/* serial mode register */
	reg = DATA_BLIND_VAL(DATA_BLIND_DEF) |
		GM_SMOD_VLAN_ENA | IPG_DATA_VAL(IPG_DATA_DEF);

	if (hw->dev[port]->mtu > ETH_DATA_LEN)
		reg |= GM_SMOD_JUMBO_ENA;

	gma_write16(hw, port, GM_SERIAL_MODE, reg);

	/* virtual address for data */
	gma_set_addr(hw, port, GM_SRC_ADDR_2L, addr);

	/* physical address: used for pause frames */
	gma_set_addr(hw, port, GM_SRC_ADDR_1L, addr);

	/* ignore counter overflows */
	gma_write16(hw, port, GM_TX_IRQ_MSK, 0);
	gma_write16(hw, port, GM_RX_IRQ_MSK, 0);
	gma_write16(hw, port, GM_TR_IRQ_MSK, 0);

	/* Configure Rx MAC FIFO */
	sky2_write8(hw, SK_REG(port, RX_GMF_CTRL_T), GMF_RST_CLR);
	rx_reg = GMF_OPER_ON | GMF_RX_F_FL_ON;
	if (hw->chip_id == CHIP_ID_YUKON_EX ||
	    hw->chip_id == CHIP_ID_YUKON_FE_P)
		rx_reg |= GMF_RX_OVER_ON;

	sky2_write32(hw, SK_REG(port, RX_GMF_CTRL_T), rx_reg);

	if (hw->chip_id == CHIP_ID_YUKON_XL) {
		/* Hardware errata - clear flush mask */
		sky2_write16(hw, SK_REG(port, RX_GMF_FL_MSK), 0);
	} else {
		/* Flush Rx MAC FIFO on any flow control or error */
		sky2_write16(hw, SK_REG(port, RX_GMF_FL_MSK), GMR_FS_ANY_ERR);
	}

	/* Set threshold to 0xa (64 bytes) + 1 to workaround pause bug  */
	reg = RX_GMF_FL_THR_DEF + 1;
	/* Another magic mystery workaround from sk98lin */
	if (hw->chip_id == CHIP_ID_YUKON_FE_P &&
	    hw->chip_rev == CHIP_REV_YU_FE2_A0)
		reg = 0x178;
	sky2_write16(hw, SK_REG(port, RX_GMF_FL_THR), reg);

	/* Configure Tx MAC FIFO */
	sky2_write8(hw, SK_REG(port, TX_GMF_CTRL_T), GMF_RST_CLR);
	sky2_write16(hw, SK_REG(port, TX_GMF_CTRL_T), GMF_OPER_ON);

	/* On chips without ram buffer, pause is controled by MAC level */
	if (!(hw->flags & SKY2_HW_RAM_BUFFER)) {
		sky2_write8(hw, SK_REG(port, RX_GMF_LP_THR), 768/8);
		sky2_write8(hw, SK_REG(port, RX_GMF_UP_THR), 1024/8);

		sky2_set_tx_stfwd(hw, port);
	}

	if (hw->chip_id == CHIP_ID_YUKON_FE_P &&
	    hw->chip_rev == CHIP_REV_YU_FE2_A0) {
		/* disable dynamic watermark */
		reg = sky2_read16(hw, SK_REG(port, TX_GMF_EA));
		reg &= ~TX_DYN_WM_ENA;
		sky2_write16(hw, SK_REG(port, TX_GMF_EA), reg);
	}
}