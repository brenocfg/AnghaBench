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
struct TYPE_3__ {int z80_bank68k; } ;
struct TYPE_4__ {TYPE_1__ m; } ;

/* Variables and functions */
 int /*<<< orphan*/  EL_ANOMALY ; 
 int POPT_EN_PSG ; 
 TYPE_2__ Pico ; 
 int PicoOpt ; 
 int /*<<< orphan*/  SN76496Write (unsigned char) ; 
 int /*<<< orphan*/  elprintf (int /*<<< orphan*/ ,char*,unsigned int,unsigned char) ; 

__attribute__((used)) static void z80_md_vdp_br_write(unsigned int a, unsigned char data)
{
  // TODO: allow full VDP access
  if ((a&0xfff9) == 0x7f11) // 7f11 7f13 7f15 7f17
  {
    if (PicoOpt & POPT_EN_PSG)
      SN76496Write(data);
    return;
  }

  if ((a>>8) == 0x60)
  {
    Pico.m.z80_bank68k >>= 1;
    Pico.m.z80_bank68k |= data << 8;
    Pico.m.z80_bank68k &= 0x1ff; // 9 bits and filled in the new top one
    return;
  }

  elprintf(EL_ANOMALY, "z80 invalid w8 [%06x] %02x", a, data);
}