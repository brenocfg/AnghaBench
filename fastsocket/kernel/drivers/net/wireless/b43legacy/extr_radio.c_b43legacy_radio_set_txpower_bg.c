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
struct b43legacy_phy {int bbatt; int rfatt; int txctl1; int radio_rev; int radio_ver; scalar_t__ type; } ;
struct b43legacy_wldev {struct b43legacy_phy phy; } ;

/* Variables and functions */
 scalar_t__ B43legacy_PHYTYPE_G ; 
 int /*<<< orphan*/  B43legacy_SHM_SHARED ; 
 int /*<<< orphan*/  B43legacy_WARN_ON (int) ; 
 int /*<<< orphan*/  b43legacy_phy_lo_adjust (struct b43legacy_wldev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  b43legacy_phy_set_baseband_attenuation (struct b43legacy_wldev*,int) ; 
 int b43legacy_radio_read16 (struct b43legacy_wldev*,int) ; 
 int /*<<< orphan*/  b43legacy_radio_write16 (struct b43legacy_wldev*,int,int) ; 
 int /*<<< orphan*/  b43legacy_shm_write16 (struct b43legacy_wldev*,int /*<<< orphan*/ ,int,int) ; 

void b43legacy_radio_set_txpower_bg(struct b43legacy_wldev *dev,
				    u16 baseband_attenuation,
				    u16 radio_attenuation,
				    u16 txpower)
{
	struct b43legacy_phy *phy = &dev->phy;

	if (baseband_attenuation == 0xFFFF)
		baseband_attenuation = phy->bbatt;
	if (radio_attenuation == 0xFFFF)
		radio_attenuation = phy->rfatt;
	if (txpower == 0xFFFF)
		txpower = phy->txctl1;
	phy->bbatt = baseband_attenuation;
	phy->rfatt = radio_attenuation;
	phy->txctl1 = txpower;

	B43legacy_WARN_ON(baseband_attenuation > 11);
	if (phy->radio_rev < 6)
		B43legacy_WARN_ON(radio_attenuation > 9);
	else
		B43legacy_WARN_ON(radio_attenuation > 31);
	B43legacy_WARN_ON(txpower > 7);

	b43legacy_phy_set_baseband_attenuation(dev, baseband_attenuation);
	b43legacy_radio_write16(dev, 0x0043, radio_attenuation);
	b43legacy_shm_write16(dev, B43legacy_SHM_SHARED, 0x0064,
			      radio_attenuation);
	if (phy->radio_ver == 0x2050)
		b43legacy_radio_write16(dev, 0x0052,
					(b43legacy_radio_read16(dev, 0x0052)
					& ~0x0070) | ((txpower << 4) & 0x0070));
	/* FIXME: The spec is very weird and unclear here. */
	if (phy->type == B43legacy_PHYTYPE_G)
		b43legacy_phy_lo_adjust(dev, 0);
}