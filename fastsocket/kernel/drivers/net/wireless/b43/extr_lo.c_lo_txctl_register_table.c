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
struct b43_phy {scalar_t__ type; int radio_rev; int rev; } ;
struct b43_wldev {struct b43_phy phy; } ;

/* Variables and functions */
 scalar_t__ B43_PHYTYPE_B ; 

__attribute__((used)) static u16 lo_txctl_register_table(struct b43_wldev *dev,
				   u16 *value, u16 *pad_mix_gain)
{
	struct b43_phy *phy = &dev->phy;
	u16 reg, v, padmix;

	if (phy->type == B43_PHYTYPE_B) {
		v = 0x30;
		if (phy->radio_rev <= 5) {
			reg = 0x43;
			padmix = 0;
		} else {
			reg = 0x52;
			padmix = 5;
		}
	} else {
		if (phy->rev >= 2 && phy->radio_rev == 8) {
			reg = 0x43;
			v = 0x10;
			padmix = 2;
		} else {
			reg = 0x52;
			v = 0x30;
			padmix = 5;
		}
	}
	if (value)
		*value = v;
	if (pad_mix_gain)
		*pad_mix_gain = padmix;

	return reg;
}