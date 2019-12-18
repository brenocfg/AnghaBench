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
typedef  scalar_t__ u16 ;
struct TYPE_2__ {scalar_t__ type; } ;
struct b43legacy_wldev {TYPE_1__ phy; } ;

/* Variables and functions */
 scalar_t__ B43legacy_PHYTYPE_G ; 
 int /*<<< orphan*/  B43legacy_SHM_SHARED ; 
 int /*<<< orphan*/  b43legacy_shm_write16 (struct b43legacy_wldev*,int /*<<< orphan*/ ,int,scalar_t__) ; 
 int /*<<< orphan*/  b43legacy_write16 (struct b43legacy_wldev*,int,scalar_t__) ; 

__attribute__((used)) static void b43legacy_set_slot_time(struct b43legacy_wldev *dev,
				    u16 slot_time)
{
	/* slot_time is in usec. */
	if (dev->phy.type != B43legacy_PHYTYPE_G)
		return;
	b43legacy_write16(dev, 0x684, 510 + slot_time);
	b43legacy_shm_write16(dev, B43legacy_SHM_SHARED, 0x0010,
			      slot_time);
}