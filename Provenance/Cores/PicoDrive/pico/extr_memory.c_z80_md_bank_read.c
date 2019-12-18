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
 int /*<<< orphan*/  EL_Z80BNK ; 
 TYPE_2__ Pico ; 
 int /*<<< orphan*/  elprintf (int /*<<< orphan*/ ,char*,unsigned int,unsigned char) ; 
 unsigned char m68k_read8 (unsigned int) ; 

__attribute__((used)) static unsigned char z80_md_bank_read(unsigned short a)
{
  unsigned int addr68k;
  unsigned char ret;

  addr68k = Pico.m.z80_bank68k<<15;
  addr68k += a & 0x7fff;

  ret = m68k_read8(addr68k);

  elprintf(EL_Z80BNK, "z80->68k r8 [%06x] %02x", addr68k, ret);
  return ret;
}