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
struct TYPE_4__ {int* regs; int dirty_pal; } ;
struct TYPE_3__ {int* pal; } ;

/* Variables and functions */
 int /*<<< orphan*/  EL_32X ; 
 int /*<<< orphan*/  EL_UIO ; 
 int P32XS_FM ; 
 int PAHW_MCD ; 
 TYPE_2__ Pico32x ; 
 TYPE_1__* Pico32xMem ; 
 int PicoAHW ; 
 int /*<<< orphan*/  PicoWrite16_io (int,int) ; 
 int /*<<< orphan*/  PicoWrite16_mcd_io (int,int) ; 
 int /*<<< orphan*/  SekPc ; 
 int /*<<< orphan*/  bank_switch (int) ; 
 int /*<<< orphan*/  elprintf (int /*<<< orphan*/ ,char*,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  p32x_reg_write16 (int,int) ; 
 int /*<<< orphan*/  p32x_vdp_write16 (int,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void PicoWrite16_32x_on(u32 a, u32 d)
{
  if ((a & 0xfc00) == 0x5000)
    elprintf(EL_32X, "m68k 32x w16 [%06x] %04x @%06x", a, d & 0xffff, SekPc);

  if ((a & 0xffc0) == 0x5100) { // a15100
    p32x_reg_write16(a, d);
    return;
  }

  if ((a & 0xfc00) != 0x5000) {
    if (PicoAHW & PAHW_MCD)
      PicoWrite16_mcd_io(a, d);
    else
      PicoWrite16_io(a, d);
    if (a == 0xa130f0)
      bank_switch(Pico32x.regs[4 / 2]);
    return;
  }

  if (!(Pico32x.regs[0] & P32XS_FM)) {
    if ((a & 0xfff0) == 0x5180) { // a15180
      p32x_vdp_write16(a, d, NULL); // FIXME?
      return;
    }

    if ((a & 0xfe00) == 0x5200) { // a15200
      Pico32xMem->pal[(a & 0x1ff) / 2] = d;
      Pico32x.dirty_pal = 1;
      return;
    }
  }

  elprintf(EL_UIO, "m68k unmapped w16 [%06x] %04x @%06x", a, d & 0xffff, SekPc);
}