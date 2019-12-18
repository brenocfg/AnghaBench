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
typedef  int u32 ;
struct TYPE_3__ {int need_sync; int m68k_poll_a; scalar_t__ m68k_poll_cnt; } ;
struct TYPE_4__ {TYPE_1__ m; } ;

/* Variables and functions */
 TYPE_2__* Pico_mcd ; 
 int /*<<< orphan*/  SekCyclesDone () ; 
 int /*<<< orphan*/  SekEndRun (int) ; 
 scalar_t__ SekNotPolling ; 
 int /*<<< orphan*/  pcd_sync_s68k (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void m68k_comm_check(u32 a)
{
  pcd_sync_s68k(SekCyclesDone(), 0);
  if (a >= 0x0e && !Pico_mcd->m.need_sync) {
    // there are cases when slave updates comm and only switches RAM
    // over after that (mcd1b), so there must be a resync..
    SekEndRun(64);
    Pico_mcd->m.need_sync = 1;
  }
  if (SekNotPolling || a != Pico_mcd->m.m68k_poll_a) {
    Pico_mcd->m.m68k_poll_a = a;
    Pico_mcd->m.m68k_poll_cnt = 0;
    SekNotPolling = 0;
    return;
  }
  Pico_mcd->m.m68k_poll_cnt++;
}