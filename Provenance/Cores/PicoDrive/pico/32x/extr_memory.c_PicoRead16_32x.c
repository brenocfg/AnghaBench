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
struct TYPE_2__ {int* regs; } ;

/* Variables and functions */
 int /*<<< orphan*/  EL_32X ; 
 int /*<<< orphan*/  EL_UIO ; 
 TYPE_1__ Pico32x ; 
 int /*<<< orphan*/  SekPc ; 
 int /*<<< orphan*/  elprintf (int /*<<< orphan*/ ,char*,int,int,...) ; 

u32 PicoRead16_32x(u32 a)
{
  u32 d = 0;
  if ((a & 0xffc0) == 0x5100) { // a15100
    d = Pico32x.regs[(a & 0x3f) / 2];
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