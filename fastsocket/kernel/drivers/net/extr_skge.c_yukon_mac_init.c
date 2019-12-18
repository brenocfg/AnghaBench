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
struct skge_port {scalar_t__ autoneg; int speed; scalar_t__ duplex; int flow_control; } ;
struct skge_hw {scalar_t__ chip_id; scalar_t__ chip_rev; TYPE_1__** dev; scalar_t__ copper; } ;
struct TYPE_2__ {scalar_t__ mtu; int /*<<< orphan*/ * dev_addr; } ;

/* Variables and functions */
 scalar_t__ AUTONEG_DISABLE ; 
 int /*<<< orphan*/  B2_GP_IO ; 
 scalar_t__ CHIP_ID_YUKON_LITE ; 
 scalar_t__ CHIP_REV_YU_LITE_A3 ; 
 int /*<<< orphan*/  DATA_BLIND_DEF ; 
 int DATA_BLIND_VAL (int /*<<< orphan*/ ) ; 
 scalar_t__ DUPLEX_FULL ; 
 scalar_t__ ETH_DATA_LEN ; 
#define  FLOW_MODE_LOC_SEND 134 
#define  FLOW_MODE_NONE 133 
#define  FLOW_MODE_SYMMETRIC 132 
#define  FLOW_MODE_SYM_OR_REM 131 
 int /*<<< orphan*/  GMAC_CTRL ; 
 int /*<<< orphan*/  GMAC_IRQ_SRC ; 
 int GMC_PAUSE_OFF ; 
 int GMC_PAUSE_ON ; 
 int GMC_RST_CLR ; 
 int GMC_RST_SET ; 
 int GMF_OPER_ON ; 
 int /*<<< orphan*/  GMF_RST_CLR ; 
 int GMF_RX_F_FL_ON ; 
 int GM_GPCR_AU_ALL_DIS ; 
 int GM_GPCR_AU_FCT_DIS ; 
 int GM_GPCR_DUP_FULL ; 
 int GM_GPCR_FC_RX_DIS ; 
 int GM_GPCR_FC_TX_DIS ; 
 int GM_GPCR_SPEED_100 ; 
 int GM_GPCR_SPEED_1000 ; 
 scalar_t__ GM_GP_CTRL ; 
 scalar_t__ GM_MIB_CNT_BASE ; 
 int GM_MIB_CNT_SIZE ; 
 int GM_PAR_MIB_CLR ; 
 scalar_t__ GM_PHY_ADDR ; 
 int GM_RXCR_CRC_DIS ; 
 int GM_RXCR_MCF_ENA ; 
 int GM_RXCR_UCF_ENA ; 
 scalar_t__ GM_RX_CTRL ; 
 scalar_t__ GM_RX_IRQ_MSK ; 
 scalar_t__ GM_SERIAL_MODE ; 
 int GM_SMOD_JUMBO_ENA ; 
 int GM_SMOD_VLAN_ENA ; 
 int /*<<< orphan*/  GM_SRC_ADDR_1L ; 
 int /*<<< orphan*/  GM_SRC_ADDR_2L ; 
 scalar_t__ GM_TR_IRQ_MSK ; 
 scalar_t__ GM_TX_CTRL ; 
 scalar_t__ GM_TX_FLOW_CTRL ; 
 scalar_t__ GM_TX_IRQ_MSK ; 
 scalar_t__ GM_TX_PARAM ; 
 int GPC_ANEG_ADV_ALL_M ; 
 int GPC_DIS_FC ; 
 int GPC_DIS_SLEEP ; 
 int GPC_ENA_PAUSE ; 
 int GPC_ENA_XC ; 
 int GPC_HWCFG_GMII_COP ; 
 int GPC_HWCFG_GMII_FIB ; 
 int GPC_INT_POL_HI ; 
 int GPC_RST_CLR ; 
 int GPC_RST_SET ; 
 int /*<<< orphan*/  GPHY_CTRL ; 
 int GP_DIR_9 ; 
 int GP_IO_9 ; 
 int /*<<< orphan*/  IPG_DATA_DEF ; 
 int IPG_DATA_VAL (int /*<<< orphan*/ ) ; 
 int RX_FF_FL_DEF_MSK ; 
 int /*<<< orphan*/  RX_GMF_CTRL_T ; 
 int /*<<< orphan*/  RX_GMF_FL_MSK ; 
 int /*<<< orphan*/  RX_GMF_FL_THR ; 
 int RX_GMF_FL_THR_DEF ; 
 int /*<<< orphan*/  SK_REG (int,int /*<<< orphan*/ ) ; 
#define  SPEED_10 130 
#define  SPEED_100 129 
#define  SPEED_1000 128 
 int /*<<< orphan*/  TX_COL_DEF ; 
 int TX_COL_THR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TX_GMF_CTRL_T ; 
 int TX_IPG_JAM_DATA (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TX_IPG_JAM_DEF ; 
 int /*<<< orphan*/  TX_JAM_IPG_DEF ; 
 int TX_JAM_IPG_VAL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TX_JAM_LEN_DEF ; 
 int TX_JAM_LEN_VAL (int /*<<< orphan*/ ) ; 
 int gma_read16 (struct skge_hw*,int,scalar_t__) ; 
 int /*<<< orphan*/  gma_set_addr (struct skge_hw*,int,int /*<<< orphan*/ ,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  gma_write16 (struct skge_hw*,int,scalar_t__,int) ; 
 scalar_t__ is_yukon_lite_a0 (struct skge_hw*) ; 
 struct skge_port* netdev_priv (TYPE_1__*) ; 
 int /*<<< orphan*/  skge_read16 (struct skge_hw*,int /*<<< orphan*/ ) ; 
 int skge_read32 (struct skge_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skge_write16 (struct skge_hw*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  skge_write32 (struct skge_hw*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  skge_write8 (struct skge_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  yukon_init (struct skge_hw*,int) ; 

__attribute__((used)) static void yukon_mac_init(struct skge_hw *hw, int port)
{
	struct skge_port *skge = netdev_priv(hw->dev[port]);
	int i;
	u32 reg;
	const u8 *addr = hw->dev[port]->dev_addr;

	/* WA code for COMA mode -- set PHY reset */
	if (hw->chip_id == CHIP_ID_YUKON_LITE &&
	    hw->chip_rev >= CHIP_REV_YU_LITE_A3) {
		reg = skge_read32(hw, B2_GP_IO);
		reg |= GP_DIR_9 | GP_IO_9;
		skge_write32(hw, B2_GP_IO, reg);
	}

	/* hard reset */
	skge_write32(hw, SK_REG(port, GPHY_CTRL), GPC_RST_SET);
	skge_write32(hw, SK_REG(port, GMAC_CTRL), GMC_RST_SET);

	/* WA code for COMA mode -- clear PHY reset */
	if (hw->chip_id == CHIP_ID_YUKON_LITE &&
	    hw->chip_rev >= CHIP_REV_YU_LITE_A3) {
		reg = skge_read32(hw, B2_GP_IO);
		reg |= GP_DIR_9;
		reg &= ~GP_IO_9;
		skge_write32(hw, B2_GP_IO, reg);
	}

	/* Set hardware config mode */
	reg = GPC_INT_POL_HI | GPC_DIS_FC | GPC_DIS_SLEEP |
		GPC_ENA_XC | GPC_ANEG_ADV_ALL_M | GPC_ENA_PAUSE;
	reg |= hw->copper ? GPC_HWCFG_GMII_COP : GPC_HWCFG_GMII_FIB;

	/* Clear GMC reset */
	skge_write32(hw, SK_REG(port, GPHY_CTRL), reg | GPC_RST_SET);
	skge_write32(hw, SK_REG(port, GPHY_CTRL), reg | GPC_RST_CLR);
	skge_write32(hw, SK_REG(port, GMAC_CTRL), GMC_PAUSE_ON | GMC_RST_CLR);

	if (skge->autoneg == AUTONEG_DISABLE) {
		reg = GM_GPCR_AU_ALL_DIS;
		gma_write16(hw, port, GM_GP_CTRL,
				 gma_read16(hw, port, GM_GP_CTRL) | reg);

		switch (skge->speed) {
		case SPEED_1000:
			reg &= ~GM_GPCR_SPEED_100;
			reg |= GM_GPCR_SPEED_1000;
			break;
		case SPEED_100:
			reg &= ~GM_GPCR_SPEED_1000;
			reg |= GM_GPCR_SPEED_100;
			break;
		case SPEED_10:
			reg &= ~(GM_GPCR_SPEED_1000 | GM_GPCR_SPEED_100);
			break;
		}

		if (skge->duplex == DUPLEX_FULL)
			reg |= GM_GPCR_DUP_FULL;
	} else
		reg = GM_GPCR_SPEED_1000 | GM_GPCR_SPEED_100 | GM_GPCR_DUP_FULL;

	switch (skge->flow_control) {
	case FLOW_MODE_NONE:
		skge_write32(hw, SK_REG(port, GMAC_CTRL), GMC_PAUSE_OFF);
		reg |= GM_GPCR_FC_TX_DIS | GM_GPCR_FC_RX_DIS | GM_GPCR_AU_FCT_DIS;
		break;
	case FLOW_MODE_LOC_SEND:
		/* disable Rx flow-control */
		reg |= GM_GPCR_FC_RX_DIS | GM_GPCR_AU_FCT_DIS;
		break;
	case FLOW_MODE_SYMMETRIC:
	case FLOW_MODE_SYM_OR_REM:
		/* enable Tx & Rx flow-control */
		break;
	}

	gma_write16(hw, port, GM_GP_CTRL, reg);
	skge_read16(hw, SK_REG(port, GMAC_IRQ_SRC));

	yukon_init(hw, port);

	/* MIB clear */
	reg = gma_read16(hw, port, GM_PHY_ADDR);
	gma_write16(hw, port, GM_PHY_ADDR, reg | GM_PAR_MIB_CLR);

	for (i = 0; i < GM_MIB_CNT_SIZE; i++)
		gma_read16(hw, port, GM_MIB_CNT_BASE + 8*i);
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
			 TX_IPG_JAM_DATA(TX_IPG_JAM_DEF));

	/* configure the Serial Mode Register */
	reg = DATA_BLIND_VAL(DATA_BLIND_DEF)
		| GM_SMOD_VLAN_ENA
		| IPG_DATA_VAL(IPG_DATA_DEF);

	if (hw->dev[port]->mtu > ETH_DATA_LEN)
		reg |= GM_SMOD_JUMBO_ENA;

	gma_write16(hw, port, GM_SERIAL_MODE, reg);

	/* physical address: used for pause frames */
	gma_set_addr(hw, port, GM_SRC_ADDR_1L, addr);
	/* virtual address for data */
	gma_set_addr(hw, port, GM_SRC_ADDR_2L, addr);

	/* enable interrupt mask for counter overflows */
	gma_write16(hw, port, GM_TX_IRQ_MSK, 0);
	gma_write16(hw, port, GM_RX_IRQ_MSK, 0);
	gma_write16(hw, port, GM_TR_IRQ_MSK, 0);

	/* Initialize Mac Fifo */

	/* Configure Rx MAC FIFO */
	skge_write16(hw, SK_REG(port, RX_GMF_FL_MSK), RX_FF_FL_DEF_MSK);
	reg = GMF_OPER_ON | GMF_RX_F_FL_ON;

	/* disable Rx GMAC FIFO Flush for YUKON-Lite Rev. A0 only */
	if (is_yukon_lite_a0(hw))
		reg &= ~GMF_RX_F_FL_ON;

	skge_write8(hw, SK_REG(port, RX_GMF_CTRL_T), GMF_RST_CLR);
	skge_write16(hw, SK_REG(port, RX_GMF_CTRL_T), reg);
	/*
	 * because Pause Packet Truncation in GMAC is not working
	 * we have to increase the Flush Threshold to 64 bytes
	 * in order to flush pause packets in Rx FIFO on Yukon-1
	 */
	skge_write16(hw, SK_REG(port, RX_GMF_FL_THR), RX_GMF_FL_THR_DEF+1);

	/* Configure Tx MAC FIFO */
	skge_write8(hw, SK_REG(port, TX_GMF_CTRL_T), GMF_RST_CLR);
	skge_write16(hw, SK_REG(port, TX_GMF_CTRL_T), GMF_OPER_ON);
}