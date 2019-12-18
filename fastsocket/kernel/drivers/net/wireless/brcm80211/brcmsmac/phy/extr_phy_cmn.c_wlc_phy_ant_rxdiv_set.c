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
typedef  scalar_t__ u8 ;
typedef  int u16 ;
struct brcms_phy_pub {int dummy; } ;
struct brcms_phy {TYPE_1__* sh; int /*<<< orphan*/  d11core; } ;
struct TYPE_2__ {int /*<<< orphan*/  physhim; int /*<<< orphan*/  clk; int /*<<< orphan*/  corerev; scalar_t__ rx_antdiv; } ;

/* Variables and functions */
 scalar_t__ ANT_RX_DIV_FORCE_1 ; 
 scalar_t__ ANT_RX_DIV_START_1 ; 
 int /*<<< orphan*/  BRCM_BAND_ALL ; 
 int /*<<< orphan*/  D11REGOFFS (int /*<<< orphan*/ ) ; 
 scalar_t__ D11REV_IS (int /*<<< orphan*/ ,int) ; 
 scalar_t__ ISLCNPHY (struct brcms_phy*) ; 
 scalar_t__ ISNPHY (struct brcms_phy*) ; 
 int MCTL_EN_MAC ; 
 int /*<<< orphan*/  MHF1 ; 
 int /*<<< orphan*/  MHF1_ANTDIV ; 
 int bcma_read32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  maccontrol ; 
 int /*<<< orphan*/  mod_phy_reg (struct brcms_phy*,int,int,int) ; 
 int /*<<< orphan*/  wlapi_bmac_mhf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wlapi_enable_mac (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wlapi_suspend_mac_and_wait (int /*<<< orphan*/ ) ; 

void wlc_phy_ant_rxdiv_set(struct brcms_phy_pub *ppi, u8 val)
{
	struct brcms_phy *pi = (struct brcms_phy *) ppi;
	bool suspend;

	pi->sh->rx_antdiv = val;

	if (!(ISNPHY(pi) && D11REV_IS(pi->sh->corerev, 16))) {
		if (val > ANT_RX_DIV_FORCE_1)
			wlapi_bmac_mhf(pi->sh->physhim, MHF1, MHF1_ANTDIV,
				       MHF1_ANTDIV, BRCM_BAND_ALL);
		else
			wlapi_bmac_mhf(pi->sh->physhim, MHF1, MHF1_ANTDIV, 0,
				       BRCM_BAND_ALL);
	}

	if (ISNPHY(pi))
		return;

	if (!pi->sh->clk)
		return;

	suspend = (0 == (bcma_read32(pi->d11core, D11REGOFFS(maccontrol)) &
			 MCTL_EN_MAC));
	if (!suspend)
		wlapi_suspend_mac_and_wait(pi->sh->physhim);

	if (ISLCNPHY(pi)) {
		if (val > ANT_RX_DIV_FORCE_1) {
			mod_phy_reg(pi, 0x410, (0x1 << 1), 0x01 << 1);
			mod_phy_reg(pi, 0x410,
				    (0x1 << 0),
				    ((ANT_RX_DIV_START_1 == val) ? 1 : 0) << 0);
		} else {
			mod_phy_reg(pi, 0x410, (0x1 << 1), 0x00 << 1);
			mod_phy_reg(pi, 0x410, (0x1 << 0), (u16) val << 0);
		}
	}

	if (!suspend)
		wlapi_enable_mac(pi->sh->physhim);

	return;
}