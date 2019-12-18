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
typedef  int u32 ;
struct TYPE_6__ {unsigned long* Fetch; } ;
struct TYPE_5__ {unsigned long* Fetch; } ;
struct TYPE_4__ {void** word_ram1M; void* word_ram2M; } ;

/* Variables and functions */
 int FAMEC_FETCHBITS ; 
 int M68K_FETCHBANK1 ; 
 TYPE_3__ PicoCpuFM68k ; 
 TYPE_2__ PicoCpuFS68k ; 
 TYPE_1__* Pico_mcd ; 
 int /*<<< orphan*/  cpu68k_map_all_ram (int,int,void*,int) ; 
 int /*<<< orphan*/  cpu68k_map_set (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * m68k_cell_read16 ; 
 int /*<<< orphan*/ * m68k_cell_read8 ; 
 int /*<<< orphan*/ * m68k_cell_write16 ; 
 int /*<<< orphan*/ * m68k_cell_write8 ; 
 int /*<<< orphan*/  m68k_read16_map ; 
 int /*<<< orphan*/  m68k_read8_map ; 
 int /*<<< orphan*/  m68k_write16_map ; 
 int /*<<< orphan*/  m68k_write8_map ; 
 int /*<<< orphan*/ * s68k_dec_read16 ; 
 int /*<<< orphan*/ * s68k_dec_read8 ; 
 int /*<<< orphan*/ ** s68k_dec_write16 ; 
 int /*<<< orphan*/ ** s68k_dec_write8 ; 
 int /*<<< orphan*/  s68k_read16_map ; 
 int /*<<< orphan*/  s68k_read8_map ; 
 int /*<<< orphan*/  s68k_write16_map ; 
 int /*<<< orphan*/  s68k_write8_map ; 

__attribute__((used)) static void remap_word_ram(u32 r3)
{
  void *bank;

  // WORD RAM
  if (!(r3 & 4)) {
    // 2M mode. XXX: allowing access in all cases for simplicity
    bank = Pico_mcd->word_ram2M;
    cpu68k_map_all_ram(0x200000, 0x23ffff, bank, 0);
    cpu68k_map_all_ram(0x080000, 0x0bffff, bank, 1);
    // TODO: handle 0x0c0000
  }
  else {
    int b0 = r3 & 1;
    int m = (r3 & 0x18) >> 3;
    bank = Pico_mcd->word_ram1M[b0];
    cpu68k_map_all_ram(0x200000, 0x21ffff, bank, 0);
    bank = Pico_mcd->word_ram1M[b0 ^ 1];
    cpu68k_map_all_ram(0x0c0000, 0x0effff, bank, 1);
    // "cell arrange" on m68k
    cpu68k_map_set(m68k_read8_map,   0x220000, 0x23ffff, m68k_cell_read8[b0], 1);
    cpu68k_map_set(m68k_read16_map,  0x220000, 0x23ffff, m68k_cell_read16[b0], 1);
    cpu68k_map_set(m68k_write8_map,  0x220000, 0x23ffff, m68k_cell_write8[b0], 1);
    cpu68k_map_set(m68k_write16_map, 0x220000, 0x23ffff, m68k_cell_write16[b0], 1);
    // "decode format" on s68k
    cpu68k_map_set(s68k_read8_map,   0x080000, 0x0bffff, s68k_dec_read8[b0 ^ 1], 1);
    cpu68k_map_set(s68k_read16_map,  0x080000, 0x0bffff, s68k_dec_read16[b0 ^ 1], 1);
    cpu68k_map_set(s68k_write8_map,  0x080000, 0x0bffff, s68k_dec_write8[b0 ^ 1][m], 1);
    cpu68k_map_set(s68k_write16_map, 0x080000, 0x0bffff, s68k_dec_write16[b0 ^ 1][m], 1);
  }

#ifdef EMU_F68K
  // update fetchmap..
  int i;
  if (!(r3 & 4))
  {
    for (i = M68K_FETCHBANK1*2/16; (i<<(24-FAMEC_FETCHBITS)) < 0x240000; i++)
      PicoCpuFM68k.Fetch[i] = (unsigned long)Pico_mcd->word_ram2M - 0x200000;
  }
  else
  {
    for (i = M68K_FETCHBANK1*2/16; (i<<(24-FAMEC_FETCHBITS)) < 0x220000; i++)
      PicoCpuFM68k.Fetch[i] = (unsigned long)Pico_mcd->word_ram1M[r3 & 1] - 0x200000;
    for (i = M68K_FETCHBANK1*0x0c/0x100; (i<<(24-FAMEC_FETCHBITS)) < 0x0e0000; i++)
      PicoCpuFS68k.Fetch[i] = (unsigned long)Pico_mcd->word_ram1M[(r3&1)^1] - 0x0c0000;
  }
#endif
}