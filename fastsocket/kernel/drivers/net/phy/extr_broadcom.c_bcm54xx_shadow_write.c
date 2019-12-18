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
typedef  int /*<<< orphan*/  u16 ;
struct phy_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MII_BCM54XX_SHD ; 
 int MII_BCM54XX_SHD_DATA (int /*<<< orphan*/ ) ; 
 int MII_BCM54XX_SHD_VAL (int /*<<< orphan*/ ) ; 
 int MII_BCM54XX_SHD_WRITE ; 
 int phy_write (struct phy_device*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int bcm54xx_shadow_write(struct phy_device *phydev, u16 shadow, u16 val)
{
	return phy_write(phydev, MII_BCM54XX_SHD,
			 MII_BCM54XX_SHD_WRITE |
			 MII_BCM54XX_SHD_VAL(shadow) |
			 MII_BCM54XX_SHD_DATA(val));
}