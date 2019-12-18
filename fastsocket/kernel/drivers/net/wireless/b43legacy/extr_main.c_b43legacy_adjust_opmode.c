#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
typedef  int u16 ;
struct b43legacy_wldev {TYPE_3__* dev; struct b43legacy_wl* wl; } ;
struct b43legacy_wl {int filter_flags; } ;
struct TYPE_4__ {int revision; } ;
struct TYPE_6__ {TYPE_2__* bus; TYPE_1__ id; } ;
struct TYPE_5__ {int chip_id; int chip_rev; } ;

/* Variables and functions */
 int B43legacy_MACCTL_AP ; 
 int B43legacy_MACCTL_BEACPROMISC ; 
 int B43legacy_MACCTL_INFRA ; 
 int B43legacy_MACCTL_KEEP_BAD ; 
 int B43legacy_MACCTL_KEEP_BADPLCP ; 
 int B43legacy_MACCTL_KEEP_CTL ; 
 int B43legacy_MACCTL_PROMISC ; 
 int /*<<< orphan*/  B43legacy_MMIO_MACCTL ; 
 int FIF_BCN_PRBRESP_PROMISC ; 
 int FIF_CONTROL ; 
 int FIF_FCSFAIL ; 
 int FIF_PLCPFAIL ; 
 int FIF_PROMISC_IN_BSS ; 
 int /*<<< orphan*/  NL80211_IFTYPE_ADHOC ; 
 int /*<<< orphan*/  NL80211_IFTYPE_AP ; 
 scalar_t__ b43legacy_is_mode (struct b43legacy_wl*,int /*<<< orphan*/ ) ; 
 int b43legacy_read32 (struct b43legacy_wldev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  b43legacy_write16 (struct b43legacy_wldev*,int,int) ; 
 int /*<<< orphan*/  b43legacy_write32 (struct b43legacy_wldev*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void b43legacy_adjust_opmode(struct b43legacy_wldev *dev)
{
	struct b43legacy_wl *wl = dev->wl;
	u32 ctl;
	u16 cfp_pretbtt;

	ctl = b43legacy_read32(dev, B43legacy_MMIO_MACCTL);
	/* Reset status to STA infrastructure mode. */
	ctl &= ~B43legacy_MACCTL_AP;
	ctl &= ~B43legacy_MACCTL_KEEP_CTL;
	ctl &= ~B43legacy_MACCTL_KEEP_BADPLCP;
	ctl &= ~B43legacy_MACCTL_KEEP_BAD;
	ctl &= ~B43legacy_MACCTL_PROMISC;
	ctl &= ~B43legacy_MACCTL_BEACPROMISC;
	ctl |= B43legacy_MACCTL_INFRA;

	if (b43legacy_is_mode(wl, NL80211_IFTYPE_AP))
		ctl |= B43legacy_MACCTL_AP;
	else if (b43legacy_is_mode(wl, NL80211_IFTYPE_ADHOC))
		ctl &= ~B43legacy_MACCTL_INFRA;

	if (wl->filter_flags & FIF_CONTROL)
		ctl |= B43legacy_MACCTL_KEEP_CTL;
	if (wl->filter_flags & FIF_FCSFAIL)
		ctl |= B43legacy_MACCTL_KEEP_BAD;
	if (wl->filter_flags & FIF_PLCPFAIL)
		ctl |= B43legacy_MACCTL_KEEP_BADPLCP;
	if (wl->filter_flags & FIF_PROMISC_IN_BSS)
		ctl |= B43legacy_MACCTL_PROMISC;
	if (wl->filter_flags & FIF_BCN_PRBRESP_PROMISC)
		ctl |= B43legacy_MACCTL_BEACPROMISC;

	/* Workaround: On old hardware the HW-MAC-address-filter
	 * doesn't work properly, so always run promisc in filter
	 * it in software. */
	if (dev->dev->id.revision <= 4)
		ctl |= B43legacy_MACCTL_PROMISC;

	b43legacy_write32(dev, B43legacy_MMIO_MACCTL, ctl);

	cfp_pretbtt = 2;
	if ((ctl & B43legacy_MACCTL_INFRA) &&
	    !(ctl & B43legacy_MACCTL_AP)) {
		if (dev->dev->bus->chip_id == 0x4306 &&
		    dev->dev->bus->chip_rev == 3)
			cfp_pretbtt = 100;
		else
			cfp_pretbtt = 50;
	}
	b43legacy_write16(dev, 0x612, cfp_pretbtt);
}