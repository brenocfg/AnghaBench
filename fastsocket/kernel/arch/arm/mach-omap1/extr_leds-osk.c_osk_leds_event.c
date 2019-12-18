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
typedef  int /*<<< orphan*/  u16 ;
typedef  int led_event_t ;

/* Variables and functions */
 int /*<<< orphan*/  IDLE_LED ; 
 int LED_STATE_CLAIMED ; 
 int LED_STATE_ENABLED ; 
 int /*<<< orphan*/  TIMER_LED ; 
 int /*<<< orphan*/  hw_led_state ; 
#define  led_claim 135 
#define  led_halted 134 
#define  led_idle_end 133 
#define  led_idle_start 132 
#define  led_release 131 
#define  led_start 130 
 int led_state ; 
#define  led_stop 129 
#define  led_timer 128 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 
 int /*<<< orphan*/  mistral_setled () ; 

void osk_leds_event(led_event_t evt)
{
	unsigned long	flags;
	u16		leds;

	local_irq_save(flags);

	if (!(led_state & LED_STATE_ENABLED) && evt != led_start)
		goto done;

	leds = hw_led_state;
	switch (evt) {
	case led_start:
		led_state |= LED_STATE_ENABLED;
		hw_led_state = 0;
		leds = ~0;
		break;

	case led_halted:
	case led_stop:
		led_state &= ~LED_STATE_ENABLED;
		hw_led_state = 0;
		break;

	case led_claim:
		led_state |= LED_STATE_CLAIMED;
		hw_led_state = 0;
		leds = ~0;
		break;

	case led_release:
		led_state &= ~LED_STATE_CLAIMED;
		hw_led_state = 0;
		break;

#ifdef	CONFIG_OMAP_OSK_MISTRAL

	case led_timer:
		hw_led_state ^= TIMER_LED;
		mistral_setled();
		break;

	case led_idle_start:	/* idle == off */
		hw_led_state &= ~IDLE_LED;
		mistral_setled();
		break;

	case led_idle_end:
		hw_led_state |= IDLE_LED;
		mistral_setled();
		break;

#endif	/* CONFIG_OMAP_OSK_MISTRAL */

	default:
		break;
	}

	leds ^= hw_led_state;

done:
	local_irq_restore(flags);
}