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
typedef  int /*<<< orphan*/  SH2 ;

/* Variables and functions */
 int /*<<< orphan*/  P32X_EVENT_PWM ; 
 int /*<<< orphan*/  p32x_event_schedule_sh2 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int p32x_pwm_schedule_ (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sh2_cycles_done_m68k (int /*<<< orphan*/ *) ; 

void p32x_pwm_schedule_sh2(SH2 *sh2)
{
  int after = p32x_pwm_schedule_(sh2, sh2_cycles_done_m68k(sh2));
  if (after != 0)
    p32x_event_schedule_sh2(sh2, P32X_EVENT_PWM, after);
}