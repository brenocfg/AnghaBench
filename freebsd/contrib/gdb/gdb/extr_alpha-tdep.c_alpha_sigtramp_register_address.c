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
struct gdbarch_tdep {scalar_t__ sc_pc_offset; scalar_t__ sc_fpregs_offset; scalar_t__ sc_regs_offset; } ;
typedef  scalar_t__ CORE_ADDR ;

/* Variables and functions */
 int ALPHA_FP0_REGNUM ; 
 int ALPHA_PC_REGNUM ; 
 int /*<<< orphan*/  current_gdbarch ; 
 struct gdbarch_tdep* gdbarch_tdep (int /*<<< orphan*/ ) ; 

__attribute__((used)) static CORE_ADDR
alpha_sigtramp_register_address (CORE_ADDR sigcontext_addr, int regnum)
{ 
  struct gdbarch_tdep *tdep = gdbarch_tdep (current_gdbarch);

  if (regnum >= 0 && regnum < 32)
    return sigcontext_addr + tdep->sc_regs_offset + regnum * 8;
  else if (regnum >= ALPHA_FP0_REGNUM && regnum < ALPHA_FP0_REGNUM + 32)
    return sigcontext_addr + tdep->sc_fpregs_offset + regnum * 8;
  else if (regnum == ALPHA_PC_REGNUM)
    return sigcontext_addr + tdep->sc_pc_offset; 

  return 0;
}