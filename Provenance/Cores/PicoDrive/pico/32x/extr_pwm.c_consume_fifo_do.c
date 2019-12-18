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
struct Pico32xMem {unsigned short** pwm_fifo; void** pwm_current; void** pwm; } ;
struct TYPE_2__ {scalar_t__* pwm_p; scalar_t__ pwm_irq_cnt; unsigned int pwm_cycle_p; } ;
typedef  int /*<<< orphan*/  SH2 ;

/* Variables and functions */
 int /*<<< orphan*/  EL_PWM ; 
 int PWM_BUFF_LEN ; 
 TYPE_1__ Pico32x ; 
 struct Pico32xMem* Pico32xMem ; 
 void* convert_sample (unsigned short) ; 
 int /*<<< orphan*/  do_pwm_irq (int /*<<< orphan*/ *,unsigned int) ; 
 int /*<<< orphan*/  elprintf (int /*<<< orphan*/ ,char*,unsigned int,int,int,scalar_t__,scalar_t__,int) ; 
 int pwm_cycles ; 
 int pwm_doing_fifo ; 
 scalar_t__ pwm_irq_reload ; 
 int pwm_ptr ; 
 scalar_t__ pwm_silent ; 

__attribute__((used)) static void consume_fifo_do(SH2 *sh2, unsigned int m68k_cycles,
  int sh2_cycles_diff)
{
  struct Pico32xMem *mem = Pico32xMem;
  unsigned short *fifo_l = mem->pwm_fifo[0];
  unsigned short *fifo_r = mem->pwm_fifo[1];
  int sum = 0;

  if (pwm_cycles == 0 || pwm_doing_fifo)
    return;

  elprintf(EL_PWM, "pwm: %u: consume %d/%d, %d,%d ptr %d",
    m68k_cycles, sh2_cycles_diff, sh2_cycles_diff / pwm_cycles,
    Pico32x.pwm_p[0], Pico32x.pwm_p[1], pwm_ptr);

  // this is for recursion from dreq1 writes
  pwm_doing_fifo = 1;

  for (; sh2_cycles_diff >= pwm_cycles; sh2_cycles_diff -= pwm_cycles)
  {
    if (Pico32x.pwm_p[0] > 0) {
      fifo_l[0] = fifo_l[1];
      fifo_l[1] = fifo_l[2];
      fifo_l[2] = fifo_l[3];
      Pico32x.pwm_p[0]--;
      mem->pwm_current[0] = convert_sample(fifo_l[0]);
      sum += mem->pwm_current[0];
    }
    if (Pico32x.pwm_p[1] > 0) {
      fifo_r[0] = fifo_r[1];
      fifo_r[1] = fifo_r[2];
      fifo_r[2] = fifo_r[3];
      Pico32x.pwm_p[1]--;
      mem->pwm_current[1] = convert_sample(fifo_r[0]);
      sum += mem->pwm_current[1];
    }

    mem->pwm[pwm_ptr * 2    ] = mem->pwm_current[0];
    mem->pwm[pwm_ptr * 2 + 1] = mem->pwm_current[1];
    pwm_ptr = (pwm_ptr + 1) & (PWM_BUFF_LEN - 1);

    if (--Pico32x.pwm_irq_cnt == 0) {
      Pico32x.pwm_irq_cnt = pwm_irq_reload;
      do_pwm_irq(sh2, m68k_cycles);
    }
  }
  Pico32x.pwm_cycle_p = m68k_cycles * 3 - sh2_cycles_diff;
  pwm_doing_fifo = 0;
  if (sum != 0)
    pwm_silent = 0;
}