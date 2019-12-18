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
typedef  int u32 ;
typedef  int u16 ;
struct TYPE_6__ {int* regs; int comm_dirty_68k; } ;
struct TYPE_5__ {scalar_t__ cnt; } ;
struct TYPE_4__ {scalar_t__ m68krcycles_done; } ;

/* Variables and functions */
 int P32XS_ADEN ; 
 int P32XS_FM ; 
 int P32XS_nRES ; 
 TYPE_3__ Pico32x ; 
 int /*<<< orphan*/  SH2_STATE_CPOLL ; 
 int SekCyclesDone () ; 
 int /*<<< orphan*/  dreq0_write (int*,int) ; 
 TYPE_2__ m68k_poll ; 
 TYPE_1__ msh2 ; 
 int /*<<< orphan*/  p32x_pwm_write16 (int,int,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  p32x_reg_write8 (int,int) ; 
 int /*<<< orphan*/  p32x_reset_sh2s () ; 
 int /*<<< orphan*/  p32x_sh2_poll_event (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  p32x_sync_sh2s (int) ; 
 int /*<<< orphan*/ * sh2s ; 

__attribute__((used)) static void p32x_reg_write16(u32 a, u32 d)
{
  u16 *r = Pico32x.regs;
  a &= 0x3e;

  // for things like bset on comm port
  m68k_poll.cnt = 0;

  switch (a) {
    case 0x00: // adapter ctl
      if ((d ^ r[0]) & d & P32XS_nRES)
        p32x_reset_sh2s();
      r[0] &= ~(P32XS_FM|P32XS_nRES|P32XS_ADEN);
      r[0] |= d & (P32XS_FM|P32XS_nRES|P32XS_ADEN);
      return;
    case 0x08: // DREQ src
      r[a / 2] = d & 0xff;
      return;
    case 0x0a:
      r[a / 2] = d & ~1;
      return;
    case 0x0c: // DREQ dest
      r[a / 2] = d & 0xff;
      return;
    case 0x0e:
      r[a / 2] = d;
      return;
    case 0x10: // DREQ len
      r[a / 2] = d & ~3;
      return;
    case 0x12: // FIFO reg
      dreq0_write(r, d);
      return;
    case 0x1a: // TV + mystery bit
      r[a / 2] = d & 0x0101;
      return;
    case 0x30: // PWM control
      d = (r[a / 2] & ~0x0f) | (d & 0x0f);
      r[a / 2] = d;
      p32x_pwm_write16(a, d, NULL, SekCyclesDone());
      return;
  }

  // comm port
  if ((a & 0x30) == 0x20) {
    int cycles = SekCyclesDone();
    int comreg;
    
    if (r[a / 2] == d)
      return;

    comreg = 1 << (a & 0x0f) / 2;
    if (Pico32x.comm_dirty_68k & comreg)
      p32x_sync_sh2s(cycles);

    r[a / 2] = d;
    p32x_sh2_poll_event(&sh2s[0], SH2_STATE_CPOLL, cycles);
    p32x_sh2_poll_event(&sh2s[1], SH2_STATE_CPOLL, cycles);
    Pico32x.comm_dirty_68k |= comreg;

    if (cycles - (int)msh2.m68krcycles_done > 120)
      p32x_sync_sh2s(cycles);
    return;
  }
  // PWM
  else if ((a & 0x30) == 0x30) {
    p32x_pwm_write16(a, d, NULL, SekCyclesDone());
    return;
  }

  p32x_reg_write8(a + 1, d);
}