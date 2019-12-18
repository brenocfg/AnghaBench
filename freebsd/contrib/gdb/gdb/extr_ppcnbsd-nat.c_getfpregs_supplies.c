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
 int /*<<< orphan*/  current_gdbarch ; 
 struct gdbarch_tdep* gdbarch_tdep (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
getfpregs_supplies (int regno)
{
  struct gdbarch_tdep *tdep = gdbarch_tdep (current_gdbarch);

  return ((regno >= FP0_REGNUM && regno <= FP0_REGNUM + 31)
	  || regno == tdep->ppc_fpscr_regnum);
}