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
 int LED_STATE_CLAIMED ; 
 int LED_STATE_ENABLED ; 
 int /*<<< orphan*/  SEQUOIA_LED_AMBER ; 
 int /*<<< orphan*/  SEQUOIA_LED_BACK ; 
 int /*<<< orphan*/  SEQUOIA_LED_GREEN ; 
 int /*<<< orphan*/  hw_led_state ; 
#define  led_amber_off 140 
#define  led_amber_on 139 
#define  led_claim 138 
#define  led_green_off 137 
#define  led_green_on 136 
#define  led_idle_end 135 
#define  led_idle_start 134 
#define  led_red_off 133 
#define  led_red_on 132 
#define  led_release 131 
#define  led_start 130 
 int led_state ; 
#define  led_stop 129 
#define  led_timer 128 
 int /*<<< orphan*/  leds_lock ; 
 int /*<<< orphan*/  saved_state ; 
 int /*<<< orphan*/  sequoia_read (int) ; 
 int /*<<< orphan*/  sequoia_write (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void sequoia_leds_event(led_event_t evt)
{
	unsigned long flags;

	spin_lock_irqsave(&leds_lock, flags);

	hw_led_state = sequoia_read(0x09);

	switch (evt) {
	case led_start:
		hw_led_state |= SEQUOIA_LED_GREEN;
		hw_led_state |= SEQUOIA_LED_AMBER;
#ifdef CONFIG_LEDS_CPU
		hw_led_state |= SEQUOIA_LED_BACK;
#else
		hw_led_state &= ~SEQUOIA_LED_BACK;
#endif
		led_state |= LED_STATE_ENABLED;
		break;

	case led_stop:
		hw_led_state &= ~SEQUOIA_LED_BACK;
		hw_led_state |= SEQUOIA_LED_GREEN;
		hw_led_state |= SEQUOIA_LED_AMBER;
		led_state &= ~LED_STATE_ENABLED;
		break;

	case led_claim:
		led_state |= LED_STATE_CLAIMED;
		saved_state = hw_led_state;
		hw_led_state &= ~SEQUOIA_LED_BACK;
		hw_led_state |= SEQUOIA_LED_GREEN;
		hw_led_state |= SEQUOIA_LED_AMBER;
		break;

	case led_release:
		led_state &= ~LED_STATE_CLAIMED;
		hw_led_state = saved_state;
		break;

#ifdef CONFIG_LEDS_TIMER
	case led_timer:
		if (!(led_state & LED_STATE_CLAIMED))
			hw_led_state ^= SEQUOIA_LED_GREEN;
		break;
#endif

#ifdef CONFIG_LEDS_CPU
	case led_idle_start:
		if (!(led_state & LED_STATE_CLAIMED))
			hw_led_state &= ~SEQUOIA_LED_BACK;
		break;

	case led_idle_end:
		if (!(led_state & LED_STATE_CLAIMED))
			hw_led_state |= SEQUOIA_LED_BACK;
		break;
#endif

	case led_green_on:
		if (led_state & LED_STATE_CLAIMED)
			hw_led_state &= ~SEQUOIA_LED_GREEN;
		break;

	case led_green_off:
		if (led_state & LED_STATE_CLAIMED)
			hw_led_state |= SEQUOIA_LED_GREEN;
		break;

	case led_amber_on:
		if (led_state & LED_STATE_CLAIMED)
			hw_led_state &= ~SEQUOIA_LED_AMBER;
		break;

	case led_amber_off:
		if (led_state & LED_STATE_CLAIMED)
			hw_led_state |= SEQUOIA_LED_AMBER;
		break;

	case led_red_on:
		if (led_state & LED_STATE_CLAIMED)
			hw_led_state |= SEQUOIA_LED_BACK;
		break;

	case led_red_off:
		if (led_state & LED_STATE_CLAIMED)
			hw_led_state &= ~SEQUOIA_LED_BACK;
		break;

	default:
		break;
	}

	if  (led_state & LED_STATE_ENABLED)
		sequoia_write(hw_led_state,0x09);

	spin_unlock_irqrestore(&leds_lock, flags);
}