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
struct b43legacy_phy {scalar_t__ type; scalar_t__ rev; int aci_wlan_automatic; int aci_enable; int interfmode; int aci_hw_rssi; int /*<<< orphan*/  gmode; } ;
struct b43legacy_wldev {struct b43legacy_phy phy; } ;

/* Variables and functions */
 scalar_t__ B43legacy_PHYTYPE_G ; 
#define  B43legacy_RADIO_INTERFMODE_AUTOWLAN 131 
#define  B43legacy_RADIO_INTERFMODE_MANUALWLAN 130 
#define  B43legacy_RADIO_INTERFMODE_NONE 129 
#define  B43legacy_RADIO_INTERFMODE_NONWLAN 128 
 int EINVAL ; 
 int ENODEV ; 
 int /*<<< orphan*/  b43legacy_radio_interference_mitigation_disable (struct b43legacy_wldev*,int) ; 
 int /*<<< orphan*/  b43legacy_radio_interference_mitigation_enable (struct b43legacy_wldev*,int) ; 

int b43legacy_radio_set_interference_mitigation(struct b43legacy_wldev *dev,
						int mode)
{
	struct b43legacy_phy *phy = &dev->phy;
	int currentmode;

	if ((phy->type != B43legacy_PHYTYPE_G) ||
	    (phy->rev == 0) || (!phy->gmode))
		return -ENODEV;

	phy->aci_wlan_automatic = false;
	switch (mode) {
	case B43legacy_RADIO_INTERFMODE_AUTOWLAN:
		phy->aci_wlan_automatic = true;
		if (phy->aci_enable)
			mode = B43legacy_RADIO_INTERFMODE_MANUALWLAN;
		else
			mode = B43legacy_RADIO_INTERFMODE_NONE;
		break;
	case B43legacy_RADIO_INTERFMODE_NONE:
	case B43legacy_RADIO_INTERFMODE_NONWLAN:
	case B43legacy_RADIO_INTERFMODE_MANUALWLAN:
		break;
	default:
		return -EINVAL;
	}

	currentmode = phy->interfmode;
	if (currentmode == mode)
		return 0;
	if (currentmode != B43legacy_RADIO_INTERFMODE_NONE)
		b43legacy_radio_interference_mitigation_disable(dev,
								currentmode);

	if (mode == B43legacy_RADIO_INTERFMODE_NONE) {
		phy->aci_enable = false;
		phy->aci_hw_rssi = false;
	} else
		b43legacy_radio_interference_mitigation_enable(dev, mode);
	phy->interfmode = mode;

	return 0;
}