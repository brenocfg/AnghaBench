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
 scalar_t__ CYCLES_GT (unsigned int,int) ; 
 int SekCycleAim ; 
 int /*<<< orphan*/  SekSyncM68k () ; 
 int /*<<< orphan*/  pcd_sync_s68k (int,int /*<<< orphan*/ ) ; 

void pcd_run_cpus_lockstep(int m68k_cycles)
{
  unsigned int target = SekCycleAim + m68k_cycles;
  do {
    SekCycleAim += 8;
    SekSyncM68k();
    pcd_sync_s68k(SekCycleAim, 0);
  } while (CYCLES_GT(target, SekCycleAim));

  SekCycleAim = target;
}