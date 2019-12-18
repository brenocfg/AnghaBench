#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u16 ;
struct b43legacy_phy {int radio_ver; int /*<<< orphan*/  type; int /*<<< orphan*/  radio_rev; } ;
struct b43legacy_wldev {TYPE_4__* dev; struct b43legacy_phy phy; } ;
struct TYPE_8__ {TYPE_3__* bus; } ;
struct TYPE_6__ {int board_rev; } ;
struct TYPE_5__ {int type; } ;
struct TYPE_7__ {int chip_id; TYPE_2__ sprom; TYPE_1__ boardinfo; } ;

/* Variables and functions */
 int /*<<< orphan*/  B43legacy_PHYTYPE_G ; 
 scalar_t__ is_bcm_board_vendor (struct b43legacy_wldev*) ; 

u16 b43legacy_default_radio_attenuation(struct b43legacy_wldev *dev)
{
	struct b43legacy_phy *phy = &dev->phy;
	u16 att = 0xFFFF;

	switch (phy->radio_ver) {
	case 0x2053:
		switch (phy->radio_rev) {
		case 1:
			att = 6;
			break;
		}
		break;
	case 0x2050:
		switch (phy->radio_rev) {
		case 0:
			att = 5;
			break;
		case 1:
			if (phy->type == B43legacy_PHYTYPE_G) {
				if (is_bcm_board_vendor(dev) &&
				    dev->dev->bus->boardinfo.type == 0x421 &&
				    dev->dev->bus->sprom.board_rev >= 30)
					att = 3;
				else if (is_bcm_board_vendor(dev) &&
					 dev->dev->bus->boardinfo.type == 0x416)
					att = 3;
				else
					att = 1;
			} else {
				if (is_bcm_board_vendor(dev) &&
				    dev->dev->bus->boardinfo.type == 0x421 &&
				    dev->dev->bus->sprom.board_rev >= 30)
					att = 7;
				else
					att = 6;
			}
			break;
		case 2:
			if (phy->type == B43legacy_PHYTYPE_G) {
				if (is_bcm_board_vendor(dev) &&
				    dev->dev->bus->boardinfo.type == 0x421 &&
				    dev->dev->bus->sprom.board_rev >= 30)
					att = 3;
				else if (is_bcm_board_vendor(dev) &&
					 dev->dev->bus->boardinfo.type ==
					 0x416)
					att = 5;
				else if (dev->dev->bus->chip_id == 0x4320)
					att = 4;
				else
					att = 3;
			} else
				att = 6;
			break;
		case 3:
			att = 5;
			break;
		case 4:
		case 5:
			att = 1;
			break;
		case 6:
		case 7:
			att = 5;
			break;
		case 8:
			att = 0x1A;
			break;
		case 9:
		default:
			att = 5;
		}
	}
	if (is_bcm_board_vendor(dev) &&
	    dev->dev->bus->boardinfo.type == 0x421) {
		if (dev->dev->bus->sprom.board_rev < 0x43)
			att = 2;
		else if (dev->dev->bus->sprom.board_rev < 0x51)
			att = 3;
	}
	if (att == 0xFFFF)
		att = 5;

	return att;
}