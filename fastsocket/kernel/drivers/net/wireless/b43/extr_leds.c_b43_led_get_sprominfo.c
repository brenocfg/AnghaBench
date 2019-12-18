#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct b43_wldev {TYPE_2__* dev; } ;
typedef  enum b43_led_behaviour { ____Placeholder_b43_led_behaviour } b43_led_behaviour ;
struct TYPE_4__ {int /*<<< orphan*/  board_vendor; TYPE_1__* bus_sprom; } ;
struct TYPE_3__ {int gpio0; int gpio1; int gpio2; int gpio3; } ;

/* Variables and functions */
 int B43_LED_ACTIVELOW ; 
 int B43_LED_ACTIVITY ; 
 int B43_LED_ASSOC ; 
 int B43_LED_BEHAVIOUR ; 
 int B43_LED_OFF ; 
 int B43_LED_RADIO_A ; 
 int B43_LED_RADIO_ALL ; 
 int B43_LED_RADIO_B ; 
 int /*<<< orphan*/  B43_WARN_ON (int) ; 
 int /*<<< orphan*/  PCI_VENDOR_ID_ASUSTEK ; 
 int /*<<< orphan*/  PCI_VENDOR_ID_COMPAQ ; 

__attribute__((used)) static void b43_led_get_sprominfo(struct b43_wldev *dev,
				  unsigned int led_index,
				  enum b43_led_behaviour *behaviour,
				  bool *activelow)
{
	u8 sprom[4];

	sprom[0] = dev->dev->bus_sprom->gpio0;
	sprom[1] = dev->dev->bus_sprom->gpio1;
	sprom[2] = dev->dev->bus_sprom->gpio2;
	sprom[3] = dev->dev->bus_sprom->gpio3;

	if (sprom[led_index] == 0xFF) {
		/* There is no LED information in the SPROM
		 * for this LED. Hardcode it here. */
		*activelow = false;
		switch (led_index) {
		case 0:
			*behaviour = B43_LED_ACTIVITY;
			*activelow = true;
			if (dev->dev->board_vendor == PCI_VENDOR_ID_COMPAQ)
				*behaviour = B43_LED_RADIO_ALL;
			break;
		case 1:
			*behaviour = B43_LED_RADIO_B;
			if (dev->dev->board_vendor == PCI_VENDOR_ID_ASUSTEK)
				*behaviour = B43_LED_ASSOC;
			break;
		case 2:
			*behaviour = B43_LED_RADIO_A;
			break;
		case 3:
			*behaviour = B43_LED_OFF;
			break;
		default:
			*behaviour = B43_LED_OFF;
			B43_WARN_ON(1);
			return;
		}
	} else {
		*behaviour = sprom[led_index] & B43_LED_BEHAVIOUR;
		*activelow = !!(sprom[led_index] & B43_LED_ACTIVELOW);
	}
}