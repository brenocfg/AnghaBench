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
 int /*<<< orphan*/  b43_phy_maskset (struct b43_wldev*,int,int,int) ; 

__attribute__((used)) static void b43_phy_lcn_set_tx_gain_override(struct b43_wldev *dev, bool enable)
{
	b43_phy_maskset(dev, 0x4b0, ~(0x1 << 7), enable << 7);
	b43_phy_maskset(dev, 0x4b0, ~(0x1 << 14), enable << 14);
	b43_phy_maskset(dev, 0x43b, ~(0x1 << 6), enable << 6);
}