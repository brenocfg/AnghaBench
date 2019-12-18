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
struct TYPE_3__ {int z80Run; scalar_t__ z80_reset; } ;
struct TYPE_4__ {int* zram; TYPE_1__ m; } ;

/* Variables and functions */
 int EL_ANOMALY ; 
 int EL_UIO ; 
 TYPE_2__ Pico ; 
 int /*<<< orphan*/  SekPc ; 
 int /*<<< orphan*/  elprintf (int,char*,int,int /*<<< orphan*/ ) ; 
 int ym2612_read_local_68k () ; 

__attribute__((used)) static u32 PicoRead8_z80(u32 a)
{
  u32 d = 0xff;
  if ((Pico.m.z80Run & 1) || Pico.m.z80_reset) {
    elprintf(EL_ANOMALY, "68k z80 read with no bus! [%06x] @ %06x", a, SekPc);
    // open bus. Pulled down if MegaCD2 is attached.
    return 0;
  }

  if ((a & 0x4000) == 0x0000)
    d = Pico.zram[a & 0x1fff];
  else if ((a & 0x6000) == 0x4000) // 0x4000-0x5fff
    d = ym2612_read_local_68k(); 
  else
    elprintf(EL_UIO|EL_ANOMALY, "68k bad read [%06x] @%06x", a, SekPc);
  return d;
}