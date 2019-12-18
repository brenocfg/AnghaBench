#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int u32 ;

/* Variables and functions */
 int /*<<< orphan*/  EL_CDREGS ; 
 int PicoRead16_io (int) ; 
 int /*<<< orphan*/  SekPc ; 
 int /*<<< orphan*/  elprintf (int /*<<< orphan*/ ,char*,int,int,int /*<<< orphan*/ ) ; 
 int m68k_reg_read16 (int) ; 

u32 PicoRead16_mcd_io(u32 a)
{
  u32 d;
  if ((a & 0xff00) == 0x2000) {
    d = m68k_reg_read16(a);
    elprintf(EL_CDREGS, "m68k_regs r16: [%02x] %04x @%06x",
      a & 0x3f, d, SekPc);
    return d;
  }

  return PicoRead16_io(a);
}