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
typedef  int u32 ;
struct TYPE_3__ {int dmna_ret_2m; unsigned short hint_vector; int /*<<< orphan*/  busreq; } ;
struct TYPE_4__ {int* s68k_regs; TYPE_1__ m; scalar_t__ bios; int /*<<< orphan*/  word_ram2M; } ;

/* Variables and functions */
 TYPE_2__* Pico_mcd ; 
 int /*<<< orphan*/  remap_prg_window (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  remap_word_ram (int) ; 
 int /*<<< orphan*/  wram_2M_to_1M (int /*<<< orphan*/ ) ; 

void pcd_state_loaded_mem(void)
{
  u32 r3 = Pico_mcd->s68k_regs[3];

  /* after load events */
  if (r3 & 4) // 1M mode?
    wram_2M_to_1M(Pico_mcd->word_ram2M);
  remap_word_ram(r3);
  remap_prg_window(Pico_mcd->m.busreq, r3);
  Pico_mcd->m.dmna_ret_2m &= 3;

  // restore hint vector
  *(unsigned short *)(Pico_mcd->bios + 0x72) = Pico_mcd->m.hint_vector;
}