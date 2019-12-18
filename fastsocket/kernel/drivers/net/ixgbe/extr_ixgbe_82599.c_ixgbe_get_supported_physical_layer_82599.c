#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  int u32 ;
typedef  int u16 ;
struct TYPE_3__ {int /*<<< orphan*/  (* read_i2c_eeprom ) (struct ixgbe_hw*,int /*<<< orphan*/ ,int*) ;int /*<<< orphan*/  (* identify_sfp ) (struct ixgbe_hw*) ;int /*<<< orphan*/  (* read_reg ) (struct ixgbe_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ;int /*<<< orphan*/  (* identify ) (struct ixgbe_hw*) ;} ;
struct TYPE_4__ {int type; scalar_t__ sfp_type; TYPE_1__ ops; } ;
struct ixgbe_hw {TYPE_2__ phy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IXGBE_AUTOC ; 
 int /*<<< orphan*/  IXGBE_AUTOC2 ; 
 int IXGBE_AUTOC2_10G_KR ; 
 int IXGBE_AUTOC2_10G_SERIAL_PMA_PMD_MASK ; 
 int IXGBE_AUTOC2_10G_SFI ; 
 int IXGBE_AUTOC_10G_CX4 ; 
 int IXGBE_AUTOC_10G_KX4 ; 
 int IXGBE_AUTOC_10G_PMA_PMD_MASK ; 
 int IXGBE_AUTOC_10G_XAUI ; 
 int IXGBE_AUTOC_1G_KX_BX ; 
 int IXGBE_AUTOC_1G_PMA_PMD_MASK ; 
 int IXGBE_AUTOC_KR_SUPP ; 
 int IXGBE_AUTOC_KX4_SUPP ; 
 int IXGBE_AUTOC_KX_SUPP ; 
#define  IXGBE_AUTOC_LMS_10G_LINK_NO_AN 147 
#define  IXGBE_AUTOC_LMS_10G_SERIAL 146 
#define  IXGBE_AUTOC_LMS_1G_AN 145 
#define  IXGBE_AUTOC_LMS_1G_LINK_NO_AN 144 
#define  IXGBE_AUTOC_LMS_KX4_KX_KR 143 
#define  IXGBE_AUTOC_LMS_KX4_KX_KR_1G_AN 142 
 int IXGBE_AUTOC_LMS_MASK ; 
 int IXGBE_PHYSICAL_LAYER_1000BASE_BX ; 
 int IXGBE_PHYSICAL_LAYER_1000BASE_KX ; 
 int IXGBE_PHYSICAL_LAYER_1000BASE_T ; 
 int IXGBE_PHYSICAL_LAYER_100BASE_TX ; 
 int IXGBE_PHYSICAL_LAYER_10GBASE_CX4 ; 
 int IXGBE_PHYSICAL_LAYER_10GBASE_KR ; 
 int IXGBE_PHYSICAL_LAYER_10GBASE_KX4 ; 
 int IXGBE_PHYSICAL_LAYER_10GBASE_LR ; 
 int IXGBE_PHYSICAL_LAYER_10GBASE_SR ; 
 int IXGBE_PHYSICAL_LAYER_10GBASE_T ; 
 int IXGBE_PHYSICAL_LAYER_10GBASE_XAUI ; 
 int IXGBE_PHYSICAL_LAYER_SFP_ACTIVE_DA ; 
 int IXGBE_PHYSICAL_LAYER_SFP_PLUS_CU ; 
 int IXGBE_PHYSICAL_LAYER_UNKNOWN ; 
 int IXGBE_READ_REG (struct ixgbe_hw*,int /*<<< orphan*/ ) ; 
 int IXGBE_SFF_10GBASELR_CAPABLE ; 
 int IXGBE_SFF_10GBASESR_CAPABLE ; 
 int /*<<< orphan*/  IXGBE_SFF_10GBE_COMP_CODES ; 
 int IXGBE_SFF_1GBASET_CAPABLE ; 
 int /*<<< orphan*/  IXGBE_SFF_1GBE_COMP_CODES ; 
 int /*<<< orphan*/  IXGBE_SFF_QSFP_10GBE_COMP ; 
 int /*<<< orphan*/  MDIO_MMD_PMAPMD ; 
 int /*<<< orphan*/  MDIO_PMA_EXTABLE ; 
 int MDIO_PMA_EXTABLE_1000BT ; 
 int MDIO_PMA_EXTABLE_100BTX ; 
 int MDIO_PMA_EXTABLE_10GBT ; 
#define  ixgbe_phy_cu_unknown 141 
#define  ixgbe_phy_qsfp_active_unknown 140 
#define  ixgbe_phy_qsfp_intel 139 
#define  ixgbe_phy_qsfp_passive_unknown 138 
#define  ixgbe_phy_qsfp_unknown 137 
#define  ixgbe_phy_sfp_active_unknown 136 
#define  ixgbe_phy_sfp_avago 135 
#define  ixgbe_phy_sfp_ftl 134 
#define  ixgbe_phy_sfp_ftl_active 133 
#define  ixgbe_phy_sfp_intel 132 
#define  ixgbe_phy_sfp_passive_tyco 131 
#define  ixgbe_phy_sfp_passive_unknown 130 
#define  ixgbe_phy_sfp_unknown 129 
#define  ixgbe_phy_tn 128 
 scalar_t__ ixgbe_sfp_type_not_present ; 
 int /*<<< orphan*/  stub1 (struct ixgbe_hw*) ; 
 int /*<<< orphan*/  stub2 (struct ixgbe_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  stub3 (struct ixgbe_hw*) ; 
 int /*<<< orphan*/  stub4 (struct ixgbe_hw*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  stub5 (struct ixgbe_hw*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  stub6 (struct ixgbe_hw*,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static u32 ixgbe_get_supported_physical_layer_82599(struct ixgbe_hw *hw)
{
	u32 physical_layer = IXGBE_PHYSICAL_LAYER_UNKNOWN;
	u32 autoc = IXGBE_READ_REG(hw, IXGBE_AUTOC);
	u32 autoc2 = IXGBE_READ_REG(hw, IXGBE_AUTOC2);
	u32 pma_pmd_10g_serial = autoc2 & IXGBE_AUTOC2_10G_SERIAL_PMA_PMD_MASK;
	u32 pma_pmd_10g_parallel = autoc & IXGBE_AUTOC_10G_PMA_PMD_MASK;
	u32 pma_pmd_1g = autoc & IXGBE_AUTOC_1G_PMA_PMD_MASK;
	u16 ext_ability = 0;
	u8 comp_codes_10g = 0;
	u8 comp_codes_1g = 0;

	hw->phy.ops.identify(hw);

	switch (hw->phy.type) {
	case ixgbe_phy_tn:
	case ixgbe_phy_cu_unknown:
		hw->phy.ops.read_reg(hw, MDIO_PMA_EXTABLE, MDIO_MMD_PMAPMD,
							 &ext_ability);
		if (ext_ability & MDIO_PMA_EXTABLE_10GBT)
			physical_layer |= IXGBE_PHYSICAL_LAYER_10GBASE_T;
		if (ext_ability & MDIO_PMA_EXTABLE_1000BT)
			physical_layer |= IXGBE_PHYSICAL_LAYER_1000BASE_T;
		if (ext_ability & MDIO_PMA_EXTABLE_100BTX)
			physical_layer |= IXGBE_PHYSICAL_LAYER_100BASE_TX;
		goto out;
	default:
		break;
	}

	switch (autoc & IXGBE_AUTOC_LMS_MASK) {
	case IXGBE_AUTOC_LMS_1G_AN:
	case IXGBE_AUTOC_LMS_1G_LINK_NO_AN:
		if (pma_pmd_1g == IXGBE_AUTOC_1G_KX_BX) {
			physical_layer = IXGBE_PHYSICAL_LAYER_1000BASE_KX |
			    IXGBE_PHYSICAL_LAYER_1000BASE_BX;
			goto out;
		} else
			/* SFI mode so read SFP module */
			goto sfp_check;
		break;
	case IXGBE_AUTOC_LMS_10G_LINK_NO_AN:
		if (pma_pmd_10g_parallel == IXGBE_AUTOC_10G_CX4)
			physical_layer = IXGBE_PHYSICAL_LAYER_10GBASE_CX4;
		else if (pma_pmd_10g_parallel == IXGBE_AUTOC_10G_KX4)
			physical_layer = IXGBE_PHYSICAL_LAYER_10GBASE_KX4;
		else if (pma_pmd_10g_parallel == IXGBE_AUTOC_10G_XAUI)
			physical_layer = IXGBE_PHYSICAL_LAYER_10GBASE_XAUI;
		goto out;
		break;
	case IXGBE_AUTOC_LMS_10G_SERIAL:
		if (pma_pmd_10g_serial == IXGBE_AUTOC2_10G_KR) {
			physical_layer = IXGBE_PHYSICAL_LAYER_10GBASE_KR;
			goto out;
		} else if (pma_pmd_10g_serial == IXGBE_AUTOC2_10G_SFI)
			goto sfp_check;
		break;
	case IXGBE_AUTOC_LMS_KX4_KX_KR:
	case IXGBE_AUTOC_LMS_KX4_KX_KR_1G_AN:
		if (autoc & IXGBE_AUTOC_KX_SUPP)
			physical_layer |= IXGBE_PHYSICAL_LAYER_1000BASE_KX;
		if (autoc & IXGBE_AUTOC_KX4_SUPP)
			physical_layer |= IXGBE_PHYSICAL_LAYER_10GBASE_KX4;
		if (autoc & IXGBE_AUTOC_KR_SUPP)
			physical_layer |= IXGBE_PHYSICAL_LAYER_10GBASE_KR;
		goto out;
		break;
	default:
		goto out;
		break;
	}

sfp_check:
	/* SFP check must be done last since DA modules are sometimes used to
	 * test KR mode -  we need to id KR mode correctly before SFP module.
	 * Call identify_sfp because the pluggable module may have changed */
	hw->phy.ops.identify_sfp(hw);
	if (hw->phy.sfp_type == ixgbe_sfp_type_not_present)
		goto out;

	switch (hw->phy.type) {
	case ixgbe_phy_sfp_passive_tyco:
	case ixgbe_phy_sfp_passive_unknown:
	case ixgbe_phy_qsfp_passive_unknown:
		physical_layer = IXGBE_PHYSICAL_LAYER_SFP_PLUS_CU;
		break;
	case ixgbe_phy_sfp_ftl_active:
	case ixgbe_phy_sfp_active_unknown:
	case ixgbe_phy_qsfp_active_unknown:
		physical_layer = IXGBE_PHYSICAL_LAYER_SFP_ACTIVE_DA;
		break;
	case ixgbe_phy_sfp_avago:
	case ixgbe_phy_sfp_ftl:
	case ixgbe_phy_sfp_intel:
	case ixgbe_phy_sfp_unknown:
		hw->phy.ops.read_i2c_eeprom(hw,
		      IXGBE_SFF_1GBE_COMP_CODES, &comp_codes_1g);
		hw->phy.ops.read_i2c_eeprom(hw,
		      IXGBE_SFF_10GBE_COMP_CODES, &comp_codes_10g);
		if (comp_codes_10g & IXGBE_SFF_10GBASESR_CAPABLE)
			physical_layer = IXGBE_PHYSICAL_LAYER_10GBASE_SR;
		else if (comp_codes_10g & IXGBE_SFF_10GBASELR_CAPABLE)
			physical_layer = IXGBE_PHYSICAL_LAYER_10GBASE_LR;
		else if (comp_codes_1g & IXGBE_SFF_1GBASET_CAPABLE)
			physical_layer = IXGBE_PHYSICAL_LAYER_1000BASE_T;
		break;
	case ixgbe_phy_qsfp_intel:
	case ixgbe_phy_qsfp_unknown:
		hw->phy.ops.read_i2c_eeprom(hw,
			IXGBE_SFF_QSFP_10GBE_COMP, &comp_codes_10g);
		if (comp_codes_10g & IXGBE_SFF_10GBASESR_CAPABLE)
			physical_layer = IXGBE_PHYSICAL_LAYER_10GBASE_SR;
		else if (comp_codes_10g & IXGBE_SFF_10GBASELR_CAPABLE)
			physical_layer = IXGBE_PHYSICAL_LAYER_10GBASE_LR;
		break;
	default:
		break;
	}

out:
	return physical_layer;
}