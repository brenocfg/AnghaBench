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
struct sky2_port {int flags; int advertising; int speed; scalar_t__ duplex; size_t flow_mode; } ;
struct sky2_hw {int flags; int chip_id; scalar_t__ chip_rev; char pmd_type; int /*<<< orphan*/ * dev; } ;

/* Variables and functions */
 int ADVERTISED_1000baseT_Full ; 
 int ADVERTISED_1000baseT_Half ; 
 int ADVERTISED_100baseT_Full ; 
 int ADVERTISED_100baseT_Half ; 
 int ADVERTISED_10baseT_Full ; 
 int ADVERTISED_10baseT_Half ; 
 int /*<<< orphan*/  BLINK_84MS ; 
 int CHIP_ID_YUKON_EC ; 
#define  CHIP_ID_YUKON_EC_U 135 
#define  CHIP_ID_YUKON_EX 134 
#define  CHIP_ID_YUKON_FE 133 
#define  CHIP_ID_YUKON_FE_P 132 
#define  CHIP_ID_YUKON_SUPR 131 
 int const CHIP_ID_YUKON_UL_2 ; 
#define  CHIP_ID_YUKON_XL 130 
 scalar_t__ CHIP_REV_YU_FE2_A0 ; 
 scalar_t__ DUPLEX_FULL ; 
 size_t FC_NONE ; 
 int FC_RX ; 
 int /*<<< orphan*/  GMAC_CTRL ; 
 int /*<<< orphan*/  GMC_PAUSE_OFF ; 
 int /*<<< orphan*/  GMC_PAUSE_ON ; 
 int GM_GPCR_AU_DUP_DIS ; 
 int GM_GPCR_AU_FCT_DIS ; 
 int GM_GPCR_AU_SPD_DIS ; 
 int GM_GPCR_DUP_FULL ; 
 int GM_GPCR_SPEED_100 ; 
 int GM_GPCR_SPEED_1000 ; 
 int /*<<< orphan*/  GM_GP_CTRL ; 
 int /*<<< orphan*/  LED_PAR_CTRL_ACT_BL ; 
 int /*<<< orphan*/  LED_PAR_CTRL_LINK ; 
 int /*<<< orphan*/  LED_PAR_CTRL_SPEED ; 
 int /*<<< orphan*/  MAC_TX_CLK_25_MHZ ; 
 int /*<<< orphan*/  MO_LED_OFF ; 
 int /*<<< orphan*/  MO_LED_ON ; 
 int PHY_AN_CSMA ; 
 int PHY_CT_ANE ; 
 int PHY_CT_DUP_MD ; 
 int PHY_CT_RESET ; 
 int PHY_CT_RE_CFG ; 
 int PHY_CT_SP100 ; 
 int PHY_CT_SP1000 ; 
 int PHY_MARV_1000T_CTRL ; 
 int PHY_MARV_AUNE_ADV ; 
 int PHY_MARV_CTRL ; 
 int PHY_MARV_EXT_ADR ; 
 int PHY_MARV_EXT_CTRL ; 
 int PHY_MARV_FE_LED_PAR ; 
 int PHY_MARV_FE_SPEC_2 ; 
 int PHY_MARV_INT_MASK ; 
 int PHY_MARV_LED_CTRL ; 
 int PHY_MARV_LED_OVER ; 
 int PHY_MARV_PAGE_ADDR ; 
 int PHY_MARV_PAGE_DATA ; 
 int PHY_MARV_PHY_CTRL ; 
 int PHY_MARV_PHY_STAT ; 
 int PHY_M_1000C_AFD ; 
 int PHY_M_1000C_AHD ; 
 int PHY_M_1000C_MSE ; 
 int PHY_M_AN_1000X_AFD ; 
 int PHY_M_AN_1000X_AHD ; 
 int PHY_M_AN_100_FD ; 
 int PHY_M_AN_100_HD ; 
 int PHY_M_AN_10_FD ; 
 int PHY_M_AN_10_HD ; 
 int PHY_M_DEF_MSK ; 
 int PHY_M_EC_DOWN_S_ENA ; 
 int PHY_M_EC_DSC_2 (int) ; 
 int PHY_M_EC_MAC_S (int /*<<< orphan*/ ) ; 
 int PHY_M_EC_MAC_S_MSK ; 
 int PHY_M_EC_M_DSC (int /*<<< orphan*/ ) ; 
 int PHY_M_EC_M_DSC_MSK ; 
 int PHY_M_EC_S_DSC (int) ; 
 int PHY_M_EC_S_DSC_MSK ; 
 int PHY_M_FELP_LED0_CTRL (int /*<<< orphan*/ ) ; 
 int PHY_M_FELP_LED1_CTRL (int /*<<< orphan*/ ) ; 
 int PHY_M_FELP_LED1_MSK ; 
 int PHY_M_FELP_LED2_CTRL (int /*<<< orphan*/ ) ; 
 int PHY_M_FESC_SEL_CL_A ; 
 int PHY_M_FIB_SIGD_POL ; 
 int PHY_M_IS_AN_COMPL ; 
 int PHY_M_LEDC_INIT_CTRL (int) ; 
 int PHY_M_LEDC_LOS_CTRL (int) ; 
 int PHY_M_LEDC_STA0_CTRL (int) ; 
 int PHY_M_LEDC_STA1_CTRL (int) ; 
 int PHY_M_LEDC_TX_CTRL ; 
 int PHY_M_LED_BLINK_RT (int /*<<< orphan*/ ) ; 
 int PHY_M_LED_MO_100 (int /*<<< orphan*/ ) ; 
 int PHY_M_LED_MO_RX (int /*<<< orphan*/ ) ; 
 int PHY_M_LED_PULS_DUR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PHY_M_MAC_MD_1000BX ; 
 int PHY_M_MAC_MD_MSK ; 
 int PHY_M_MAC_MODE_SEL (int /*<<< orphan*/ ) ; 
 int PHY_M_PC_DIS_SCRAMB ; 
 int PHY_M_PC_DOWN_S_ENA ; 
 int PHY_M_PC_DSC (int) ; 
 int PHY_M_PC_DSC_MSK ; 
 int /*<<< orphan*/  PHY_M_PC_ENA_AUTO ; 
 int PHY_M_PC_ENA_ENE_DT ; 
 int PHY_M_PC_ENA_LIP_NP ; 
 int PHY_M_PC_EN_DET_MSK ; 
 int PHY_M_PC_MDIX_MSK ; 
 int PHY_M_PC_MDI_XMODE (int /*<<< orphan*/ ) ; 
 int PHY_M_POLC_INIT_CTRL (int) ; 
 int PHY_M_POLC_IS0_P_MIX (int) ; 
 int PHY_M_POLC_LOS_CTRL (int) ; 
 int PHY_M_POLC_LS1_P_MIX (int) ; 
 int PHY_M_POLC_STA0_CTRL (int) ; 
 int PHY_M_POLC_STA1_CTRL (int) ; 
 int /*<<< orphan*/  PULS_170MS ; 
 int SKY2_FLAG_AUTO_PAUSE ; 
 int SKY2_FLAG_AUTO_SPEED ; 
 int SKY2_HW_FIBRE_PHY ; 
 int SKY2_HW_GIGABIT ; 
 int SKY2_HW_NEWER_PHY ; 
 int /*<<< orphan*/  SK_REG (unsigned int,int /*<<< orphan*/ ) ; 
#define  SPEED_100 129 
#define  SPEED_1000 128 
 int* copper_fc_adv ; 
 int* fiber_fc_adv ; 
 int* gm_fc_disable ; 
 int gm_phy_read (struct sky2_hw*,unsigned int,int) ; 
 int /*<<< orphan*/  gm_phy_write (struct sky2_hw*,unsigned int,int,int) ; 
 int /*<<< orphan*/  gma_write16 (struct sky2_hw*,unsigned int,int /*<<< orphan*/ ,int) ; 
 struct sky2_port* netdev_priv (int /*<<< orphan*/ ) ; 
 scalar_t__ sky2_is_copper (struct sky2_hw*) ; 
 int /*<<< orphan*/  sky2_write8 (struct sky2_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void sky2_phy_init(struct sky2_hw *hw, unsigned port)
{
	struct sky2_port *sky2 = netdev_priv(hw->dev[port]);
	u16 ctrl, ct1000, adv, pg, ledctrl, ledover, reg;

	if ( (sky2->flags & SKY2_FLAG_AUTO_SPEED) &&
	    !(hw->flags & SKY2_HW_NEWER_PHY)) {
		u16 ectrl = gm_phy_read(hw, port, PHY_MARV_EXT_CTRL);

		ectrl &= ~(PHY_M_EC_M_DSC_MSK | PHY_M_EC_S_DSC_MSK |
			   PHY_M_EC_MAC_S_MSK);
		ectrl |= PHY_M_EC_MAC_S(MAC_TX_CLK_25_MHZ);

		/* on PHY 88E1040 Rev.D0 (and newer) downshift control changed */
		if (hw->chip_id == CHIP_ID_YUKON_EC)
			/* set downshift counter to 3x and enable downshift */
			ectrl |= PHY_M_EC_DSC_2(2) | PHY_M_EC_DOWN_S_ENA;
		else
			/* set master & slave downshift counter to 1x */
			ectrl |= PHY_M_EC_M_DSC(0) | PHY_M_EC_S_DSC(1);

		gm_phy_write(hw, port, PHY_MARV_EXT_CTRL, ectrl);
	}

	ctrl = gm_phy_read(hw, port, PHY_MARV_PHY_CTRL);
	if (sky2_is_copper(hw)) {
		if (!(hw->flags & SKY2_HW_GIGABIT)) {
			/* enable automatic crossover */
			ctrl |= PHY_M_PC_MDI_XMODE(PHY_M_PC_ENA_AUTO) >> 1;

			if (hw->chip_id == CHIP_ID_YUKON_FE_P &&
			    hw->chip_rev == CHIP_REV_YU_FE2_A0) {
				u16 spec;

				/* Enable Class A driver for FE+ A0 */
				spec = gm_phy_read(hw, port, PHY_MARV_FE_SPEC_2);
				spec |= PHY_M_FESC_SEL_CL_A;
				gm_phy_write(hw, port, PHY_MARV_FE_SPEC_2, spec);
			}
		} else {
			/* disable energy detect */
			ctrl &= ~PHY_M_PC_EN_DET_MSK;

			/* enable automatic crossover */
			ctrl |= PHY_M_PC_MDI_XMODE(PHY_M_PC_ENA_AUTO);

			/* downshift on PHY 88E1112 and 88E1149 is changed */
			if ( (sky2->flags & SKY2_FLAG_AUTO_SPEED)
			    && (hw->flags & SKY2_HW_NEWER_PHY)) {
				/* set downshift counter to 3x and enable downshift */
				ctrl &= ~PHY_M_PC_DSC_MSK;
				ctrl |= PHY_M_PC_DSC(2) | PHY_M_PC_DOWN_S_ENA;
			}
		}
	} else {
		/* workaround for deviation #4.88 (CRC errors) */
		/* disable Automatic Crossover */

		ctrl &= ~PHY_M_PC_MDIX_MSK;
	}

	gm_phy_write(hw, port, PHY_MARV_PHY_CTRL, ctrl);

	/* special setup for PHY 88E1112 Fiber */
	if (hw->chip_id == CHIP_ID_YUKON_XL && (hw->flags & SKY2_HW_FIBRE_PHY)) {
		pg = gm_phy_read(hw, port, PHY_MARV_EXT_ADR);

		/* Fiber: select 1000BASE-X only mode MAC Specific Ctrl Reg. */
		gm_phy_write(hw, port, PHY_MARV_EXT_ADR, 2);
		ctrl = gm_phy_read(hw, port, PHY_MARV_PHY_CTRL);
		ctrl &= ~PHY_M_MAC_MD_MSK;
		ctrl |= PHY_M_MAC_MODE_SEL(PHY_M_MAC_MD_1000BX);
		gm_phy_write(hw, port, PHY_MARV_PHY_CTRL, ctrl);

		if (hw->pmd_type  == 'P') {
			/* select page 1 to access Fiber registers */
			gm_phy_write(hw, port, PHY_MARV_EXT_ADR, 1);

			/* for SFP-module set SIGDET polarity to low */
			ctrl = gm_phy_read(hw, port, PHY_MARV_PHY_CTRL);
			ctrl |= PHY_M_FIB_SIGD_POL;
			gm_phy_write(hw, port, PHY_MARV_PHY_CTRL, ctrl);
		}

		gm_phy_write(hw, port, PHY_MARV_EXT_ADR, pg);
	}

	ctrl = PHY_CT_RESET;
	ct1000 = 0;
	adv = PHY_AN_CSMA;
	reg = 0;

	if (sky2->flags & SKY2_FLAG_AUTO_SPEED) {
		if (sky2_is_copper(hw)) {
			if (sky2->advertising & ADVERTISED_1000baseT_Full)
				ct1000 |= PHY_M_1000C_AFD;
			if (sky2->advertising & ADVERTISED_1000baseT_Half)
				ct1000 |= PHY_M_1000C_AHD;
			if (sky2->advertising & ADVERTISED_100baseT_Full)
				adv |= PHY_M_AN_100_FD;
			if (sky2->advertising & ADVERTISED_100baseT_Half)
				adv |= PHY_M_AN_100_HD;
			if (sky2->advertising & ADVERTISED_10baseT_Full)
				adv |= PHY_M_AN_10_FD;
			if (sky2->advertising & ADVERTISED_10baseT_Half)
				adv |= PHY_M_AN_10_HD;

		} else {	/* special defines for FIBER (88E1040S only) */
			if (sky2->advertising & ADVERTISED_1000baseT_Full)
				adv |= PHY_M_AN_1000X_AFD;
			if (sky2->advertising & ADVERTISED_1000baseT_Half)
				adv |= PHY_M_AN_1000X_AHD;
		}

		/* Restart Auto-negotiation */
		ctrl |= PHY_CT_ANE | PHY_CT_RE_CFG;
	} else {
		/* forced speed/duplex settings */
		ct1000 = PHY_M_1000C_MSE;

		/* Disable auto update for duplex flow control and duplex */
		reg |= GM_GPCR_AU_DUP_DIS | GM_GPCR_AU_SPD_DIS;

		switch (sky2->speed) {
		case SPEED_1000:
			ctrl |= PHY_CT_SP1000;
			reg |= GM_GPCR_SPEED_1000;
			break;
		case SPEED_100:
			ctrl |= PHY_CT_SP100;
			reg |= GM_GPCR_SPEED_100;
			break;
		}

		if (sky2->duplex == DUPLEX_FULL) {
			reg |= GM_GPCR_DUP_FULL;
			ctrl |= PHY_CT_DUP_MD;
		} else if (sky2->speed < SPEED_1000)
			sky2->flow_mode = FC_NONE;
	}

	if (sky2->flags & SKY2_FLAG_AUTO_PAUSE) {
		if (sky2_is_copper(hw))
			adv |= copper_fc_adv[sky2->flow_mode];
		else
			adv |= fiber_fc_adv[sky2->flow_mode];
	} else {
		reg |= GM_GPCR_AU_FCT_DIS;
 		reg |= gm_fc_disable[sky2->flow_mode];

		/* Forward pause packets to GMAC? */
		if (sky2->flow_mode & FC_RX)
			sky2_write8(hw, SK_REG(port, GMAC_CTRL), GMC_PAUSE_ON);
		else
			sky2_write8(hw, SK_REG(port, GMAC_CTRL), GMC_PAUSE_OFF);
	}

	gma_write16(hw, port, GM_GP_CTRL, reg);

	if (hw->flags & SKY2_HW_GIGABIT)
		gm_phy_write(hw, port, PHY_MARV_1000T_CTRL, ct1000);

	gm_phy_write(hw, port, PHY_MARV_AUNE_ADV, adv);
	gm_phy_write(hw, port, PHY_MARV_CTRL, ctrl);

	/* Setup Phy LED's */
	ledctrl = PHY_M_LED_PULS_DUR(PULS_170MS);
	ledover = 0;

	switch (hw->chip_id) {
	case CHIP_ID_YUKON_FE:
		/* on 88E3082 these bits are at 11..9 (shifted left) */
		ledctrl |= PHY_M_LED_BLINK_RT(BLINK_84MS) << 1;

		ctrl = gm_phy_read(hw, port, PHY_MARV_FE_LED_PAR);

		/* delete ACT LED control bits */
		ctrl &= ~PHY_M_FELP_LED1_MSK;
		/* change ACT LED control to blink mode */
		ctrl |= PHY_M_FELP_LED1_CTRL(LED_PAR_CTRL_ACT_BL);
		gm_phy_write(hw, port, PHY_MARV_FE_LED_PAR, ctrl);
		break;

	case CHIP_ID_YUKON_FE_P:
		/* Enable Link Partner Next Page */
		ctrl = gm_phy_read(hw, port, PHY_MARV_PHY_CTRL);
		ctrl |= PHY_M_PC_ENA_LIP_NP;

		/* disable Energy Detect and enable scrambler */
		ctrl &= ~(PHY_M_PC_ENA_ENE_DT | PHY_M_PC_DIS_SCRAMB);
		gm_phy_write(hw, port, PHY_MARV_PHY_CTRL, ctrl);

		/* set LED2 -> ACT, LED1 -> LINK, LED0 -> SPEED */
		ctrl = PHY_M_FELP_LED2_CTRL(LED_PAR_CTRL_ACT_BL) |
			PHY_M_FELP_LED1_CTRL(LED_PAR_CTRL_LINK) |
			PHY_M_FELP_LED0_CTRL(LED_PAR_CTRL_SPEED);

		gm_phy_write(hw, port, PHY_MARV_FE_LED_PAR, ctrl);
		break;

	case CHIP_ID_YUKON_XL:
		pg = gm_phy_read(hw, port, PHY_MARV_EXT_ADR);

		/* select page 3 to access LED control register */
		gm_phy_write(hw, port, PHY_MARV_EXT_ADR, 3);

		/* set LED Function Control register */
		gm_phy_write(hw, port, PHY_MARV_PHY_CTRL,
			     (PHY_M_LEDC_LOS_CTRL(1) |	/* LINK/ACT */
			      PHY_M_LEDC_INIT_CTRL(7) |	/* 10 Mbps */
			      PHY_M_LEDC_STA1_CTRL(7) |	/* 100 Mbps */
			      PHY_M_LEDC_STA0_CTRL(7)));	/* 1000 Mbps */

		/* set Polarity Control register */
		gm_phy_write(hw, port, PHY_MARV_PHY_STAT,
			     (PHY_M_POLC_LS1_P_MIX(4) |
			      PHY_M_POLC_IS0_P_MIX(4) |
			      PHY_M_POLC_LOS_CTRL(2) |
			      PHY_M_POLC_INIT_CTRL(2) |
			      PHY_M_POLC_STA1_CTRL(2) |
			      PHY_M_POLC_STA0_CTRL(2)));

		/* restore page register */
		gm_phy_write(hw, port, PHY_MARV_EXT_ADR, pg);
		break;

	case CHIP_ID_YUKON_EC_U:
	case CHIP_ID_YUKON_EX:
	case CHIP_ID_YUKON_SUPR:
		pg = gm_phy_read(hw, port, PHY_MARV_EXT_ADR);

		/* select page 3 to access LED control register */
		gm_phy_write(hw, port, PHY_MARV_EXT_ADR, 3);

		/* set LED Function Control register */
		gm_phy_write(hw, port, PHY_MARV_PHY_CTRL,
			     (PHY_M_LEDC_LOS_CTRL(1) |	/* LINK/ACT */
			      PHY_M_LEDC_INIT_CTRL(8) |	/* 10 Mbps */
			      PHY_M_LEDC_STA1_CTRL(7) |	/* 100 Mbps */
			      PHY_M_LEDC_STA0_CTRL(7)));/* 1000 Mbps */

		/* set Blink Rate in LED Timer Control Register */
		gm_phy_write(hw, port, PHY_MARV_INT_MASK,
			     ledctrl | PHY_M_LED_BLINK_RT(BLINK_84MS));
		/* restore page register */
		gm_phy_write(hw, port, PHY_MARV_EXT_ADR, pg);
		break;

	default:
		/* set Tx LED (LED_TX) to blink mode on Rx OR Tx activity */
		ledctrl |= PHY_M_LED_BLINK_RT(BLINK_84MS) | PHY_M_LEDC_TX_CTRL;

		/* turn off the Rx LED (LED_RX) */
		ledover |= PHY_M_LED_MO_RX(MO_LED_OFF);
	}

	if (hw->chip_id == CHIP_ID_YUKON_EC_U || hw->chip_id == CHIP_ID_YUKON_UL_2) {
		/* apply fixes in PHY AFE */
		gm_phy_write(hw, port, PHY_MARV_EXT_ADR, 255);

		/* increase differential signal amplitude in 10BASE-T */
		gm_phy_write(hw, port, 0x18, 0xaa99);
		gm_phy_write(hw, port, 0x17, 0x2011);

		if (hw->chip_id == CHIP_ID_YUKON_EC_U) {
			/* fix for IEEE A/B Symmetry failure in 1000BASE-T */
			gm_phy_write(hw, port, 0x18, 0xa204);
			gm_phy_write(hw, port, 0x17, 0x2002);
		}

		/* set page register to 0 */
		gm_phy_write(hw, port, PHY_MARV_EXT_ADR, 0);
	} else if (hw->chip_id == CHIP_ID_YUKON_FE_P &&
		   hw->chip_rev == CHIP_REV_YU_FE2_A0) {
		/* apply workaround for integrated resistors calibration */
		gm_phy_write(hw, port, PHY_MARV_PAGE_ADDR, 17);
		gm_phy_write(hw, port, PHY_MARV_PAGE_DATA, 0x3f60);
	} else if (hw->chip_id != CHIP_ID_YUKON_EX &&
		   hw->chip_id < CHIP_ID_YUKON_SUPR) {
		/* no effect on Yukon-XL */
		gm_phy_write(hw, port, PHY_MARV_LED_CTRL, ledctrl);

		if ( !(sky2->flags & SKY2_FLAG_AUTO_SPEED)
		     || sky2->speed == SPEED_100) {
			/* turn on 100 Mbps LED (LED_LINK100) */
			ledover |= PHY_M_LED_MO_100(MO_LED_ON);
		}

		if (ledover)
			gm_phy_write(hw, port, PHY_MARV_LED_OVER, ledover);

	}

	/* Enable phy interrupt on auto-negotiation complete (or link up) */
	if (sky2->flags & SKY2_FLAG_AUTO_SPEED)
		gm_phy_write(hw, port, PHY_MARV_INT_MASK, PHY_M_IS_AN_COMPL);
	else
		gm_phy_write(hw, port, PHY_MARV_INT_MASK, PHY_M_DEF_MSK);
}