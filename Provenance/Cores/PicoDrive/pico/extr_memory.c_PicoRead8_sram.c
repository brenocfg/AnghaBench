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
typedef  int u32 ;
struct TYPE_4__ {int sram_reg; } ;
struct TYPE_6__ {int romsize; int* rom; TYPE_1__ m; } ;
struct TYPE_5__ {int start; int end; int flags; int data; } ;

/* Variables and functions */
 int EEPROM_read () ; 
 int /*<<< orphan*/  EL_SRAMIO ; 
 TYPE_3__ Pico ; 
 int SRF_EEPROM ; 
 int SRR_MAPPED ; 
 TYPE_2__ SRam ; 
 int /*<<< orphan*/  SekPc ; 
 int /*<<< orphan*/  elprintf (int /*<<< orphan*/ ,char*,int,int,int /*<<< orphan*/ ) ; 
 int m68k_unmapped_read8 (int) ; 

__attribute__((used)) static u32 PicoRead8_sram(u32 a)
{
  u32 d;
  if (SRam.start <= a && a <= SRam.end && (Pico.m.sram_reg & SRR_MAPPED))
  {
    if (SRam.flags & SRF_EEPROM) {
      d = EEPROM_read();
      if (!(a & 1))
        d >>= 8;
    } else
      d = *(u8 *)(SRam.data - SRam.start + a);
    elprintf(EL_SRAMIO, "sram r8  [%06x]   %02x @ %06x", a, d, SekPc);
    return d;
  }

  // XXX: this is banking unfriendly
  if (a < Pico.romsize)
    return Pico.rom[a ^ 1];
  
  return m68k_unmapped_read8(a);
}