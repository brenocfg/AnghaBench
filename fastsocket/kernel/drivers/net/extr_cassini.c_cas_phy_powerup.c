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
struct cas {int dummy; } ;

/* Variables and functions */
 int BMCR_PDOWN ; 
 int /*<<< orphan*/  MII_BMCR ; 
 int cas_phy_read (struct cas*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cas_phy_write (struct cas*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void cas_phy_powerup(struct cas *cp)
{
	u16 ctl = cas_phy_read(cp, MII_BMCR);

	if ((ctl & BMCR_PDOWN) == 0)
		return;
	ctl &= ~BMCR_PDOWN;
	cas_phy_write(cp, MII_BMCR, ctl);
}