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
typedef  int /*<<< orphan*/  u16 ;
struct TYPE_2__ {int /*<<< orphan*/  phy_id; } ;
struct nic {scalar_t__ phy; int leds; scalar_t__ mac; int /*<<< orphan*/  blink_timer; TYPE_1__ mii; int /*<<< orphan*/  netdev; } ;

/* Variables and functions */
 int E100_82552_LED_OFF ; 
 int E100_82552_LED_ON ; 
 int /*<<< orphan*/  E100_82552_LED_OVERRIDE ; 
 int HZ ; 
 int /*<<< orphan*/  MII_LED_CONTROL ; 
 scalar_t__ jiffies ; 
 scalar_t__ mac_82559_D101M ; 
 int /*<<< orphan*/  mdio_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ phy_82552_v ; 

__attribute__((used)) static void e100_blink_led(unsigned long data)
{
	struct nic *nic = (struct nic *)data;
	enum led_state {
		led_on     = 0x01,
		led_off    = 0x04,
		led_on_559 = 0x05,
		led_on_557 = 0x07,
	};
	u16 led_reg = MII_LED_CONTROL;

	if (nic->phy == phy_82552_v) {
		led_reg = E100_82552_LED_OVERRIDE;

		nic->leds = (nic->leds == E100_82552_LED_ON) ?
		            E100_82552_LED_OFF : E100_82552_LED_ON;
	} else {
		nic->leds = (nic->leds & led_on) ? led_off :
		            (nic->mac < mac_82559_D101M) ? led_on_557 :
		            led_on_559;
	}
	mdio_write(nic->netdev, nic->mii.phy_id, led_reg, nic->leds);
	mod_timer(&nic->blink_timer, jiffies + HZ / 4);
}