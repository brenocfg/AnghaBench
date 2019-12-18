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
struct TYPE_4__ {scalar_t__ zram; scalar_t__ rom; } ;
struct TYPE_3__ {int /*<<< orphan*/  z80_out; int /*<<< orphan*/  z80_in; } ;
typedef  int /*<<< orphan*/  FPTR ;

/* Variables and functions */
 int /*<<< orphan*/  CZ80 ; 
 int /*<<< orphan*/  Cz80_Set_Fetch (int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Cz80_Set_INPort (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Cz80_Set_OUTPort (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_2__ Pico ; 
 TYPE_1__ drZ80 ; 
 scalar_t__ xwrite ; 
 int /*<<< orphan*/  z80_map_set (int /*<<< orphan*/ ,int,int,scalar_t__,int) ; 
 int /*<<< orphan*/  z80_read_map ; 
 int /*<<< orphan*/  z80_sms_in ; 
 int /*<<< orphan*/  z80_sms_out ; 
 int /*<<< orphan*/  z80_write_map ; 

void PicoMemSetupMS(void)
{
  z80_map_set(z80_read_map, 0x0000, 0xbfff, Pico.rom, 0);
  z80_map_set(z80_read_map, 0xc000, 0xdfff, Pico.zram, 0);
  z80_map_set(z80_read_map, 0xe000, 0xffff, Pico.zram, 0);

  z80_map_set(z80_write_map, 0x0000, 0xbfff, xwrite, 1);
  z80_map_set(z80_write_map, 0xc000, 0xdfff, Pico.zram, 0);
  z80_map_set(z80_write_map, 0xe000, 0xffff, xwrite, 1);
 
#ifdef _USE_DRZ80
  drZ80.z80_in = z80_sms_in;
  drZ80.z80_out = z80_sms_out;
#endif
#ifdef _USE_CZ80
  Cz80_Set_Fetch(&CZ80, 0x0000, 0xbfff, (FPTR)Pico.rom);
  Cz80_Set_Fetch(&CZ80, 0xc000, 0xdfff, (FPTR)Pico.zram);
  Cz80_Set_Fetch(&CZ80, 0xe000, 0xffff, (FPTR)Pico.zram);
  Cz80_Set_INPort(&CZ80, z80_sms_in);
  Cz80_Set_OUTPort(&CZ80, z80_sms_out);
#endif
}