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
typedef  scalar_t__ u8 ;
struct cphy {int priv; scalar_t__ modtype; } ;

/* Variables and functions */
 int /*<<< orphan*/  AEL2020_GPIO_INTR ; 
 int AEL2020_GPIO_MODDET ; 
 int /*<<< orphan*/  MDIO_MMD_PMAPMD ; 
 int ael2020_get_module_type (struct cphy*,int) ; 
 int ael2020_reset (struct cphy*,int /*<<< orphan*/ ) ; 
 int cphy_cause_link_change ; 
 int cphy_cause_module_change ; 
 int edc_sr ; 
 int edc_twinax ; 
 int phy_modtype_none ; 
 int phy_modtype_twinax ; 
 int phy_modtype_twinax_long ; 
 int t3_mdio_read (struct cphy*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int*) ; 
 int t3_phy_lasi_intr_handler (struct cphy*) ; 

__attribute__((used)) static int ael2020_intr_handler(struct cphy *phy)
{
	unsigned int stat;
	int ret, edc_needed, cause = 0;

	ret = t3_mdio_read(phy, MDIO_MMD_PMAPMD, AEL2020_GPIO_INTR, &stat);
	if (ret)
		return ret;

	if (stat & (0x1 << AEL2020_GPIO_MODDET)) {
		/* modules have max 300 ms init time after hot plug */
		ret = ael2020_get_module_type(phy, 300);
		if (ret < 0)
			return ret;

		phy->modtype = (u8)ret;
		if (ret == phy_modtype_none)
			edc_needed = phy->priv;       /* on unplug retain EDC */
		else if (ret == phy_modtype_twinax ||
			 ret == phy_modtype_twinax_long)
			edc_needed = edc_twinax;
		else
			edc_needed = edc_sr;

		if (edc_needed != phy->priv) {
			ret = ael2020_reset(phy, 0);
			return ret ? ret : cphy_cause_module_change;
		}
		cause = cphy_cause_module_change;
	}

	ret = t3_phy_lasi_intr_handler(phy);
	if (ret < 0)
		return ret;

	ret |= cause;
	return ret ? ret : cphy_cause_link_change;
}