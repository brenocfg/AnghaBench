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
struct TYPE_4__ {int comm_dirty_68k; int comm_dirty_sh2; int* regs; } ;
struct TYPE_3__ {unsigned int m68krcycles_done; } ;

/* Variables and functions */
 int /*<<< orphan*/  P32XF_68KCPOLL ; 
 TYPE_2__ Pico32x ; 
 unsigned int SekCyclesDone () ; 
 int /*<<< orphan*/  SekEndRun (int) ; 
 int /*<<< orphan*/  SekSetStop (int) ; 
 scalar_t__ m68k_poll_detect (int,unsigned int,int /*<<< orphan*/ ) ; 
 TYPE_1__ msh2 ; 
 int p32x_pwm_read16 (int,int /*<<< orphan*/ *,unsigned int) ; 
 int /*<<< orphan*/  p32x_sync_sh2s (unsigned int) ; 
 int sh2_comm_faker (int) ; 

__attribute__((used)) static u32 p32x_reg_read16(u32 a)
{
  a &= 0x3e;

#if 0
  if ((a & 0x30) == 0x20)
    return sh2_comm_faker(a);
#else
  if ((a & 0x30) == 0x20) {
    unsigned int cycles = SekCyclesDone();
    int comreg = 1 << (a & 0x0f) / 2;

    if (cycles - msh2.m68krcycles_done > 244
        || (Pico32x.comm_dirty_68k & comreg))
      p32x_sync_sh2s(cycles);

    if (Pico32x.comm_dirty_sh2 & comreg)
      Pico32x.comm_dirty_sh2 &= ~comreg;
    else if (m68k_poll_detect(a, cycles, P32XF_68KCPOLL)) {
      SekSetStop(1);
      SekEndRun(16);
    }
    goto out;
  }
#endif

  if (a == 2) { // INTM, INTS
    unsigned int cycles = SekCyclesDone();
    if (cycles - msh2.m68krcycles_done > 64)
      p32x_sync_sh2s(cycles);
    goto out;
  }

  if ((a & 0x30) == 0x30)
    return p32x_pwm_read16(a, NULL, SekCyclesDone());

out:
  return Pico32x.regs[a / 2];
}