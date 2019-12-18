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
 int /*<<< orphan*/  CM_CTRL_LED ; 
 int /*<<< orphan*/  GREEN_LED ; 
 scalar_t__ INTEGRATOR_DBG_ALPHA_OFFSET ; 
 int /*<<< orphan*/  INTEGRATOR_DBG_BASE ; 
 scalar_t__ INTEGRATOR_DBG_LEDS_OFFSET ; 
 unsigned int IO_ADDRESS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RED_LED ; 
 int __raw_readl (scalar_t__) ; 
 int /*<<< orphan*/  __raw_writel (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  cm_control (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
#define  led_idle_end 132 
#define  led_idle_start 131 
#define  led_red_off 130 
#define  led_red_on 129 
#define  led_timer 128 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 
 int /*<<< orphan*/  saved_leds ; 

__attribute__((used)) static void integrator_leds_event(led_event_t ledevt)
{
	unsigned long flags;
	const unsigned int dbg_base = IO_ADDRESS(INTEGRATOR_DBG_BASE);
	unsigned int update_alpha_leds;

	// yup, change the LEDs
	local_irq_save(flags);
	update_alpha_leds = 0;

	switch(ledevt) {
	case led_idle_start:
		cm_control(CM_CTRL_LED, 0);
		break;

	case led_idle_end:
		cm_control(CM_CTRL_LED, CM_CTRL_LED);
		break;

	case led_timer:
		saved_leds ^= GREEN_LED;
		update_alpha_leds = 1;
		break;

	case led_red_on:
		saved_leds |= RED_LED;
		update_alpha_leds = 1;
		break;

	case led_red_off:
		saved_leds &= ~RED_LED;
		update_alpha_leds = 1;
		break;

	default:
		break;
	}

	if (update_alpha_leds) {
		while (__raw_readl(dbg_base + INTEGRATOR_DBG_ALPHA_OFFSET) & 1);
		__raw_writel(saved_leds, dbg_base + INTEGRATOR_DBG_LEDS_OFFSET);
	}
	local_irq_restore(flags);
}