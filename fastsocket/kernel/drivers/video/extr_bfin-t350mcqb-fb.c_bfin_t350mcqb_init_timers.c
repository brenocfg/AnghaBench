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
 int /*<<< orphan*/  H_PERIOD ; 
 int /*<<< orphan*/  H_PULSE ; 
 int /*<<< orphan*/  TIMER0_id ; 
 int /*<<< orphan*/  TIMER1_id ; 
 int TIMER_CLK_SEL ; 
 int TIMER_EMU_RUN ; 
 int TIMER_MODE_PWM ; 
 int TIMER_PERIOD_CNT ; 
 int TIMER_TIN_SEL ; 
 int /*<<< orphan*/  V_PERIOD ; 
 int /*<<< orphan*/  V_PULSE ; 
 int /*<<< orphan*/  bfin_t350mcqb_stop_timers () ; 
 int /*<<< orphan*/  set_gptimer_config (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  set_gptimer_period (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_gptimer_pwidth (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void bfin_t350mcqb_init_timers(void)
{

	bfin_t350mcqb_stop_timers();

	set_gptimer_period(TIMER0_id, H_PERIOD);
	set_gptimer_pwidth(TIMER0_id, H_PULSE);
	set_gptimer_config(TIMER0_id, TIMER_MODE_PWM | TIMER_PERIOD_CNT |
				      TIMER_TIN_SEL | TIMER_CLK_SEL|
				      TIMER_EMU_RUN);

	set_gptimer_period(TIMER1_id, V_PERIOD);
	set_gptimer_pwidth(TIMER1_id, V_PULSE);
	set_gptimer_config(TIMER1_id, TIMER_MODE_PWM | TIMER_PERIOD_CNT |
				      TIMER_TIN_SEL | TIMER_CLK_SEL |
				      TIMER_EMU_RUN);

}