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
struct TYPE_4__ {scalar_t__ zram; } ;
struct TYPE_3__ {int /*<<< orphan*/  z80_out; int /*<<< orphan*/  z80_in; } ;
typedef  int /*<<< orphan*/  FPTR ;

/* Variables and functions */
 int /*<<< orphan*/  CZ80 ; 
 int /*<<< orphan*/  Cz80_Set_Fetch (int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Cz80_Set_INPort (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Cz80_Set_OUTPort (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_2__ Pico ; 
 TYPE_1__ drZ80 ; 
 scalar_t__ ym2612_read_local_z80 ; 
 int /*<<< orphan*/  z80_map_set (int /*<<< orphan*/ ,int,int,scalar_t__,int) ; 
 scalar_t__ z80_md_bank_read ; 
 scalar_t__ z80_md_bank_write ; 
 int /*<<< orphan*/  z80_md_in ; 
 int /*<<< orphan*/  z80_md_out ; 
 scalar_t__ z80_md_vdp_br_write ; 
 scalar_t__ z80_md_vdp_read ; 
 scalar_t__ z80_md_ym2612_write ; 
 int /*<<< orphan*/  z80_read_map ; 
 int /*<<< orphan*/  z80_write_map ; 

__attribute__((used)) static void z80_mem_setup(void)
{
  z80_map_set(z80_read_map, 0x0000, 0x1fff, Pico.zram, 0);
  z80_map_set(z80_read_map, 0x2000, 0x3fff, Pico.zram, 0);
  z80_map_set(z80_read_map, 0x4000, 0x5fff, ym2612_read_local_z80, 1);
  z80_map_set(z80_read_map, 0x6000, 0x7fff, z80_md_vdp_read, 1);
  z80_map_set(z80_read_map, 0x8000, 0xffff, z80_md_bank_read, 1);

  z80_map_set(z80_write_map, 0x0000, 0x1fff, Pico.zram, 0);
  z80_map_set(z80_write_map, 0x2000, 0x3fff, Pico.zram, 0);
  z80_map_set(z80_write_map, 0x4000, 0x5fff, z80_md_ym2612_write, 1);
  z80_map_set(z80_write_map, 0x6000, 0x7fff, z80_md_vdp_br_write, 1);
  z80_map_set(z80_write_map, 0x8000, 0xffff, z80_md_bank_write, 1);

#ifdef _USE_DRZ80
  drZ80.z80_in = z80_md_in;
  drZ80.z80_out = z80_md_out;
#endif
#ifdef _USE_CZ80
  Cz80_Set_Fetch(&CZ80, 0x0000, 0x1fff, (FPTR)Pico.zram); // main RAM
  Cz80_Set_Fetch(&CZ80, 0x2000, 0x3fff, (FPTR)Pico.zram); // mirror
  Cz80_Set_INPort(&CZ80, z80_md_in);
  Cz80_Set_OUTPort(&CZ80, z80_md_out);
#endif
}