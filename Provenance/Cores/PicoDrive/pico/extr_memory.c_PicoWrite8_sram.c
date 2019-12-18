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
typedef  scalar_t__ u8 ;
typedef  scalar_t__ u32 ;
struct TYPE_4__ {int sram_reg; } ;
struct TYPE_6__ {TYPE_1__ m; } ;
struct TYPE_5__ {scalar_t__ end; scalar_t__ start; int flags; scalar_t__ data; int changed; } ;

/* Variables and functions */
 int /*<<< orphan*/  EEPROM_write8 (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  EL_SRAMIO ; 
 TYPE_3__ Pico ; 
 int SRF_EEPROM ; 
 int SRR_MAPPED ; 
 TYPE_2__ SRam ; 
 int /*<<< orphan*/  SekPc ; 
 int /*<<< orphan*/  elprintf (int /*<<< orphan*/ ,char*,scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  m68k_unmapped_write8 (scalar_t__,scalar_t__) ; 

__attribute__((used)) static void PicoWrite8_sram(u32 a, u32 d)
{
  if (a > SRam.end || a < SRam.start || !(Pico.m.sram_reg & SRR_MAPPED)) {
    m68k_unmapped_write8(a, d);
    return;
  }

  elprintf(EL_SRAMIO, "sram w8  [%06x]   %02x @ %06x", a, d & 0xff, SekPc);
  if (SRam.flags & SRF_EEPROM)
  {
    EEPROM_write8(a, d);
  }
  else {
    u8 *pm = (u8 *)(SRam.data - SRam.start + a);
    if (*pm != (u8)d) {
      SRam.changed = 1;
      *pm = (u8)d;
    }
  }
}