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
typedef  int u16 ;
struct TYPE_4__ {int* vdp_regs; } ;
struct TYPE_3__ {int** dram; } ;
typedef  int /*<<< orphan*/  SH2 ;

/* Variables and functions */
 int P32XV_FS ; 
 int P32XV_nFEN ; 
 int /*<<< orphan*/  P32X_EVENT_FILLEND ; 
 TYPE_2__ Pico32x ; 
 TYPE_1__* Pico32xMem ; 
 int /*<<< orphan*/  p32x_event_schedule_sh2 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  p32x_vdp_write8 (int,int) ; 

__attribute__((used)) static void p32x_vdp_write16(u32 a, u32 d, SH2 *sh2)
{
  a &= 0x0e;
  if (a == 6) { // fill start
    Pico32x.vdp_regs[6 / 2] = d;
    return;
  }
  if (a == 8) { // fill data
    u16 *dram = Pico32xMem->dram[(Pico32x.vdp_regs[0x0a/2] & P32XV_FS) ^ 1];
    int len = Pico32x.vdp_regs[4 / 2] + 1;
    int len1 = len;
    a = Pico32x.vdp_regs[6 / 2];
    while (len1--) {
      dram[a] = d;
      a = (a & 0xff00) | ((a + 1) & 0xff);
    }
    Pico32x.vdp_regs[0x06 / 2] = a;
    Pico32x.vdp_regs[0x08 / 2] = d;
    if (sh2 != NULL && len > 4) {
      Pico32x.vdp_regs[0x0a / 2] |= P32XV_nFEN;
      // supposedly takes 3 bus/6 sh2 cycles? or 3 sh2 cycles?
      p32x_event_schedule_sh2(sh2, P32X_EVENT_FILLEND, 3 + len);
    }
    return;
  }

  p32x_vdp_write8(a | 1, d);
}