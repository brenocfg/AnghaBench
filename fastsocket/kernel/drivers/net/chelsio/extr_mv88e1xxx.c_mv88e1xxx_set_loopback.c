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
 int /*<<< orphan*/  BMCR_LOOPBACK ; 
 int /*<<< orphan*/  MII_BMCR ; 
 int /*<<< orphan*/  mdio_clear_bit (struct cphy*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mdio_set_bit (struct cphy*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mv88e1xxx_set_loopback(struct cphy *cphy, int on)
{
	if (on)
		mdio_set_bit(cphy, MII_BMCR, BMCR_LOOPBACK);
	else
		mdio_clear_bit(cphy, MII_BMCR, BMCR_LOOPBACK);
	return 0;
}