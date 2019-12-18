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
struct TYPE_4__ {int TA; int TB; } ;
struct TYPE_5__ {TYPE_1__ ST; } ;
struct TYPE_6__ {TYPE_2__ OPN; } ;

/* Variables and functions */
 int /*<<< orphan*/  EL_YMTIMER ; 
 int POPT_EXT_FM ; 
 int PicoOpt ; 
 scalar_t__ TIMER_NO_OFLOW ; 
 int /*<<< orphan*/  YM2612PicoStateSave2 (int,int) ; 
 int /*<<< orphan*/  YM2612PicoStateSave2_940 (int,int) ; 
 int /*<<< orphan*/  elprintf (int /*<<< orphan*/ ,char*,int,int) ; 
 scalar_t__ timer_a_next_oflow ; 
 scalar_t__ timer_a_step ; 
 scalar_t__ timer_b_next_oflow ; 
 scalar_t__ timer_b_step ; 
 TYPE_3__ ym2612 ; 

void ym2612_pack_state(void)
{
  // timers are saved as tick counts, in 16.16 int format
  int tac, tat = 0, tbc, tbt = 0;
  tac = 1024 - ym2612.OPN.ST.TA;
  tbc = 256  - ym2612.OPN.ST.TB;
  if (timer_a_next_oflow != TIMER_NO_OFLOW)
    tat = (int)((double)(timer_a_step - timer_a_next_oflow) / (double)timer_a_step * tac * 65536);
  if (timer_b_next_oflow != TIMER_NO_OFLOW)
    tbt = (int)((double)(timer_b_step - timer_b_next_oflow) / (double)timer_b_step * tbc * 65536);
  elprintf(EL_YMTIMER, "save: timer a %i/%i", tat >> 16, tac);
  elprintf(EL_YMTIMER, "save: timer b %i/%i", tbt >> 16, tbc);

#ifdef __GP2X__
  if (PicoOpt & POPT_EXT_FM)
    YM2612PicoStateSave2_940(tat, tbt);
  else
#endif
    YM2612PicoStateSave2(tat, tbt);
}