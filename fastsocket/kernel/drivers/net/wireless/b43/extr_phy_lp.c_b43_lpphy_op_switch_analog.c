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
 int /*<<< orphan*/  B43_LPPHY_AFE_CTL_OVR ; 
 int /*<<< orphan*/  B43_LPPHY_AFE_CTL_OVRVAL ; 
 int /*<<< orphan*/  b43_phy_mask (struct b43_wldev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  b43_phy_set (struct b43_wldev*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void b43_lpphy_op_switch_analog(struct b43_wldev *dev, bool on)
{
       if (on) {
               b43_phy_mask(dev, B43_LPPHY_AFE_CTL_OVR, 0xfff8);
       } else {
               b43_phy_set(dev, B43_LPPHY_AFE_CTL_OVRVAL, 0x0007);
               b43_phy_set(dev, B43_LPPHY_AFE_CTL_OVR, 0x0007);
       }
}