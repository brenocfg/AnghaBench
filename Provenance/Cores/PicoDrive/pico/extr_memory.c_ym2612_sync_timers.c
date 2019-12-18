#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int status; } ;
struct TYPE_5__ {TYPE_1__ ST; } ;
struct TYPE_6__ {TYPE_2__ OPN; } ;

/* Variables and functions */
 int /*<<< orphan*/  EL_YMTIMER ; 
 int TIMER_NO_OFLOW ; 
 int /*<<< orphan*/  elprintf (int /*<<< orphan*/ ,char*,int,int) ; 
 int timer_a_next_oflow ; 
 int timer_a_step ; 
 int timer_b_next_oflow ; 
 int timer_b_step ; 
 TYPE_3__ ym2612 ; 

void ym2612_sync_timers(int z80_cycles, int mode_old, int mode_new)
{
  int xcycles = z80_cycles << 8;

  /* check for overflows */
  if ((mode_old & 4) && xcycles > timer_a_next_oflow)
    ym2612.OPN.ST.status |= 1;

  if ((mode_old & 8) && xcycles > timer_b_next_oflow)
    ym2612.OPN.ST.status |= 2;

  /* update timer a */
  if (mode_old & 1)
    while (xcycles > timer_a_next_oflow)
      timer_a_next_oflow += timer_a_step;

  if ((mode_old ^ mode_new) & 1) // turning on/off
  {
    if (mode_old & 1)
      timer_a_next_oflow = TIMER_NO_OFLOW;
    else
      timer_a_next_oflow = xcycles + timer_a_step;
  }
  if (mode_new & 1)
    elprintf(EL_YMTIMER, "timer a upd to %i @ %i", timer_a_next_oflow>>8, z80_cycles);

  /* update timer b */
  if (mode_old & 2)
    while (xcycles > timer_b_next_oflow)
      timer_b_next_oflow += timer_b_step;

  if ((mode_old ^ mode_new) & 2)
  {
    if (mode_old & 2)
      timer_b_next_oflow = TIMER_NO_OFLOW;
    else
      timer_b_next_oflow = xcycles + timer_b_step;
  }
  if (mode_new & 2)
    elprintf(EL_YMTIMER, "timer b upd to %i @ %i", timer_b_next_oflow>>8, z80_cycles);
}