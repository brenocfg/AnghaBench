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
typedef  scalar_t__ u16 ;
struct brcms_phy_pub {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  phy_rev; } ;
struct brcms_phy {int /*<<< orphan*/  d11core; TYPE_1__ pubpi; } ;

/* Variables and functions */
 int /*<<< orphan*/  D11REGOFFS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ISNPHY (struct brcms_phy*) ; 
 scalar_t__ NREV_IS (int /*<<< orphan*/ ,int) ; 
 int ON ; 
 int /*<<< orphan*/  bcma_set16 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  bcma_wflush16 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  bcma_write16 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  phyregaddr ; 
 int /*<<< orphan*/  phyregdata ; 
 int /*<<< orphan*/  wlc_phy_por_inform (struct brcms_phy_pub*) ; 

void wlc_phy_runbist_config(struct brcms_phy_pub *ppi, bool start_end)
{
	struct brcms_phy *pi = (struct brcms_phy *) ppi;
	u16 rxc;
	rxc = 0;

	if (start_end == ON) {
		if (!ISNPHY(pi))
			return;

		if (NREV_IS(pi->pubpi.phy_rev, 3)
		    || NREV_IS(pi->pubpi.phy_rev, 4)) {
			bcma_wflush16(pi->d11core, D11REGOFFS(phyregaddr),
				      0xa0);
			bcma_set16(pi->d11core, D11REGOFFS(phyregdata),
				   0x1 << 15);
		}
	} else {
		if (NREV_IS(pi->pubpi.phy_rev, 3)
		    || NREV_IS(pi->pubpi.phy_rev, 4)) {
			bcma_wflush16(pi->d11core, D11REGOFFS(phyregaddr),
				      0xa0);
			bcma_write16(pi->d11core, D11REGOFFS(phyregdata), rxc);
		}

		wlc_phy_por_inform(ppi);
	}
}