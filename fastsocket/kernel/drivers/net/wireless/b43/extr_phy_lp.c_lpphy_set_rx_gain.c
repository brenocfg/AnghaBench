#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_2__ {int rev; } ;
struct b43_wldev {TYPE_1__ phy; } ;

/* Variables and functions */
 int /*<<< orphan*/  lpphy_enable_rx_gain_override (struct b43_wldev*) ; 
 int /*<<< orphan*/  lpphy_rev0_1_set_rx_gain (struct b43_wldev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lpphy_rev2plus_set_rx_gain (struct b43_wldev*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void lpphy_set_rx_gain(struct b43_wldev *dev, u32 gain)
{
	if (dev->phy.rev < 2)
		lpphy_rev0_1_set_rx_gain(dev, gain);
	else
		lpphy_rev2plus_set_rx_gain(dev, gain);
	lpphy_enable_rx_gain_override(dev);
}