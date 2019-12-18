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
typedef  int led_event_t ;
struct TYPE_2__ {int /*<<< orphan*/  leds; } ;

/* Variables and functions */
 int /*<<< orphan*/  GPIO_IDLE ; 
 int /*<<< orphan*/  GPIO_TIMER ; 
 int /*<<< orphan*/  H2P2_DBG_FPGA_LED_AMBER ; 
 int /*<<< orphan*/  H2P2_DBG_FPGA_LED_BLUE ; 
 int /*<<< orphan*/  H2P2_DBG_FPGA_LED_GREEN ; 
 int /*<<< orphan*/  H2P2_DBG_FPGA_LED_RED ; 
 int /*<<< orphan*/  H2P2_DBG_FPGA_P2_LED_IDLE ; 
 int /*<<< orphan*/  H2P2_DBG_FPGA_P2_LED_TIMER ; 
 int LED_STATE_CLAIMED ; 
 int LED_STATE_ENABLED ; 
 int LED_TIMER_ON ; 
 int /*<<< orphan*/  __raw_writew (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_1__* fpga ; 
 int /*<<< orphan*/  gpio_set_value (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  hw_led_state ; 
#define  led_amber_off 143 
#define  led_amber_on 142 
#define  led_blue_off 141 
#define  led_blue_on 140 
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
 int /*<<< orphan*/  lock ; 
 int /*<<< orphan*/  machine_is_omap_h4 () ; 
 int /*<<< orphan*/  machine_is_omap_perseus2 () ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void h2p2_dbg_leds_event(led_event_t evt)
{
	unsigned long flags;

	spin_lock_irqsave(&lock, flags);

	if (!(led_state & LED_STATE_ENABLED) && evt != led_start)
		goto done;

	switch (evt) {
	case led_start:
		if (fpga)
			led_state |= LED_STATE_ENABLED;
		break;

	case led_stop:
	case led_halted:
		/* all leds off during suspend or shutdown */

		if (!(machine_is_omap_perseus2() || machine_is_omap_h4())) {
			gpio_set_value(GPIO_TIMER, 0);
			gpio_set_value(GPIO_IDLE, 0);
		}

		__raw_writew(~0, &fpga->leds);
		led_state &= ~LED_STATE_ENABLED;
		goto done;

	case led_claim:
		led_state |= LED_STATE_CLAIMED;
		hw_led_state = 0;
		break;

	case led_release:
		led_state &= ~LED_STATE_CLAIMED;
		break;

#ifdef CONFIG_LEDS_TIMER
	case led_timer:
		led_state ^= LED_TIMER_ON;

		if (machine_is_omap_perseus2() || machine_is_omap_h4())
			hw_led_state ^= H2P2_DBG_FPGA_P2_LED_TIMER;
		else {
			gpio_set_value(GPIO_TIMER,
					led_state & LED_TIMER_ON);
			goto done;
		}

		break;
#endif

#ifdef CONFIG_LEDS_CPU
	/* LED lit iff busy */
	case led_idle_start:
		if (machine_is_omap_perseus2() || machine_is_omap_h4())
			hw_led_state &= ~H2P2_DBG_FPGA_P2_LED_IDLE;
		else {
			gpio_set_value(GPIO_IDLE, 1);
			goto done;
		}

		break;

	case led_idle_end:
		if (machine_is_omap_perseus2() || machine_is_omap_h4())
			hw_led_state |= H2P2_DBG_FPGA_P2_LED_IDLE;
		else {
			gpio_set_value(GPIO_IDLE, 0);
			goto done;
		}

		break;
#endif

	case led_green_on:
		hw_led_state |= H2P2_DBG_FPGA_LED_GREEN;
		break;
	case led_green_off:
		hw_led_state &= ~H2P2_DBG_FPGA_LED_GREEN;
		break;

	case led_amber_on:
		hw_led_state |= H2P2_DBG_FPGA_LED_AMBER;
		break;
	case led_amber_off:
		hw_led_state &= ~H2P2_DBG_FPGA_LED_AMBER;
		break;

	case led_red_on:
		hw_led_state |= H2P2_DBG_FPGA_LED_RED;
		break;
	case led_red_off:
		hw_led_state &= ~H2P2_DBG_FPGA_LED_RED;
		break;

	case led_blue_on:
		hw_led_state |= H2P2_DBG_FPGA_LED_BLUE;
		break;
	case led_blue_off:
		hw_led_state &= ~H2P2_DBG_FPGA_LED_BLUE;
		break;

	default:
		break;
	}


	/*
	 *  Actually burn the LEDs
	 */
	if (led_state & LED_STATE_ENABLED)
		__raw_writew(~hw_led_state, &fpga->leds);

done:
	spin_unlock_irqrestore(&lock, flags);
}