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
struct gdbarch_tdep {int ppc_fpscr_regnum; } ;

/* Variables and functions */
 int FP0_REGNUM ; 
 int FPREG_FPR_OFFSET (int) ; 
 int FPREG_FPSCR_OFFSET ; 
 int /*<<< orphan*/  current_gdbarch ; 
 struct gdbarch_tdep* gdbarch_tdep (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  supply_register (int,char*) ; 

void
ppcnbsd_supply_fpreg (char *fpregs, int regno)
{
  struct gdbarch_tdep *tdep = gdbarch_tdep (current_gdbarch);
  int i;

  for (i = FP0_REGNUM; i <= FP0_REGNUM + 31; i++)
    {
      if (regno == i || regno == -1)
	supply_register (i, fpregs + FPREG_FPR_OFFSET (i - FP0_REGNUM));
    }

  if (regno == tdep->ppc_fpscr_regnum || regno == -1)
    supply_register (tdep->ppc_fpscr_regnum, fpregs + FPREG_FPSCR_OFFSET);
}