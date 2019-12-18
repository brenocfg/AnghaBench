#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int state; unsigned int m68krcycles_done; struct TYPE_7__* other_sh2; } ;
typedef  TYPE_1__ SH2 ;

/* Variables and functions */
 int /*<<< orphan*/  EL_32X ; 
 int SH2_IDLE_STATES ; 
 int SH2_STATE_RUN ; 
 int /*<<< orphan*/  elprintf_sh2 (TYPE_1__*,int /*<<< orphan*/ ,char*,unsigned int,int) ; 
 int event_time_next ; 
 int /*<<< orphan*/  run_sh2 (TYPE_1__*,int) ; 
 int sh2_cycles_left (TYPE_1__*) ; 
 int /*<<< orphan*/  sh2_end_run (TYPE_1__*,int) ; 

void p32x_sync_other_sh2(SH2 *sh2, unsigned int m68k_target)
{
  SH2 *osh2 = sh2->other_sh2;
  int left_to_event;
  int m68k_cycles;

  if (osh2->state & SH2_STATE_RUN)
    return;

  m68k_cycles = m68k_target - osh2->m68krcycles_done;
  if (m68k_cycles < 200)
    return;

  if (osh2->state & SH2_IDLE_STATES) {
    osh2->m68krcycles_done = m68k_target;
    return;
  }

  elprintf_sh2(osh2, EL_32X, "sync to %u %d",
    m68k_target, m68k_cycles);

  run_sh2(osh2, m68k_cycles);

  // there might be new event to schedule current sh2 to
  if (event_time_next) {
    left_to_event = event_time_next - m68k_target;
    left_to_event *= 3;
    if (sh2_cycles_left(sh2) > left_to_event) {
      if (left_to_event < 1)
        left_to_event = 1;
      sh2_end_run(sh2, left_to_event);
    }
  }
}