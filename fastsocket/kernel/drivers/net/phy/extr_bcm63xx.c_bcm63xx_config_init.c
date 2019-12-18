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
struct phy_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MII_BCM63XX_IR ; 
 int MII_BCM63XX_IR_DUPLEX ; 
 int MII_BCM63XX_IR_EN ; 
 int MII_BCM63XX_IR_GMASK ; 
 int MII_BCM63XX_IR_LINK ; 
 int MII_BCM63XX_IR_SPEED ; 
 int phy_read (struct phy_device*,int /*<<< orphan*/ ) ; 
 int phy_write (struct phy_device*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int bcm63xx_config_init(struct phy_device *phydev)
{
	int reg, err;

	reg = phy_read(phydev, MII_BCM63XX_IR);
	if (reg < 0)
		return reg;

	/* Mask interrupts globally.  */
	reg |= MII_BCM63XX_IR_GMASK;
	err = phy_write(phydev, MII_BCM63XX_IR, reg);
	if (err < 0)
		return err;

	/* Unmask events we are interested in  */
	reg = ~(MII_BCM63XX_IR_DUPLEX |
		MII_BCM63XX_IR_SPEED |
		MII_BCM63XX_IR_LINK) |
		MII_BCM63XX_IR_EN;
	err = phy_write(phydev, MII_BCM63XX_IR, reg);
	if (err < 0)
		return err;
	return 0;
}