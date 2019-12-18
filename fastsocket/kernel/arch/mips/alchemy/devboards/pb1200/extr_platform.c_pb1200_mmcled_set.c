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
struct led_classdev {int dummy; } ;
typedef  enum led_brightness { ____Placeholder_led_brightness } led_brightness ;
struct TYPE_2__ {int disk_leds; } ;

/* Variables and functions */
 int LED_OFF ; 
 TYPE_1__* bcsr ; 
 int mmc_activity ; 

__attribute__((used)) static void pb1200_mmcled_set(struct led_classdev *led,
			enum led_brightness brightness)
{
	if (brightness != LED_OFF) {
		if (++mmc_activity == 1)
			bcsr->disk_leds &= ~(1 << 8);
	} else {
		if (--mmc_activity == 0)
			bcsr->disk_leds |= (1 << 8);
	}
}