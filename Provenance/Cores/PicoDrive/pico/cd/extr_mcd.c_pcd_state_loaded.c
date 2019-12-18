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
struct TYPE_3__ {unsigned int update_cycles; } ;
struct TYPE_4__ {int pcm_regs_dirty; int* s68k_regs; TYPE_1__ pcm; scalar_t__ pcm_mixpos; scalar_t__ pcm_mixbuf_dirty; int /*<<< orphan*/  pcm_mixbuf; } ;

/* Variables and functions */
 size_t PCD_EVENT_CDC ; 
 size_t PCD_EVENT_TIMER3 ; 
 TYPE_2__* Pico_mcd ; 
 int /*<<< orphan*/  SekCycleAim ; 
 unsigned int SekCycleAimS68k ; 
 unsigned int SekCycleCntS68k ; 
 scalar_t__ event_time_next ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 unsigned int pcd_cycles_m68k_to_s68k (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pcd_event_schedule (unsigned int,size_t,int) ; 
 scalar_t__* pcd_event_times ; 
 int /*<<< orphan*/  pcd_run_events (unsigned int) ; 
 int /*<<< orphan*/  pcd_set_cycle_mult () ; 
 int /*<<< orphan*/  pcd_state_loaded_mem () ; 

void pcd_state_loaded(void)
{
  unsigned int cycles;
  int diff;

  pcd_set_cycle_mult();
  pcd_state_loaded_mem();

  memset(Pico_mcd->pcm_mixbuf, 0, sizeof(Pico_mcd->pcm_mixbuf));
  Pico_mcd->pcm_mixbuf_dirty = 0;
  Pico_mcd->pcm_mixpos = 0;
  Pico_mcd->pcm_regs_dirty = 1;

  // old savestates..
  cycles = pcd_cycles_m68k_to_s68k(SekCycleAim);
  diff = cycles - SekCycleAimS68k;
  if (diff < -1000 || diff > 1000) {
    SekCycleCntS68k = SekCycleAimS68k = cycles;
  }
  if (pcd_event_times[PCD_EVENT_CDC] == 0) {
    pcd_event_schedule(SekCycleAimS68k, PCD_EVENT_CDC, 12500000/75);

    if (Pico_mcd->s68k_regs[0x31])
      pcd_event_schedule(SekCycleAimS68k, PCD_EVENT_TIMER3,
        Pico_mcd->s68k_regs[0x31] * 384);
  }

  diff = cycles - Pico_mcd->pcm.update_cycles;
  if ((unsigned int)diff > 12500000/50)
    Pico_mcd->pcm.update_cycles = cycles;

  // reschedule
  event_time_next = 0;
  pcd_run_events(SekCycleCntS68k);
}