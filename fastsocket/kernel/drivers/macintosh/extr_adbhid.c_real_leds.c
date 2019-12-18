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

/* Variables and functions */
 int /*<<< orphan*/  ADB_WRITEREG (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  KEYB_LEDREG ; 
 int /*<<< orphan*/  adb_request (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,unsigned char) ; 
 int /*<<< orphan*/  led_request ; 
 int /*<<< orphan*/  leds_done ; 
 int /*<<< orphan*/  leds_lock ; 
 int* leds_pending ; 
 int leds_req_pending ; 
 int* pending_devs ; 
 size_t pending_led_end ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void real_leds(unsigned char leds, int device)
{
	unsigned long flags;

	spin_lock_irqsave(&leds_lock, flags);
	if (!leds_req_pending) {
		leds_req_pending = 1;
		spin_unlock_irqrestore(&leds_lock, flags);	       
		adb_request(&led_request, leds_done, 0, 3,
			    ADB_WRITEREG(device, KEYB_LEDREG), 0xff, ~leds);
		return;
	} else {
		if (!(leds_pending[device] & 0x100)) {
			pending_devs[pending_led_end] = device;
			pending_led_end++;
			pending_led_end = (pending_led_end < 16) ? pending_led_end : 0;
		}
		leds_pending[device] = leds | 0x100;
	}
	spin_unlock_irqrestore(&leds_lock, flags);	       
}