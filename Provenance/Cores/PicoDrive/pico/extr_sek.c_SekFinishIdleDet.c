#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */

/* Variables and functions */
 int /*<<< orphan*/  CycloneFinishIdle () ; 
 int EL_IDLE ; 
 int EL_STATUS ; 
 int /*<<< orphan*/  elprintf (int,char*,unsigned short) ; 
 int /*<<< orphan*/  fm68k_emulate (int /*<<< orphan*/ ,int) ; 
 size_t idledet_count ; 
 unsigned short** idledet_ptrs ; 

void SekFinishIdleDet(void)
{
#ifdef EMU_C68K
  CycloneFinishIdle();
#endif
#ifdef EMU_F68K
  fm68k_emulate(0, 2);
#endif
  while (idledet_count > 0)
  {
    unsigned short *op = idledet_ptrs[--idledet_count];
    if      ((*op & 0xfd00) == 0x7100)
      *op &= 0xff, *op |= 0x6600;
    else if ((*op & 0xfd00) == 0x7500)
      *op &= 0xff, *op |= 0x6700;
    else if ((*op & 0xfd00) == 0x7d00)
      *op &= 0xff, *op |= 0x6000;
    else
      elprintf(EL_STATUS|EL_IDLE, "idle: don't know how to restore %04x", *op);
  }
}