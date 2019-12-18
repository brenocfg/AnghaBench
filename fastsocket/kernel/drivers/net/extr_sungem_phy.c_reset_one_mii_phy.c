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
struct mii_phy {int dummy; } ;

/* Variables and functions */
 int BMCR_ISOLATE ; 
 int BMCR_PDOWN ; 
 int BMCR_RESET ; 
 int /*<<< orphan*/  MII_BMCR ; 
 int __phy_read (struct mii_phy*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __phy_write (struct mii_phy*,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int reset_one_mii_phy(struct mii_phy* phy, int phy_id)
{
	u16 val;
	int limit = 10000;

	val = __phy_read(phy, phy_id, MII_BMCR);
	val &= ~(BMCR_ISOLATE | BMCR_PDOWN);
	val |= BMCR_RESET;
	__phy_write(phy, phy_id, MII_BMCR, val);

	udelay(100);

	while (--limit) {
		val = __phy_read(phy, phy_id, MII_BMCR);
		if ((val & BMCR_RESET) == 0)
			break;
		udelay(10);
	}
	if ((val & BMCR_ISOLATE) && limit > 0)
		__phy_write(phy, phy_id, MII_BMCR, val & ~BMCR_ISOLATE);

	return (limit <= 0);
}