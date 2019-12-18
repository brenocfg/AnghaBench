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
typedef  scalar_t__ u16 ;
struct TYPE_4__ {int phy_type; int /*<<< orphan*/  phy_rev; } ;
struct brcms_phy {scalar_t__ phy_wreg; int /*<<< orphan*/  d11core; TYPE_2__ pubpi; TYPE_1__* sh; } ;
struct TYPE_3__ {int /*<<< orphan*/  corerev; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONF_HAS (int /*<<< orphan*/ ,int const) ; 
 int /*<<< orphan*/  D11REGOFFS (int /*<<< orphan*/ ) ; 
 scalar_t__ D11REV_GE (int /*<<< orphan*/ ,int) ; 
 scalar_t__ D11REV_IS (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  NREV_GE (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  PHYTYPE ; 
#define  PHY_TYPE_LCN 129 
#define  PHY_TYPE_N 128 
 int PHY_TYPE_SSN ; 
 scalar_t__ RADIO_2055_READ_OFF ; 
 scalar_t__ RADIO_2057_READ_OFF ; 
 scalar_t__ RADIO_2064_READ_OFF ; 
 scalar_t__ RADIO_IDCODE ; 
 scalar_t__ bcma_read16 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bcma_wflush16 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  phy4waddr ; 
 int /*<<< orphan*/  phy4wdatalo ; 
 int /*<<< orphan*/  radioregaddr ; 
 int /*<<< orphan*/  radioregdata ; 

u16 read_radio_reg(struct brcms_phy *pi, u16 addr)
{
	u16 data;

	if ((addr == RADIO_IDCODE))
		return 0xffff;

	switch (pi->pubpi.phy_type) {
	case PHY_TYPE_N:
		if (!CONF_HAS(PHYTYPE, PHY_TYPE_N))
			break;
		if (NREV_GE(pi->pubpi.phy_rev, 7))
			addr |= RADIO_2057_READ_OFF;
		else
			addr |= RADIO_2055_READ_OFF;
		break;

	case PHY_TYPE_LCN:
		if (!CONF_HAS(PHYTYPE, PHY_TYPE_LCN))
			break;
		addr |= RADIO_2064_READ_OFF;
		break;

	default:
		break;
	}

	if ((D11REV_GE(pi->sh->corerev, 24)) ||
	    (D11REV_IS(pi->sh->corerev, 22)
	     && (pi->pubpi.phy_type != PHY_TYPE_SSN))) {
		bcma_wflush16(pi->d11core, D11REGOFFS(radioregaddr), addr);
		data = bcma_read16(pi->d11core, D11REGOFFS(radioregdata));
	} else {
		bcma_wflush16(pi->d11core, D11REGOFFS(phy4waddr), addr);
		data = bcma_read16(pi->d11core, D11REGOFFS(phy4wdatalo));
	}
	pi->phy_wreg = 0;

	return data;
}