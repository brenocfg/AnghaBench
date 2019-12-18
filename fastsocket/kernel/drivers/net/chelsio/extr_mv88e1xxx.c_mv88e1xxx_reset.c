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
typedef  int u32 ;
struct cphy {int dummy; } ;

/* Variables and functions */
 int BMCR_RESET ; 
 int /*<<< orphan*/  MII_BMCR ; 
 int /*<<< orphan*/  mdio_set_bit (struct cphy*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  simple_mdio_read (struct cphy*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int mv88e1xxx_reset(struct cphy *cphy, int wait)
{
	u32 ctl;
	int time_out = 1000;

	mdio_set_bit(cphy, MII_BMCR, BMCR_RESET);

	do {
		(void) simple_mdio_read(cphy, MII_BMCR, &ctl);
		ctl &= BMCR_RESET;
		if (ctl)
			udelay(1);
	} while (ctl && --time_out);

	return ctl ? -1 : 0;
}