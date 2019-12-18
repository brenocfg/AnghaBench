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
typedef  scalar_t__ u32 ;
struct TYPE_3__ {scalar_t__ s68k_poll_a; scalar_t__ s68k_poll_clk; scalar_t__ s68k_poll_cnt; } ;
struct TYPE_4__ {TYPE_1__ m; } ;

/* Variables and functions */
 int /*<<< orphan*/  EL_CDPOLL ; 
 scalar_t__ POLL_CYCLES ; 
 scalar_t__ POLL_LIMIT ; 
 TYPE_2__* Pico_mcd ; 
 scalar_t__ SekCyclesDoneS68k () ; 
 scalar_t__ SekIsStoppedS68k () ; 
 int /*<<< orphan*/  SekNotPolling ; 
 scalar_t__ SekNotPollingS68k ; 
 int /*<<< orphan*/  SekPcS68k ; 
 int /*<<< orphan*/  SekSetStopS68k (int) ; 
 int /*<<< orphan*/  elprintf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,scalar_t__) ; 

u32 s68k_poll_detect(u32 a, u32 d)
{
#ifdef USE_POLL_DETECT
  u32 cycles, cnt = 0;
  if (SekIsStoppedS68k())
    return d;

  cycles = SekCyclesDoneS68k();
  if (!SekNotPolling && a == Pico_mcd->m.s68k_poll_a) {
    u32 clkdiff = cycles - Pico_mcd->m.s68k_poll_clk;
    if (clkdiff <= POLL_CYCLES) {
      cnt = Pico_mcd->m.s68k_poll_cnt + 1;
      //printf("-- diff: %u, cnt = %i\n", clkdiff, cnt);
      if (Pico_mcd->m.s68k_poll_cnt > POLL_LIMIT) {
        SekSetStopS68k(1);
        elprintf(EL_CDPOLL, "s68k poll detected @%06x, a=%02x",
          SekPcS68k, a);
      }
    }
  }
  Pico_mcd->m.s68k_poll_a = a;
  Pico_mcd->m.s68k_poll_clk = cycles;
  Pico_mcd->m.s68k_poll_cnt = cnt;
  SekNotPollingS68k = 0;
#endif
  return d;
}