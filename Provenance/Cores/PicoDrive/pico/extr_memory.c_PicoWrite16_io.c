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
typedef  int u8 ;
typedef  int u32 ;
struct TYPE_3__ {int sram_reg; } ;
struct TYPE_4__ {TYPE_1__ m; } ;

/* Variables and functions */
 int /*<<< orphan*/  EL_SRAMIO ; 
 int POPT_EN_32X ; 
 TYPE_2__ Pico ; 
 int PicoOpt ; 
 int /*<<< orphan*/  PicoWrite16_32x (int,int) ; 
 int SRR_MAPPED ; 
 int SRR_READONLY ; 
 int /*<<< orphan*/  ctl_write_z80busreq (int) ; 
 int /*<<< orphan*/  ctl_write_z80reset (int) ; 
 int /*<<< orphan*/  elprintf (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  io_ports_write (int,int) ; 
 int /*<<< orphan*/  m68k_unmapped_write16 (int,int) ; 

void PicoWrite16_io(u32 a, u32 d)
{
  if ((a & 0xffe0) == 0x0000) { // I/O ports (verified: only LSB!)
    io_ports_write(a, d);
    return;
  }
  if ((a & 0xff00) == 0x1100) { // z80 busreq
    ctl_write_z80busreq(d >> 8);
    return;
  }
  if ((a & 0xff00) == 0x1200) { // z80 reset
    ctl_write_z80reset(d >> 8);
    return;
  }
  if (a == 0xa130f0) { // sram access register
    elprintf(EL_SRAMIO, "sram reg=%02x", d);
    Pico.m.sram_reg &= ~(SRR_MAPPED|SRR_READONLY);
    Pico.m.sram_reg |= (u8)(d & 3);
    return;
  }
  if (PicoOpt & POPT_EN_32X) {
    PicoWrite16_32x(a, d);
    return;
  }
  m68k_unmapped_write16(a, d);
}