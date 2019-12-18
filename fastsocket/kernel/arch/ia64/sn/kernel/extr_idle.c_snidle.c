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
struct TYPE_2__ {int idle_flag; } ;

/* Variables and functions */
 int /*<<< orphan*/  LED_CPU_ACTIVITY ; 
 TYPE_1__* pda ; 
 int /*<<< orphan*/  set_led_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void snidle(int state)
{
	if (state) {
		if (pda->idle_flag == 0) {
			/* 
			 * Turn the activity LED off.
			 */
			set_led_bits(0, LED_CPU_ACTIVITY);
		}

		pda->idle_flag = 1;
	} else {
		/* 
		 * Turn the activity LED on.
		 */
		set_led_bits(LED_CPU_ACTIVITY, LED_CPU_ACTIVITY);

		pda->idle_flag = 0;
	}
}