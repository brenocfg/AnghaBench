#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int z80irqvector; int Z80PC_BASE; int Z80PC; int Z80SP_BASE; int Z80SP; scalar_t__ Z80IF; scalar_t__ Z80IM; scalar_t__ Z80I; } ;

/* Variables and functions */
 int /*<<< orphan*/  CZ80 ; 
 int /*<<< orphan*/  CZ80_SP ; 
 int /*<<< orphan*/  Cz80_Reset (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Cz80_Set_Reg (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int PAHW_SMS ; 
 int PicoAHW ; 
 size_t Z80_MEM_SHIFT ; 
 TYPE_1__ drZ80 ; 
 size_t drz80_sp_base ; 
 int* z80_read_map ; 

void z80_reset(void)
{
#ifdef _USE_DRZ80
  drZ80.Z80I = 0;
  drZ80.Z80IM = 0;
  drZ80.Z80IF = 0;
  drZ80.z80irqvector = 0xff0000; // RST 38h
  drZ80.Z80PC_BASE = drZ80.Z80PC = z80_read_map[0] << 1;
  // others not changed, undefined on cold boot
/*
  drZ80.Z80F  = (1<<2);  // set ZFlag
  drZ80.Z80F2 = (1<<2);  // set ZFlag
  drZ80.Z80IX = 0xFFFF << 16;
  drZ80.Z80IY = 0xFFFF << 16;
*/
  // drZ80 is locked in single bank
  drz80_sp_base = (PicoAHW & PAHW_SMS) ? 0xc000 : 0x0000;
  drZ80.Z80SP_BASE = z80_read_map[drz80_sp_base >> Z80_MEM_SHIFT] << 1;
  if (PicoAHW & PAHW_SMS)
    drZ80.Z80SP = drZ80.Z80SP_BASE + 0xdff0; // simulate BIOS
  // XXX: since we use direct SP pointer, it might make sense to force it to RAM,
  // but we'll rely on built-in stack protection for now
#endif
#ifdef _USE_CZ80
  Cz80_Reset(&CZ80);
  if (PicoAHW & PAHW_SMS)
    Cz80_Set_Reg(&CZ80, CZ80_SP, 0xdff0);
#endif
}