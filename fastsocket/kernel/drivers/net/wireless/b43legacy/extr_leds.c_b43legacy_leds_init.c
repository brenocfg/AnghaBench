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
typedef  int u8 ;
struct TYPE_6__ {int /*<<< orphan*/  vendor; } ;
struct TYPE_5__ {int gpio0; int gpio1; int gpio2; int gpio3; } ;
struct ssb_bus {TYPE_3__ boardinfo; TYPE_2__ sprom; } ;
struct b43legacy_wldev {TYPE_1__* dev; } ;
typedef  enum b43legacy_led_behaviour { ____Placeholder_b43legacy_led_behaviour } b43legacy_led_behaviour ;
struct TYPE_4__ {struct ssb_bus* bus; } ;

/* Variables and functions */
 int B43legacy_LED_ACTIVELOW ; 
 int B43legacy_LED_ACTIVITY ; 
 int B43legacy_LED_ASSOC ; 
 int B43legacy_LED_BEHAVIOUR ; 
 int B43legacy_LED_OFF ; 
 int B43legacy_LED_RADIO_A ; 
 int B43legacy_LED_RADIO_ALL ; 
 int B43legacy_LED_RADIO_B ; 
 int /*<<< orphan*/  B43legacy_WARN_ON (int) ; 
 int /*<<< orphan*/  PCI_VENDOR_ID_ASUSTEK ; 
 int /*<<< orphan*/  PCI_VENDOR_ID_COMPAQ ; 
 int /*<<< orphan*/  b43legacy_map_led (struct b43legacy_wldev*,int,int,int) ; 

void b43legacy_leds_init(struct b43legacy_wldev *dev)
{
	struct ssb_bus *bus = dev->dev->bus;
	u8 sprom[4];
	int i;
	enum b43legacy_led_behaviour behaviour;
	bool activelow;

	sprom[0] = bus->sprom.gpio0;
	sprom[1] = bus->sprom.gpio1;
	sprom[2] = bus->sprom.gpio2;
	sprom[3] = bus->sprom.gpio3;

	for (i = 0; i < 4; i++) {
		if (sprom[i] == 0xFF) {
			/* There is no LED information in the SPROM
			 * for this LED. Hardcode it here. */
			activelow = false;
			switch (i) {
			case 0:
				behaviour = B43legacy_LED_ACTIVITY;
				activelow = true;
				if (bus->boardinfo.vendor == PCI_VENDOR_ID_COMPAQ)
					behaviour = B43legacy_LED_RADIO_ALL;
				break;
			case 1:
				behaviour = B43legacy_LED_RADIO_B;
				if (bus->boardinfo.vendor == PCI_VENDOR_ID_ASUSTEK)
					behaviour = B43legacy_LED_ASSOC;
				break;
			case 2:
				behaviour = B43legacy_LED_RADIO_A;
				break;
			case 3:
				behaviour = B43legacy_LED_OFF;
				break;
			default:
				B43legacy_WARN_ON(1);
				return;
			}
		} else {
			behaviour = sprom[i] & B43legacy_LED_BEHAVIOUR;
			activelow = !!(sprom[i] & B43legacy_LED_ACTIVELOW);
		}
		b43legacy_map_led(dev, i, behaviour, activelow);
	}
}