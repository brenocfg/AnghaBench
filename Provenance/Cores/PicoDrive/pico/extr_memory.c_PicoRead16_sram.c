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
typedef  int u8 ;
typedef  scalar_t__ u32 ;
typedef  scalar_t__ u16 ;
struct TYPE_4__ {int sram_reg; } ;
struct TYPE_6__ {scalar_t__ romsize; scalar_t__ rom; TYPE_1__ m; } ;
struct TYPE_5__ {scalar_t__ start; scalar_t__ end; int flags; scalar_t__ data; } ;

/* Variables and functions */
 scalar_t__ EEPROM_read () ; 
 int /*<<< orphan*/  EL_SRAMIO ; 
 TYPE_3__ Pico ; 
 int SRF_EEPROM ; 
 int SRR_MAPPED ; 
 TYPE_2__ SRam ; 
 int /*<<< orphan*/  SekPc ; 
 int /*<<< orphan*/  elprintf (int /*<<< orphan*/ ,char*,scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ m68k_unmapped_read16 (scalar_t__) ; 

__attribute__((used)) static u32 PicoRead16_sram(u32 a)
{
  u32 d;
  if (SRam.start <= a && a <= SRam.end && (Pico.m.sram_reg & SRR_MAPPED))
  {
    if (SRam.flags & SRF_EEPROM)
      d = EEPROM_read();
    else {
      u8 *pm = (u8 *)(SRam.data - SRam.start + a);
      d  = pm[0] << 8;
      d |= pm[1];
    }
    elprintf(EL_SRAMIO, "sram r16 [%06x] %04x @ %06x", a, d, SekPc);
    return d;
  }

  if (a < Pico.romsize)
    return *(u16 *)(Pico.rom + a);

  return m68k_unmapped_read16(a);
}