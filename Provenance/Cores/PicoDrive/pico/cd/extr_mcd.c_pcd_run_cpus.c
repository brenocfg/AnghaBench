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
struct TYPE_3__ {int m68k_poll_cnt; scalar_t__ need_sync; int /*<<< orphan*/  m68k_poll_a; } ;
struct TYPE_4__ {TYPE_1__ m; } ;

/* Variables and functions */
 scalar_t__ CYCLES_GT (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  EL_CDPOLL ; 
 TYPE_2__* Pico_mcd ; 
 scalar_t__ SekCycleAim ; 
 scalar_t__ SekCycleCnt ; 
 int /*<<< orphan*/  SekPc ; 
 int /*<<< orphan*/  SekRunM68kOnce () ; 
 scalar_t__ SekShouldInterrupt () ; 
 int /*<<< orphan*/  elprintf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int pcd_sync_s68k (scalar_t__,int) ; 

void pcd_run_cpus_normal(int m68k_cycles)
{
  SekCycleAim += m68k_cycles;
  if (SekShouldInterrupt() || Pico_mcd->m.m68k_poll_cnt < 12)
    Pico_mcd->m.m68k_poll_cnt = 0;
  else if (Pico_mcd->m.m68k_poll_cnt >= 16) {
    int s68k_left = pcd_sync_s68k(SekCycleAim, 1);
    if (s68k_left <= 0) {
      elprintf(EL_CDPOLL, "m68k poll [%02x] x%d @%06x",
        Pico_mcd->m.m68k_poll_a, Pico_mcd->m.m68k_poll_cnt, SekPc);
      SekCycleCnt = SekCycleAim;
      return;
    }
    SekCycleCnt = SekCycleAim - (s68k_left * 40220 >> 16);
  }

  while (CYCLES_GT(SekCycleAim, SekCycleCnt)) {
    SekRunM68kOnce();
    if (Pico_mcd->m.need_sync) {
      Pico_mcd->m.need_sync = 0;
      pcd_sync_s68k(SekCycleCnt, 0);
    }
  }
}