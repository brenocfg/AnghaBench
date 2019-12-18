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
 int /*<<< orphan*/  P32X_EVENT_PWM ; 
 int /*<<< orphan*/  p32x_event_schedule (unsigned int,int /*<<< orphan*/ ,int) ; 
 int p32x_pwm_schedule_ (int /*<<< orphan*/ *,unsigned int) ; 

void p32x_pwm_schedule(unsigned int m68k_now)
{
  int after = p32x_pwm_schedule_(NULL, m68k_now);
  if (after != 0)
    p32x_event_schedule(m68k_now, P32X_EVENT_PWM, after);
}