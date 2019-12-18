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
struct TYPE_2__ {int hb_count; int* pio_shub_war_cam_addr; scalar_t__ sn_lb_int_war_ticks; int /*<<< orphan*/  hb_state; } ;

/* Variables and functions */
 int HZ ; 
 int /*<<< orphan*/  LED_CPU_HEARTBEAT ; 
 scalar_t__ SN_LB_INT_WAR_INTERVAL ; 
 scalar_t__ enable_shub_wars_1_1 () ; 
 scalar_t__ is_shub1 () ; 
 TYPE_1__* pda ; 
 int /*<<< orphan*/  set_led_bits (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sn_lb_int_war_check () ; 

void sn_timer_interrupt(int irq, void *dev_id)
{
	/* LED blinking */
	if (!pda->hb_count--) {
		pda->hb_count = HZ / 2;
		set_led_bits(pda->hb_state ^=
			     LED_CPU_HEARTBEAT, LED_CPU_HEARTBEAT);
	}

	if (is_shub1()) {
		if (enable_shub_wars_1_1()) {
			/* Bugfix code for SHUB 1.1 */
			if (pda->pio_shub_war_cam_addr)
				*pda->pio_shub_war_cam_addr = 0x8000000000000010UL;
		}
		if (pda->sn_lb_int_war_ticks == 0)
			sn_lb_int_war_check();
		pda->sn_lb_int_war_ticks++;
		if (pda->sn_lb_int_war_ticks >= SN_LB_INT_WAR_INTERVAL)
			pda->sn_lb_int_war_ticks = 0;
	}
}