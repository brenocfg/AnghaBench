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
typedef  int led_event_t ;

/* Variables and functions */
 int /*<<< orphan*/  LED2_ON ; 
 int /*<<< orphan*/  LED_GREEN ; 
 int LED_STATE_CLAIMED ; 
 int LED_STATE_ENABLED ; 
 int /*<<< orphan*/  clear_cs3_bit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hw_led_state ; 
#define  led_amber_off 141 
#define  led_amber_on 140 
#define  led_claim 139 
#define  led_green_off 138 
#define  led_green_on 137 
#define  led_halted 136 
#define  led_idle_end 135 
#define  led_idle_start 134 
#define  led_red_off 133 
#define  led_red_on 132 
#define  led_release 131 
#define  led_start 130 
 int led_state ; 
#define  led_stop 129 
#define  led_timer 128 
 int /*<<< orphan*/  set_cs3_bit (int /*<<< orphan*/ ) ; 

void simpad_leds_event(led_event_t evt)
{
	switch (evt)
	{
	case led_start:
	        hw_led_state = LED_GREEN;
		led_state = LED_STATE_ENABLED;
		break;

	case led_stop:
		led_state &= ~LED_STATE_ENABLED;
		break;

	case led_claim:
		led_state |= LED_STATE_CLAIMED;
		hw_led_state = LED_GREEN;
		break;

	case led_release:
		led_state &= ~LED_STATE_CLAIMED;
		hw_led_state = LED_GREEN;
		break;

#ifdef CONFIG_LEDS_TIMER
	case led_timer:
		if (!(led_state & LED_STATE_CLAIMED))
			hw_led_state ^= LED_GREEN;
		break;
#endif

#ifdef CONFIG_LEDS_CPU
	case led_idle_start:
		break;

	case led_idle_end:
		break;
#endif

	case led_halted:
		break;

	case led_green_on:
		if (led_state & LED_STATE_CLAIMED)
			hw_led_state |= LED_GREEN;
		break;

	case led_green_off:
		if (led_state & LED_STATE_CLAIMED)
			hw_led_state &= ~LED_GREEN;
		break;

	case led_amber_on:
		break;

	case led_amber_off:
		break;

	case led_red_on:
		break;

	case led_red_off:
		break;

	default:
		break;
	}

	if  (led_state & LED_STATE_ENABLED)
		set_cs3_bit(LED2_ON);
	else 
	        clear_cs3_bit(LED2_ON);
}