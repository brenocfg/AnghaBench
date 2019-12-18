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
struct TYPE_2__ {int* regs; int pwm_irq_cnt; } ;

/* Variables and functions */
 TYPE_1__ Pico32x ; 
 int pwm_cycles ; 
 int pwm_irq_reload ; 
 int pwm_mult ; 

void p32x_pwm_ctl_changed(void)
{
  int control = Pico32x.regs[0x30 / 2];
  int cycles = Pico32x.regs[0x32 / 2];

  cycles = (cycles - 1) & 0x0fff;
  pwm_cycles = cycles;

  // supposedly we should stop FIFO when xMd is 0,
  // but mars test disagrees
  pwm_mult = 0;
  if ((control & 0x0f) != 0)
    pwm_mult = 0x10000 / cycles;

  pwm_irq_reload = (control & 0x0f00) >> 8;
  pwm_irq_reload = ((pwm_irq_reload - 1) & 0x0f) + 1;

  if (Pico32x.pwm_irq_cnt == 0)
    Pico32x.pwm_irq_cnt = pwm_irq_reload;
}