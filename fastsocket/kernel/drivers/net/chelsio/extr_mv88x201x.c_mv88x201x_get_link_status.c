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
typedef  int /*<<< orphan*/  u32 ;
struct cphy {int dummy; } ;

/* Variables and functions */
 int DUPLEX_FULL ; 
 int /*<<< orphan*/  MDIO_MMD_PMAPMD ; 
 int /*<<< orphan*/  MDIO_STAT1 ; 
 int /*<<< orphan*/  MDIO_STAT1_LSTATUS ; 
 int PAUSE_RX ; 
 int PAUSE_TX ; 
 int SPEED_10000 ; 
 int /*<<< orphan*/  cphy_mdio_read (struct cphy*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  led_link (struct cphy*,int) ; 

__attribute__((used)) static int mv88x201x_get_link_status(struct cphy *cphy, int *link_ok,
				     int *speed, int *duplex, int *fc)
{
	u32 val = 0;

	if (link_ok) {
		/* Read link status. */
		cphy_mdio_read(cphy, MDIO_MMD_PMAPMD, MDIO_STAT1, &val);
		val &= MDIO_STAT1_LSTATUS;
		*link_ok = (val == MDIO_STAT1_LSTATUS);
		/* Turn on/off Link LED */
		led_link(cphy, *link_ok);
	}
	if (speed)
		*speed = SPEED_10000;
	if (duplex)
		*duplex = DUPLEX_FULL;
	if (fc)
		*fc = PAUSE_RX | PAUSE_TX;
	return 0;
}