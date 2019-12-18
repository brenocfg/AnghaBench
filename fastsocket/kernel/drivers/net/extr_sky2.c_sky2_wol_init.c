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
typedef  int /*<<< orphan*/  u32 ;
typedef  int u16 ;
struct sky2_port {unsigned int port; int flow_mode; int advertising; int wol; TYPE_1__* netdev; int /*<<< orphan*/  phy_lock; struct sky2_hw* hw; } ;
struct sky2_hw {scalar_t__ regs; } ;
typedef  enum flow_control { ____Placeholder_flow_control } flow_control ;
struct TYPE_2__ {int /*<<< orphan*/  dev_addr; } ;

/* Variables and functions */
 int ADVERTISED_1000baseT_Full ; 
 int ADVERTISED_1000baseT_Half ; 
 scalar_t__ B0_CTST ; 
 int CS_RST_CLR ; 
 int /*<<< orphan*/  ETH_ALEN ; 
 int FC_NONE ; 
 int /*<<< orphan*/  GMAC_CTRL ; 
 int /*<<< orphan*/  GMAC_LINK_CTRL ; 
 int /*<<< orphan*/  GMC_RST_CLR ; 
 int /*<<< orphan*/  GMF_RST_SET ; 
 int GMLC_RST_CLR ; 
 int GM_GPCR_AU_FCT_DIS ; 
 int GM_GPCR_DUP_FULL ; 
 int GM_GPCR_FC_RX_DIS ; 
 int GM_GPCR_FC_TX_DIS ; 
 int GM_GPCR_RX_ENA ; 
 int GM_GPCR_TX_ENA ; 
 int /*<<< orphan*/  GM_GP_CTRL ; 
 int /*<<< orphan*/  GPC_RST_CLR ; 
 int /*<<< orphan*/  GPHY_CTRL ; 
 int /*<<< orphan*/  PCI_DEV_REG1 ; 
 int /*<<< orphan*/  PCI_Y2_PME_LEGACY ; 
 int /*<<< orphan*/  RX_GMF_CTRL_T ; 
 scalar_t__ SK_REG (unsigned int,int /*<<< orphan*/ ) ; 
 int WAKE_MAGIC ; 
 int WAKE_PHY ; 
 int WOL_CTL_CLEAR_RESULT ; 
 int WOL_CTL_DIS_LINK_CHG_UNIT ; 
 int WOL_CTL_DIS_MAGIC_PKT_UNIT ; 
 int WOL_CTL_DIS_PATTERN_UNIT ; 
 int WOL_CTL_DIS_PME_ON_LINK_CHG ; 
 int WOL_CTL_DIS_PME_ON_MAGIC_PKT ; 
 int WOL_CTL_DIS_PME_ON_PATTERN ; 
 int WOL_CTL_ENA_LINK_CHG_UNIT ; 
 int WOL_CTL_ENA_MAGIC_PKT_UNIT ; 
 int WOL_CTL_ENA_PME_ON_LINK_CHG ; 
 int WOL_CTL_ENA_PME_ON_MAGIC_PKT ; 
 int /*<<< orphan*/  WOL_CTRL_STAT ; 
 int /*<<< orphan*/  WOL_MAC_ADDR ; 
 scalar_t__ WOL_REGS (unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gma_write16 (struct sky2_hw*,unsigned int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memcpy_toio (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sky2_pci_read32 (struct sky2_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sky2_pci_write32 (struct sky2_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sky2_phy_init (struct sky2_hw*,unsigned int) ; 
 int /*<<< orphan*/  sky2_phy_power_up (struct sky2_hw*,unsigned int) ; 
 int /*<<< orphan*/  sky2_write16 (struct sky2_hw*,scalar_t__,int) ; 
 int /*<<< orphan*/  sky2_write8 (struct sky2_hw*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void sky2_wol_init(struct sky2_port *sky2)
{
	struct sky2_hw *hw = sky2->hw;
	unsigned port = sky2->port;
	enum flow_control save_mode;
	u16 ctrl;
	u32 reg1;

	/* Bring hardware out of reset */
	sky2_write16(hw, B0_CTST, CS_RST_CLR);
	sky2_write16(hw, SK_REG(port, GMAC_LINK_CTRL), GMLC_RST_CLR);

	sky2_write8(hw, SK_REG(port, GPHY_CTRL), GPC_RST_CLR);
	sky2_write8(hw, SK_REG(port, GMAC_CTRL), GMC_RST_CLR);

	/* Force to 10/100
	 * sky2_reset will re-enable on resume
	 */
	save_mode = sky2->flow_mode;
	ctrl = sky2->advertising;

	sky2->advertising &= ~(ADVERTISED_1000baseT_Half|ADVERTISED_1000baseT_Full);
	sky2->flow_mode = FC_NONE;

	spin_lock_bh(&sky2->phy_lock);
	sky2_phy_power_up(hw, port);
	sky2_phy_init(hw, port);
	spin_unlock_bh(&sky2->phy_lock);

	sky2->flow_mode = save_mode;
	sky2->advertising = ctrl;

	/* Set GMAC to no flow control and auto update for speed/duplex */
	gma_write16(hw, port, GM_GP_CTRL,
		    GM_GPCR_FC_TX_DIS|GM_GPCR_TX_ENA|GM_GPCR_RX_ENA|
		    GM_GPCR_DUP_FULL|GM_GPCR_FC_RX_DIS|GM_GPCR_AU_FCT_DIS);

	/* Set WOL address */
	memcpy_toio(hw->regs + WOL_REGS(port, WOL_MAC_ADDR),
		    sky2->netdev->dev_addr, ETH_ALEN);

	/* Turn on appropriate WOL control bits */
	sky2_write16(hw, WOL_REGS(port, WOL_CTRL_STAT), WOL_CTL_CLEAR_RESULT);
	ctrl = 0;
	if (sky2->wol & WAKE_PHY)
		ctrl |= WOL_CTL_ENA_PME_ON_LINK_CHG|WOL_CTL_ENA_LINK_CHG_UNIT;
	else
		ctrl |= WOL_CTL_DIS_PME_ON_LINK_CHG|WOL_CTL_DIS_LINK_CHG_UNIT;

	if (sky2->wol & WAKE_MAGIC)
		ctrl |= WOL_CTL_ENA_PME_ON_MAGIC_PKT|WOL_CTL_ENA_MAGIC_PKT_UNIT;
	else
		ctrl |= WOL_CTL_DIS_PME_ON_MAGIC_PKT|WOL_CTL_DIS_MAGIC_PKT_UNIT;

	ctrl |= WOL_CTL_DIS_PME_ON_PATTERN|WOL_CTL_DIS_PATTERN_UNIT;
	sky2_write16(hw, WOL_REGS(port, WOL_CTRL_STAT), ctrl);

	/* Turn on legacy PCI-Express PME mode */
	reg1 = sky2_pci_read32(hw, PCI_DEV_REG1);
	reg1 |= PCI_Y2_PME_LEGACY;
	sky2_pci_write32(hw, PCI_DEV_REG1, reg1);

	/* block receiver */
	sky2_write8(hw, SK_REG(port, RX_GMF_CTRL_T), GMF_RST_SET);

}