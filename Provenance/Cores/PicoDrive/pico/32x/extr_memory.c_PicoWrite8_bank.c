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
struct TYPE_4__ {int sram_reg; } ;
struct TYPE_6__ {TYPE_1__ m; } ;
struct TYPE_5__ {int* regs; } ;

/* Variables and functions */
 int /*<<< orphan*/  EL_UIO ; 
 TYPE_3__ Pico ; 
 TYPE_2__ Pico32x ; 
 int SRR_MAPPED ; 
 int /*<<< orphan*/  SekPc ; 
 int /*<<< orphan*/  elprintf (int /*<<< orphan*/ ,char*,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  m68k_write8 (int,int) ; 

__attribute__((used)) static void PicoWrite8_bank(u32 a, u32 d)
{
  if (!(Pico.m.sram_reg & SRR_MAPPED))
    elprintf(EL_UIO, "m68k w8  [%06x]   %02x @%06x",
      a, d & 0xff, SekPc);

  a = (Pico32x.regs[4 / 2] << 20) | (a & 0xfffff);
  m68k_write8(a, d);
}