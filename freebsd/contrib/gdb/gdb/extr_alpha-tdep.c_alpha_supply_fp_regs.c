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
 int ALPHA_FP0_REGNUM ; 
 int ALPHA_FPCR_REGNUM ; 
 int /*<<< orphan*/  supply_register (int,void const*) ; 

void
alpha_supply_fp_regs (int regno, const void *f0_f30, const void *fpcr)
{
  int i;

  for (i = ALPHA_FP0_REGNUM; i < ALPHA_FP0_REGNUM + 31; ++i)
    if (regno == i || regno == -1)
      supply_register (i, (const char *)f0_f30 + (i - ALPHA_FP0_REGNUM) * 8);

  if (regno == ALPHA_FPCR_REGNUM || regno == -1)
    supply_register (ALPHA_FPCR_REGNUM, fpcr);
}