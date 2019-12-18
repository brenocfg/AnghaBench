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
typedef  scalar_t__ u16 ;
struct b43_wldev {int /*<<< orphan*/  wl; } ;

/* Variables and functions */
 int /*<<< orphan*/  B43_MMIO_IFSSLOT ; 
 scalar_t__ IEEE80211_BAND_5GHZ ; 
 scalar_t__ b43_current_band (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  b43_write16 (struct b43_wldev*,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void b43_set_slot_time(struct b43_wldev *dev, u16 slot_time)
{
	/* slot_time is in usec. */
	/* This test used to exit for all but a G PHY. */
	if (b43_current_band(dev->wl) == IEEE80211_BAND_5GHZ)
		return;
	b43_write16(dev, B43_MMIO_IFSSLOT, 510 + slot_time);
	/* Shared memory location 0x0010 is the slot time and should be
	 * set to slot_time; however, this register is initially 0 and changing
	 * the value adversely affects the transmit rate for BCM4311
	 * devices. Until this behavior is unterstood, delete this step
	 *
	 * b43_shm_write16(dev, B43_SHM_SHARED, 0x0010, slot_time);
	 */
}