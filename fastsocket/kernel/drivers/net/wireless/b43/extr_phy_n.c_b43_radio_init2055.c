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
struct b43_wldev {int /*<<< orphan*/  wl; } ;

/* Variables and functions */
 scalar_t__ B43_STAT_INITIALIZED ; 
 scalar_t__ IEEE80211_BAND_5GHZ ; 
 int /*<<< orphan*/  b2055_upload_inittab (struct b43_wldev*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ b43_current_band (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  b43_radio_init2055_post (struct b43_wldev*) ; 
 int /*<<< orphan*/  b43_radio_init2055_pre (struct b43_wldev*) ; 
 scalar_t__ b43_status (struct b43_wldev*) ; 

__attribute__((used)) static void b43_radio_init2055(struct b43_wldev *dev)
{
	b43_radio_init2055_pre(dev);
	if (b43_status(dev) < B43_STAT_INITIALIZED) {
		/* Follow wl, not specs. Do not force uploading all regs */
		b2055_upload_inittab(dev, 0, 0);
	} else {
		bool ghz5 = b43_current_band(dev->wl) == IEEE80211_BAND_5GHZ;
		b2055_upload_inittab(dev, ghz5, 0);
	}
	b43_radio_init2055_post(dev);
}