#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_2__ {int* pal; } ;

/* Variables and functions */
 int /*<<< orphan*/  EL_32X ; 
 int /*<<< orphan*/  EL_UIO ; 
 int PAHW_MCD ; 
 TYPE_1__* Pico32xMem ; 
 int PicoAHW ; 
 int PicoRead16_io (int) ; 
 int PicoRead16_mcd_io (int) ; 
 int /*<<< orphan*/  SekPc ; 
 int /*<<< orphan*/  elprintf (int /*<<< orphan*/ ,char*,int,int,...) ; 
 int p32x_reg_read16 (int) ; 
 int p32x_vdp_read16 (int) ; 

__attribute__((used)) static u32 PicoRead16_32x_on(u32 a)
{
  u32 d = 0;
  if ((a & 0xffc0) == 0x5100) { // a15100
    d = p32x_reg_read16(a);
    goto out;
  }

  if ((a & 0xfc00) != 0x5000) {
    if (PicoAHW & PAHW_MCD)
      return PicoRead16_mcd_io(a);
    else
      return PicoRead16_io(a);
  }

  if ((a & 0xfff0) == 0x5180) { // a15180
    d = p32x_vdp_read16(a);
    goto out;
  }

  if ((a & 0xfe00) == 0x5200) { // a15200
    d = Pico32xMem->pal[(a & 0x1ff) / 2];
    goto out;
  }

  if ((a & 0xfffc) == 0x30ec) { // a130ec
    d = !(a & 2) ? ('M'<<8)|'A' : ('R'<<8)|'S';
    goto out;
  }

  elprintf(EL_UIO, "m68k unmapped r16 [%06x] @%06x", a, SekPc);
  return d;

out:
  elprintf(EL_32X, "m68k 32x r16 [%06x] %04x @%06x", a, d, SekPc);
  return d;
}