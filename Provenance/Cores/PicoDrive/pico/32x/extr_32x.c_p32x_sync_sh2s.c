#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_4__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int* regs; int /*<<< orphan*/  emu_flags; } ;
struct TYPE_5__ {unsigned int m68krcycles_done; int state; } ;

/* Variables and functions */
 scalar_t__ CYCLES_GE (unsigned int,unsigned int) ; 
 scalar_t__ CYCLES_GT (unsigned int,unsigned int) ; 
 int /*<<< orphan*/  EL_32X ; 
 int P32XS_nRES ; 
 TYPE_4__ Pico32x ; 
 int SH2_IDLE_STATES ; 
 int /*<<< orphan*/  elprintf (int /*<<< orphan*/ ,char*,unsigned int,...) ; 
 unsigned int event_time_next ; 
 TYPE_1__ msh2 ; 
 int /*<<< orphan*/  p32x_run_events (unsigned int) ; 
 int /*<<< orphan*/  p32x_timers_do (unsigned int) ; 
 int /*<<< orphan*/  run_sh2 (TYPE_1__*,int) ; 
 TYPE_1__ ssh2 ; 

void sync_sh2s_normal(unsigned int m68k_target)
{
  unsigned int now, target, timer_cycles;
  int cycles;

  elprintf(EL_32X, "sh2 sync to %u", m68k_target);

  if (!(Pico32x.regs[0] & P32XS_nRES)) {
    msh2.m68krcycles_done = ssh2.m68krcycles_done = m68k_target;
    return; // rare
  }

  now = msh2.m68krcycles_done;
  if (CYCLES_GT(now, ssh2.m68krcycles_done))
    now = ssh2.m68krcycles_done;
  timer_cycles = now;

  while (CYCLES_GT(m68k_target, now))
  {
    if (event_time_next && CYCLES_GE(now, event_time_next))
      p32x_run_events(now);

    target = m68k_target;
    if (event_time_next && CYCLES_GT(target, event_time_next))
      target = event_time_next;

    while (CYCLES_GT(target, now))
    {
      elprintf(EL_32X, "sh2 exec to %u %d,%d/%d, flags %x", target,
        target - msh2.m68krcycles_done, target - ssh2.m68krcycles_done,
        m68k_target - now, Pico32x.emu_flags);

      if (!(ssh2.state & SH2_IDLE_STATES)) {
        cycles = target - ssh2.m68krcycles_done;
        if (cycles > 0) {
          run_sh2(&ssh2, cycles);

          if (event_time_next && CYCLES_GT(target, event_time_next))
            target = event_time_next;
        }
      }

      if (!(msh2.state & SH2_IDLE_STATES)) {
        cycles = target - msh2.m68krcycles_done;
        if (cycles > 0) {
          run_sh2(&msh2, cycles);

          if (event_time_next && CYCLES_GT(target, event_time_next))
            target = event_time_next;
        }
      }

      now = target;
      if (!(msh2.state & SH2_IDLE_STATES)) {
        if (CYCLES_GT(now, msh2.m68krcycles_done))
          now = msh2.m68krcycles_done;
      }
      if (!(ssh2.state & SH2_IDLE_STATES)) {
        if (CYCLES_GT(now, ssh2.m68krcycles_done))
          now = ssh2.m68krcycles_done;
      }
    }

    p32x_timers_do(now - timer_cycles);
    timer_cycles = now;
  }

  // advance idle CPUs
  if (msh2.state & SH2_IDLE_STATES) {
    if (CYCLES_GT(m68k_target, msh2.m68krcycles_done))
      msh2.m68krcycles_done = m68k_target;
  }
  if (ssh2.state & SH2_IDLE_STATES) {
    if (CYCLES_GT(m68k_target, ssh2.m68krcycles_done))
      ssh2.m68krcycles_done = m68k_target;
  }
}