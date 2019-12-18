#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_1__ ;
typedef  struct TYPE_11__   TYPE_10__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_12__ {size_t is_slave; int /*<<< orphan*/  other_sh2; scalar_t__ poll_addr; } ;
struct TYPE_11__ {int* regs; int comm_dirty_sh2; int /*<<< orphan*/ * sh2irqi; int /*<<< orphan*/  sh2irqs; } ;
typedef  TYPE_1__ SH2 ;

/* Variables and functions */
 int /*<<< orphan*/  P32XF_68KCPOLL ; 
 int /*<<< orphan*/  P32XI_HINT ; 
 int /*<<< orphan*/  P32XI_PWM ; 
 int /*<<< orphan*/  P32XI_VINT ; 
 int /*<<< orphan*/  P32XI_VRES ; 
 int P32XS_FM ; 
 TYPE_10__ Pico32x ; 
 int /*<<< orphan*/  SH2_STATE_CPOLL ; 
 int /*<<< orphan*/  p32x_m68k_poll_event (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  p32x_pwm_schedule_sh2 (TYPE_1__*) ; 
 int /*<<< orphan*/  p32x_pwm_sync_to_sh2 (TYPE_1__*) ; 
 int /*<<< orphan*/  p32x_pwm_write16 (int,int,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  p32x_sh2_poll_event (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  p32x_sh2reg_write8 (int,int,TYPE_1__*) ; 
 int /*<<< orphan*/  p32x_update_cmd_irq (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  p32x_update_irls (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sh2_cycles_done_m68k (TYPE_1__*) ; 

__attribute__((used)) static void p32x_sh2reg_write16(u32 a, u32 d, SH2 *sh2)
{
  a &= 0x3e;

  sh2->poll_addr = 0;

  // comm
  if ((a & 0x30) == 0x20) {
    int comreg;
    if (Pico32x.regs[a / 2] == d)
      return;

    Pico32x.regs[a / 2] = d;
    p32x_m68k_poll_event(P32XF_68KCPOLL);
    p32x_sh2_poll_event(sh2->other_sh2, SH2_STATE_CPOLL,
      sh2_cycles_done_m68k(sh2));
    comreg = 1 << (a & 0x0f) / 2;
    Pico32x.comm_dirty_sh2 |= comreg;
    return;
  }
  // PWM
  else if ((a & 0x30) == 0x30) {
    p32x_pwm_write16(a, d, sh2, sh2_cycles_done_m68k(sh2));
    return;
  }

  switch (a) {
    case 0: // FM
      Pico32x.regs[0] &= ~P32XS_FM;
      Pico32x.regs[0] |= d & P32XS_FM;
      break;
    case 0x14:
      Pico32x.sh2irqs &= ~P32XI_VRES;
      goto irls;
    case 0x16:
      Pico32x.sh2irqi[sh2->is_slave] &= ~P32XI_VINT;
      goto irls;
    case 0x18:
      Pico32x.sh2irqi[sh2->is_slave] &= ~P32XI_HINT;
      goto irls;
    case 0x1a:
      Pico32x.regs[2 / 2] &= ~(1 << sh2->is_slave);
      p32x_update_cmd_irq(sh2, 0);
      return;
    case 0x1c:
      p32x_pwm_sync_to_sh2(sh2);
      Pico32x.sh2irqi[sh2->is_slave] &= ~P32XI_PWM;
      p32x_pwm_schedule_sh2(sh2);
      goto irls;
  }

  p32x_sh2reg_write8(a | 1, d, sh2);
  return;

irls:
  p32x_update_irls(sh2, 0);
}