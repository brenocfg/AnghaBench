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
struct b43_wldev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  b43_phy_switch_macfreq (struct b43_wldev*,int) ; 
 int /*<<< orphan*/  b43_phy_write (struct b43_wldev*,int,int) ; 

__attribute__((used)) static void b43_phy_lcn_txrx_spur_avoidance_mode(struct b43_wldev *dev,
						 bool enable)
{
	if (enable) {
		b43_phy_write(dev, 0x942, 0x7);
		b43_phy_write(dev, 0x93b, ((1 << 13) + 23));
		b43_phy_write(dev, 0x93c, ((1 << 13) + 1989));

		b43_phy_write(dev, 0x44a, 0x084);
		b43_phy_write(dev, 0x44a, 0x080);
		b43_phy_write(dev, 0x6d3, 0x2222);
		b43_phy_write(dev, 0x6d3, 0x2220);
	} else {
		b43_phy_write(dev, 0x942, 0x0);
		b43_phy_write(dev, 0x93b, ((0 << 13) + 23));
		b43_phy_write(dev, 0x93c, ((0 << 13) + 1989));
	}
	b43_phy_switch_macfreq(dev, enable);
}