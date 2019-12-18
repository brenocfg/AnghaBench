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
 int D21 ; 
 int D22 ; 
 int D23 ; 
 int D26 ; 
 int D27 ; 
 int LED_STATE_CLAIMED ; 
 int LED_STATE_ENABLED ; 
 int LUB_DISC_BLNK_LED ; 
 int hw_led_state ; 
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
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 

void lubbock_leds_event(led_event_t evt)
{
	unsigned long flags;

	local_irq_save(flags);

	switch (evt) {
	case led_start:
		hw_led_state = 0;
		led_state = LED_STATE_ENABLED;
		break;

	case led_stop:
		led_state &= ~LED_STATE_ENABLED;
		break;

	case led_claim:
		led_state |= LED_STATE_CLAIMED;
		hw_led_state = 0;
		break;

	case led_release:
		led_state &= ~LED_STATE_CLAIMED;
		hw_led_state = 0;
		break;

#ifdef CONFIG_LEDS_TIMER
	case led_timer:
		hw_led_state ^= D26;
		break;
#endif

#ifdef CONFIG_LEDS_CPU
	case led_idle_start:
		hw_led_state &= ~D27;
		break;

	case led_idle_end:
		hw_led_state |= D27;
		break;
#endif

	case led_halted:
		break;

	case led_green_on:
		hw_led_state |= D21;
		break;

	case led_green_off:
		hw_led_state &= ~D21;
		break;

	case led_amber_on:
		hw_led_state |= D22;
		break;

	case led_amber_off:
		hw_led_state &= ~D22;
		break;

	case led_red_on:
		hw_led_state |= D23;
		break;

	case led_red_off:
		hw_led_state &= ~D23;
		break;

	default:
		break;
	}

	if  (led_state & LED_STATE_ENABLED)
		LUB_DISC_BLNK_LED = (LUB_DISC_BLNK_LED | 0xff) & ~hw_led_state;
	else
		LUB_DISC_BLNK_LED |= 0xff;

	local_irq_restore(flags);
}