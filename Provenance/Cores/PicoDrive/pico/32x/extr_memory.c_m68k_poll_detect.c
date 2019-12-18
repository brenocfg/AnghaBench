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
struct TYPE_4__ {int emu_flags; } ;
struct TYPE_3__ {int addr; int cycles; scalar_t__ cnt; } ;

/* Variables and functions */
 int /*<<< orphan*/  EL_32X ; 
 scalar_t__ POLL_THRESHOLD ; 
 TYPE_2__ Pico32x ; 
 scalar_t__ SekNotPolling ; 
 int /*<<< orphan*/  elprintf (int /*<<< orphan*/ ,char*,int,int) ; 
 TYPE_1__ m68k_poll ; 

__attribute__((used)) static int m68k_poll_detect(u32 a, u32 cycles, u32 flags)
{
  int ret = 0;

  if (a - 2 <= m68k_poll.addr && m68k_poll.addr <= a + 2
    && cycles - m68k_poll.cycles <= 64 && !SekNotPolling)
  {
    if (m68k_poll.cnt++ > POLL_THRESHOLD) {
      if (!(Pico32x.emu_flags & flags)) {
        elprintf(EL_32X, "m68k poll addr %08x, cyc %u",
          a, cycles - m68k_poll.cycles);
        ret = 1;
      }
      Pico32x.emu_flags |= flags;
    }
  }
  else {
    m68k_poll.cnt = 0;
    m68k_poll.addr = a;
    SekNotPolling = 0;
  }
  m68k_poll.cycles = cycles;

  return ret;
}