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
struct b43legacy_phy {int type; } ;
struct b43legacy_wldev {struct b43legacy_phy phy; } ;

/* Variables and functions */
#define  B43legacy_PHYTYPE_B 129 
#define  B43legacy_PHYTYPE_G 128 
 int /*<<< orphan*/  B43legacy_SHM_SHARED ; 
 int /*<<< orphan*/  b43legacy_shm_write16 (struct b43legacy_wldev*,int /*<<< orphan*/ ,int,int) ; 

void b43legacy_radio_clear_tssi(struct b43legacy_wldev *dev)
{
	struct b43legacy_phy *phy = &dev->phy;

	switch (phy->type) {
	case B43legacy_PHYTYPE_B:
	case B43legacy_PHYTYPE_G:
		b43legacy_shm_write16(dev, B43legacy_SHM_SHARED, 0x0058,
				      0x7F7F);
		b43legacy_shm_write16(dev, B43legacy_SHM_SHARED, 0x005a,
				      0x7F7F);
		b43legacy_shm_write16(dev, B43legacy_SHM_SHARED, 0x0070,
				      0x7F7F);
		b43legacy_shm_write16(dev, B43legacy_SHM_SHARED, 0x0072,
				      0x7F7F);
		break;
	}
}