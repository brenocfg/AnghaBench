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
typedef  scalar_t__ u16 ;
struct b43_wldev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  B43_PHY_GTABCTL ; 
 int /*<<< orphan*/  B43_PHY_GTABDATA ; 
 int /*<<< orphan*/  b43_phy_write (struct b43_wldev*,int /*<<< orphan*/ ,scalar_t__) ; 

void b43_gtab_write(struct b43_wldev *dev, u16 table, u16 offset, u16 value)
{
	b43_phy_write(dev, B43_PHY_GTABCTL, table + offset);
	b43_phy_write(dev, B43_PHY_GTABDATA, value);
}