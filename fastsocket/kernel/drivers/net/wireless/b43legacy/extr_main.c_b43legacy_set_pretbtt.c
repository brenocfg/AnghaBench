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
struct b43legacy_wldev {int /*<<< orphan*/  wl; } ;

/* Variables and functions */
 int /*<<< orphan*/  B43legacy_MMIO_TSF_CFP_PRETBTT ; 
 int /*<<< orphan*/  B43legacy_SHM_SHARED ; 
 int /*<<< orphan*/  B43legacy_SHM_SH_PRETBTT ; 
 int /*<<< orphan*/  NL80211_IFTYPE_ADHOC ; 
 scalar_t__ b43legacy_is_mode (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  b43legacy_shm_write16 (struct b43legacy_wldev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  b43legacy_write16 (struct b43legacy_wldev*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void b43legacy_set_pretbtt(struct b43legacy_wldev *dev)
{
	u16 pretbtt;

	/* The time value is in microseconds. */
	if (b43legacy_is_mode(dev->wl, NL80211_IFTYPE_ADHOC))
		pretbtt = 2;
	else
		pretbtt = 250;
	b43legacy_shm_write16(dev, B43legacy_SHM_SHARED,
			      B43legacy_SHM_SH_PRETBTT, pretbtt);
	b43legacy_write16(dev, B43legacy_MMIO_TSF_CFP_PRETBTT, pretbtt);
}