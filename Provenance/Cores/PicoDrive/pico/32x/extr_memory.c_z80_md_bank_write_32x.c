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
struct TYPE_4__ {int z80_bank68k; } ;
struct TYPE_6__ {TYPE_1__ m; } ;
struct TYPE_5__ {int /*<<< orphan*/  emu_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  EL_Z80BNK ; 
 int /*<<< orphan*/  P32XF_Z80_32X_IO ; 
 TYPE_3__ Pico ; 
 TYPE_2__ Pico32x ; 
 int /*<<< orphan*/  elprintf (int /*<<< orphan*/ ,char*,unsigned int,unsigned char) ; 
 int /*<<< orphan*/  m68k_write8 (unsigned int,unsigned char) ; 

__attribute__((used)) static void z80_md_bank_write_32x(unsigned int a, unsigned char d)
{
  unsigned int addr68k;

  addr68k = Pico.m.z80_bank68k << 15;
  addr68k += a & 0x7fff;
  if ((addr68k & 0xfff000) == 0xa15000)
    Pico32x.emu_flags |= P32XF_Z80_32X_IO;

  elprintf(EL_Z80BNK, "z80->68k w8 [%06x] %02x", addr68k, d);
  m68k_write8(addr68k, d);
}