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
struct TYPE_2__ {int /*<<< orphan*/  peri_regs; } ;

/* Variables and functions */
 int /*<<< orphan*/  EL_32XP ; 
 int PREG8 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  elprintf (int /*<<< orphan*/ ,char*,int,int) ; 
 TYPE_1__* sh2s ; 
 scalar_t__* timer_cycles ; 
 int* timer_tick_cycles ; 

void p32x_timers_recalc(void)
{
  int cycles;
  int tmp, i;

  // SH2 timer step
  for (i = 0; i < 2; i++) {
    tmp = PREG8(sh2s[i].peri_regs, 0x80) & 7;
    // Sclk cycles per timer tick
    if (tmp)
      cycles = 0x20 << tmp;
    else
      cycles = 2;
    timer_tick_cycles[i] = cycles;
    timer_cycles[i] = 0;
    elprintf(EL_32XP, "WDT cycles[%d] = %d", i, cycles);
  }
}