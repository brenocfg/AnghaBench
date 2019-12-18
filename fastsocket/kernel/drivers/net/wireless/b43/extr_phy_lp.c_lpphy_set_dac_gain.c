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
typedef  int u16 ;
struct b43_wldev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  B43_LPPHY_AFE_DAC_CTL ; 
 int /*<<< orphan*/  b43_phy_maskset (struct b43_wldev*,int /*<<< orphan*/ ,int,int) ; 
 int b43_phy_read (struct b43_wldev*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void lpphy_set_dac_gain(struct b43_wldev *dev, u16 dac)
{
	u16 ctl = b43_phy_read(dev, B43_LPPHY_AFE_DAC_CTL) & 0xC7F;
	ctl |= dac << 7;
	b43_phy_maskset(dev, B43_LPPHY_AFE_DAC_CTL, 0xF000, ctl);
}