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
typedef  int u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct rt2x00_dev {scalar_t__ curr_band; int /*<<< orphan*/  intf_associated; int /*<<< orphan*/  cap_flags; } ;
struct link_qual {int rssi; int vgc_level; int false_cca; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAPABILITY_EXTERNAL_LNA_A ; 
 int /*<<< orphan*/  CAPABILITY_EXTERNAL_LNA_BG ; 
 scalar_t__ IEEE80211_BAND_5GHZ ; 
 int /*<<< orphan*/  rt61pci_set_vgc (struct rt2x00_dev*,struct link_qual*,int) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void rt61pci_link_tuner(struct rt2x00_dev *rt2x00dev,
			       struct link_qual *qual, const u32 count)
{
	u8 up_bound;
	u8 low_bound;

	/*
	 * Determine r17 bounds.
	 */
	if (rt2x00dev->curr_band == IEEE80211_BAND_5GHZ) {
		low_bound = 0x28;
		up_bound = 0x48;
		if (test_bit(CAPABILITY_EXTERNAL_LNA_A, &rt2x00dev->cap_flags)) {
			low_bound += 0x10;
			up_bound += 0x10;
		}
	} else {
		low_bound = 0x20;
		up_bound = 0x40;
		if (test_bit(CAPABILITY_EXTERNAL_LNA_BG, &rt2x00dev->cap_flags)) {
			low_bound += 0x10;
			up_bound += 0x10;
		}
	}

	/*
	 * If we are not associated, we should go straight to the
	 * dynamic CCA tuning.
	 */
	if (!rt2x00dev->intf_associated)
		goto dynamic_cca_tune;

	/*
	 * Special big-R17 for very short distance
	 */
	if (qual->rssi >= -35) {
		rt61pci_set_vgc(rt2x00dev, qual, 0x60);
		return;
	}

	/*
	 * Special big-R17 for short distance
	 */
	if (qual->rssi >= -58) {
		rt61pci_set_vgc(rt2x00dev, qual, up_bound);
		return;
	}

	/*
	 * Special big-R17 for middle-short distance
	 */
	if (qual->rssi >= -66) {
		rt61pci_set_vgc(rt2x00dev, qual, low_bound + 0x10);
		return;
	}

	/*
	 * Special mid-R17 for middle distance
	 */
	if (qual->rssi >= -74) {
		rt61pci_set_vgc(rt2x00dev, qual, low_bound + 0x08);
		return;
	}

	/*
	 * Special case: Change up_bound based on the rssi.
	 * Lower up_bound when rssi is weaker then -74 dBm.
	 */
	up_bound -= 2 * (-74 - qual->rssi);
	if (low_bound > up_bound)
		up_bound = low_bound;

	if (qual->vgc_level > up_bound) {
		rt61pci_set_vgc(rt2x00dev, qual, up_bound);
		return;
	}

dynamic_cca_tune:

	/*
	 * r17 does not yet exceed upper limit, continue and base
	 * the r17 tuning on the false CCA count.
	 */
	if ((qual->false_cca > 512) && (qual->vgc_level < up_bound))
		rt61pci_set_vgc(rt2x00dev, qual, ++qual->vgc_level);
	else if ((qual->false_cca < 100) && (qual->vgc_level > low_bound))
		rt61pci_set_vgc(rt2x00dev, qual, --qual->vgc_level);
}