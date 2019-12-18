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
typedef  scalar_t__ u8 ;
typedef  int u32 ;
struct TYPE_3__ {int z80Run; int z80_bank68k; scalar_t__ z80_reset; } ;
struct TYPE_4__ {TYPE_1__ m; scalar_t__* zram; } ;

/* Variables and functions */
 int EL_ANOMALY ; 
 int EL_UIO ; 
 int /*<<< orphan*/  EL_Z80BNK ; 
 int POPT_EN_FM ; 
 int POPT_EN_PSG ; 
 TYPE_2__ Pico ; 
 int PicoOpt ; 
 int /*<<< orphan*/  SN76496Write (int) ; 
 int /*<<< orphan*/  SekCyclesBurnRun (int) ; 
 int /*<<< orphan*/  SekPc ; 
 int /*<<< orphan*/  elprintf (int,char*,int,...) ; 
 int emustatus ; 
 int ym2612_write_local (int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void PicoWrite8_z80(u32 a, u32 d)
{
  if ((Pico.m.z80Run & 1) || Pico.m.z80_reset) {
    // verified on real hw
    elprintf(EL_ANOMALY, "68k z80 write with no bus or reset! [%06x] %02x @ %06x", a, d&0xff, SekPc);
    return;
  }

  if ((a & 0x4000) == 0x0000) { // z80 RAM
    SekCyclesBurnRun(2); // FIXME hack
    Pico.zram[a & 0x1fff] = (u8)d;
    return;
  }
  if ((a & 0x6000) == 0x4000) { // FM Sound
    if (PicoOpt & POPT_EN_FM)
      emustatus |= ym2612_write_local(a&3, d&0xff, 0)&1;
    return;
  }
  // TODO: probably other VDP access too? Maybe more mirrors?
  if ((a & 0x7ff9) == 0x7f11) { // PSG Sound
    if (PicoOpt & POPT_EN_PSG)
      SN76496Write(d);
    return;
  }
  if ((a & 0x7f00) == 0x6000) // Z80 BANK register
  {
    Pico.m.z80_bank68k >>= 1;
    Pico.m.z80_bank68k |= d << 8;
    Pico.m.z80_bank68k &= 0x1ff; // 9 bits and filled in the new top one
    elprintf(EL_Z80BNK, "z80 bank=%06x", Pico.m.z80_bank68k << 15);
    return;
  }
  elprintf(EL_UIO|EL_ANOMALY, "68k bad write [%06x] %02x @ %06x", a, d&0xff, SekPc);
}