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
struct TYPE_3__ {unsigned char* carthw; } ;
struct TYPE_4__ {TYPE_1__ ms; int /*<<< orphan*/  rom; } ;
typedef  int /*<<< orphan*/  FPTR ;

/* Variables and functions */
 int /*<<< orphan*/  CZ80 ; 
 int /*<<< orphan*/  Cz80_Set_Fetch (int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ ) ; 
 int EL_ANOMALY ; 
 int EL_STATUS ; 
 int /*<<< orphan*/  EL_Z80BNK ; 
 TYPE_2__ Pico ; 
 unsigned char bank_mask ; 
 int /*<<< orphan*/  elprintf (int,char*,unsigned char,...) ; 
 int /*<<< orphan*/  z80_map_set (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  z80_pc () ; 
 int /*<<< orphan*/  z80_read_map ; 

__attribute__((used)) static void write_bank(unsigned short a, unsigned char d)
{
  elprintf(EL_Z80BNK, "bank %04x %02x @ %04x", a, d, z80_pc());
  switch (a & 0x0f)
  {
    case 0x0c:
      elprintf(EL_STATUS|EL_ANOMALY, "%02x written to control reg!", d);
      break;
    case 0x0d:
      if (d != 0)
        elprintf(EL_STATUS|EL_ANOMALY, "bank0 changed to %d!", d);
      break;
    case 0x0e:
      d &= bank_mask;
      z80_map_set(z80_read_map, 0x4000, 0x7fff, Pico.rom + (d << 14), 0);
#ifdef _USE_CZ80
      Cz80_Set_Fetch(&CZ80, 0x4000, 0x7fff, (FPTR)Pico.rom + (d << 14));
#endif
      break;
    case 0x0f:
      d &= bank_mask;
      z80_map_set(z80_read_map, 0x8000, 0xbfff, Pico.rom + (d << 14), 0);
#ifdef _USE_CZ80
      Cz80_Set_Fetch(&CZ80, 0x8000, 0xbfff, (FPTR)Pico.rom + (d << 14));
#endif
      break;
  }
  Pico.ms.carthw[a & 0x0f] = d;
}