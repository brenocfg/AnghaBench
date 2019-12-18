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
typedef  int /*<<< orphan*/  u_char ;
struct st5481_adapter {int led_counter; int /*<<< orphan*/  leds; } ;

/* Variables and functions */
 int /*<<< orphan*/  GPIO_OUT ; 
 int /*<<< orphan*/  GREEN_LED ; 
 int /*<<< orphan*/  st5481_usb_device_ctrl_msg (struct st5481_adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void led_blink(struct st5481_adapter *adapter)
{
	u_char leds = adapter->leds;

	// 50 frames/sec for each channel
	if (++adapter->led_counter % 50) {
		return;
	}

	if (adapter->led_counter % 100) {
		leds |= GREEN_LED;
	} else {
		leds &= ~GREEN_LED;
	}
	
	st5481_usb_device_ctrl_msg(adapter, GPIO_OUT, leds, NULL, NULL);
}