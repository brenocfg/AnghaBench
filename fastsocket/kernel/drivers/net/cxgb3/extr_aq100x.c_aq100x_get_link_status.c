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
struct cphy {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AQ_ANEG_STAT ; 
 int /*<<< orphan*/  AQ_LINK_STAT ; 
 int DUPLEX_FULL ; 
 int DUPLEX_HALF ; 
 int /*<<< orphan*/  MDIO_MMD_AN ; 
 int /*<<< orphan*/  MDIO_MMD_PMAPMD ; 
 int SPEED_10 ; 
 int SPEED_100 ; 
 int SPEED_1000 ; 
 int SPEED_10000 ; 
 int t3_mdio_read (struct cphy*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int*) ; 

__attribute__((used)) static int aq100x_get_link_status(struct cphy *phy, int *link_ok,
				  int *speed, int *duplex, int *fc)
{
	int err;
	unsigned int v;

	if (link_ok) {
		err = t3_mdio_read(phy, MDIO_MMD_PMAPMD, AQ_LINK_STAT, &v);
		if (err)
			return err;

		*link_ok = v & 1;
		if (!*link_ok)
			return 0;
	}

	err = t3_mdio_read(phy, MDIO_MMD_AN, AQ_ANEG_STAT, &v);
	if (err)
		return err;

	if (speed) {
		switch (v & 0x6) {
		case 0x6:
			*speed = SPEED_10000;
			break;
		case 0x4:
			*speed = SPEED_1000;
			break;
		case 0x2:
			*speed = SPEED_100;
			break;
		case 0x0:
			*speed = SPEED_10;
			break;
		}
	}

	if (duplex)
		*duplex = v & 1 ? DUPLEX_FULL : DUPLEX_HALF;

	return 0;
}