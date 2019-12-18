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
typedef  scalar_t__ u8 ;
struct b43_phy {scalar_t__ type; int radio_ver; scalar_t__ analog; int radio_rev; int /*<<< orphan*/  gmode; struct b43_phy_g* g; } ;
struct b43_wldev {int /*<<< orphan*/  wl; TYPE_1__* dev; struct b43_phy phy; } ;
struct b43_rfatt {int att; int with_padmix; } ;
struct b43_phy_g {scalar_t__ cur_idle_tssi; scalar_t__ tgt_idle_tssi; scalar_t__ tx_control; int /*<<< orphan*/  bbatt; int /*<<< orphan*/  rfatt; } ;
struct b43_bbatt {int att; int with_padmix; } ;
typedef  int /*<<< orphan*/  old_rfatt ;
typedef  int /*<<< orphan*/  old_bbatt ;
struct TYPE_2__ {scalar_t__ board_vendor; scalar_t__ board_type; } ;

/* Variables and functions */
 scalar_t__ B43_DEBUG ; 
 int /*<<< orphan*/  B43_MMIO_PHY0 ; 
 scalar_t__ B43_PHYTYPE_G ; 
 int /*<<< orphan*/  B43_PHY_ITSSI ; 
 int /*<<< orphan*/  B43_WARN_ON (int) ; 
 scalar_t__ SSB_BOARDVENDOR_BCM ; 
 scalar_t__ SSB_BOARD_BU4306 ; 
 int abs (scalar_t__) ; 
 int /*<<< orphan*/  b43_dummy_transmission (struct b43_wldev*,int,int) ; 
 int /*<<< orphan*/  b43_hardware_pctl_early_init (struct b43_wldev*) ; 
 int /*<<< orphan*/  b43_hardware_pctl_init_gphy (struct b43_wldev*) ; 
 scalar_t__ b43_phy_read (struct b43_wldev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  b43_phy_write (struct b43_wldev*,int,int) ; 
 int /*<<< orphan*/  b43_radio_mask (struct b43_wldev*,int,int) ; 
 int /*<<< orphan*/  b43_radio_maskset (struct b43_wldev*,int,int,int) ; 
 int b43_read16 (struct b43_wldev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  b43_set_txpower_g (struct b43_wldev*,struct b43_rfatt*,struct b43_rfatt*,scalar_t__) ; 
 int /*<<< orphan*/  b43_shm_clear_tssi (struct b43_wldev*) ; 
 int /*<<< orphan*/  b43_write16 (struct b43_wldev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  b43dbg (int /*<<< orphan*/ ,char*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  memcpy (struct b43_rfatt*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void b43_phy_init_pctl(struct b43_wldev *dev)
{
	struct b43_phy *phy = &dev->phy;
	struct b43_phy_g *gphy = phy->g;
	struct b43_rfatt old_rfatt;
	struct b43_bbatt old_bbatt;
	u8 old_tx_control = 0;

	B43_WARN_ON(phy->type != B43_PHYTYPE_G);

	if ((dev->dev->board_vendor == SSB_BOARDVENDOR_BCM) &&
	    (dev->dev->board_type == SSB_BOARD_BU4306))
		return;

	b43_phy_write(dev, 0x0028, 0x8018);

	/* This does something with the Analog... */
	b43_write16(dev, B43_MMIO_PHY0, b43_read16(dev, B43_MMIO_PHY0)
		    & 0xFFDF);

	if (!phy->gmode)
		return;
	b43_hardware_pctl_early_init(dev);
	if (gphy->cur_idle_tssi == 0) {
		if (phy->radio_ver == 0x2050 && phy->analog == 0) {
			b43_radio_maskset(dev, 0x0076, 0x00F7, 0x0084);
		} else {
			struct b43_rfatt rfatt;
			struct b43_bbatt bbatt;

			memcpy(&old_rfatt, &gphy->rfatt, sizeof(old_rfatt));
			memcpy(&old_bbatt, &gphy->bbatt, sizeof(old_bbatt));
			old_tx_control = gphy->tx_control;

			bbatt.att = 11;
			if (phy->radio_rev == 8) {
				rfatt.att = 15;
				rfatt.with_padmix = true;
			} else {
				rfatt.att = 9;
				rfatt.with_padmix = false;
			}
			b43_set_txpower_g(dev, &bbatt, &rfatt, 0);
		}
		b43_dummy_transmission(dev, false, true);
		gphy->cur_idle_tssi = b43_phy_read(dev, B43_PHY_ITSSI);
		if (B43_DEBUG) {
			/* Current-Idle-TSSI sanity check. */
			if (abs(gphy->cur_idle_tssi - gphy->tgt_idle_tssi) >= 20) {
				b43dbg(dev->wl,
				       "!WARNING! Idle-TSSI phy->cur_idle_tssi "
				       "measuring failed. (cur=%d, tgt=%d). Disabling TX power "
				       "adjustment.\n", gphy->cur_idle_tssi,
				       gphy->tgt_idle_tssi);
				gphy->cur_idle_tssi = 0;
			}
		}
		if (phy->radio_ver == 0x2050 && phy->analog == 0) {
			b43_radio_mask(dev, 0x0076, 0xFF7B);
		} else {
			b43_set_txpower_g(dev, &old_bbatt,
					  &old_rfatt, old_tx_control);
		}
	}
	b43_hardware_pctl_init_gphy(dev);
	b43_shm_clear_tssi(dev);
}