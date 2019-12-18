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
 int /*<<< orphan*/  P32XI_VRES ; 
 int PAHW_32X ; 
 int PicoAHW ; 
 int /*<<< orphan*/  SH2_IDLE_STATES ; 
 int /*<<< orphan*/  SekCyclesDone () ; 
 int /*<<< orphan*/  msh2 ; 
 int /*<<< orphan*/  p32x_pwm_ctl_changed () ; 
 int /*<<< orphan*/  p32x_sh2_poll_event (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  p32x_timers_recalc () ; 
 int /*<<< orphan*/  p32x_trigger_irq (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ssh2 ; 

void PicoReset32x(void)
{
  if (PicoAHW & PAHW_32X) {
    p32x_trigger_irq(NULL, SekCyclesDone(), P32XI_VRES);
    p32x_sh2_poll_event(&msh2, SH2_IDLE_STATES, 0);
    p32x_sh2_poll_event(&ssh2, SH2_IDLE_STATES, 0);
    p32x_pwm_ctl_changed();
    p32x_timers_recalc();
  }
}