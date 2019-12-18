#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int* pwm_p; int* regs; int /*<<< orphan*/  pwm_irq_cnt; } ;
struct TYPE_3__ {unsigned short** pwm_fifo; } ;
typedef  int /*<<< orphan*/  SH2 ;

/* Variables and functions */
 int /*<<< orphan*/  EL_PWM ; 
 TYPE_2__ Pico32x ; 
 TYPE_1__* Pico32xMem ; 
 int /*<<< orphan*/  consume_fifo (int /*<<< orphan*/ *,unsigned int) ; 
 int /*<<< orphan*/  elprintf (int /*<<< orphan*/ ,char*,unsigned int,unsigned int,unsigned int,int,int) ; 
 int /*<<< orphan*/  p32x_pwm_ctl_changed () ; 
 int /*<<< orphan*/  pwm_irq_reload ; 

void p32x_pwm_write16(unsigned int a, unsigned int d,
  SH2 *sh2, unsigned int m68k_cycles)
{
  elprintf(EL_PWM, "pwm: %u: w16 %02x %04x (p %d %d)",
    m68k_cycles, a & 0x0e, d, Pico32x.pwm_p[0], Pico32x.pwm_p[1]);

  consume_fifo(sh2, m68k_cycles);

  a &= 0x0e;
  if (a == 0) { // control
    // avoiding pops..
    if ((Pico32x.regs[0x30 / 2] & 0x0f) == 0)
      Pico32xMem->pwm_fifo[0][0] = Pico32xMem->pwm_fifo[1][0] = 0;
    Pico32x.regs[0x30 / 2] = d;
    p32x_pwm_ctl_changed();
    Pico32x.pwm_irq_cnt = pwm_irq_reload; // ?
  }
  else if (a == 2) { // cycle
    Pico32x.regs[0x32 / 2] = d & 0x0fff;
    p32x_pwm_ctl_changed();
  }
  else if (a <= 8) {
    d = (d - 1) & 0x0fff;

    if (a == 4 || a == 8) { // L ch or MONO
      unsigned short *fifo = Pico32xMem->pwm_fifo[0];
      if (Pico32x.pwm_p[0] < 3)
        Pico32x.pwm_p[0]++;
      else {
        fifo[1] = fifo[2];
        fifo[2] = fifo[3];
      }
      fifo[Pico32x.pwm_p[0]] = d;
    }
    if (a == 6 || a == 8) { // R ch or MONO
      unsigned short *fifo = Pico32xMem->pwm_fifo[1];
      if (Pico32x.pwm_p[1] < 3)
        Pico32x.pwm_p[1]++;
      else {
        fifo[1] = fifo[2];
        fifo[2] = fifo[3];
      }
      fifo[Pico32x.pwm_p[1]] = d;
    }
  }
}