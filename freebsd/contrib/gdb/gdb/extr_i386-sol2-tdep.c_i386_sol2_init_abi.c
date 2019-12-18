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
struct gdbarch_tdep {int sizeof_gregset; int sizeof_fpregset; int /*<<< orphan*/  gregset_num_regs; int /*<<< orphan*/  sc_num_regs; int /*<<< orphan*/  gregset_reg_offset; int /*<<< orphan*/  sc_reg_offset; int /*<<< orphan*/  sigcontext_addr; } ;
struct gdbarch_info {int dummy; } ;
struct gdbarch {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 struct gdbarch_tdep* gdbarch_tdep (struct gdbarch*) ; 
 int /*<<< orphan*/  i386_sol2_gregset_reg_offset ; 
 int /*<<< orphan*/  i386_sol2_mcontext_addr ; 
 int /*<<< orphan*/  i386_sol2_pc_in_sigtramp ; 
 int /*<<< orphan*/  i386_svr4_init_abi (struct gdbarch_info,struct gdbarch*) ; 
 int /*<<< orphan*/  set_gdbarch_pc_in_sigtramp (struct gdbarch*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
i386_sol2_init_abi (struct gdbarch_info info, struct gdbarch *gdbarch)
{
  struct gdbarch_tdep *tdep = gdbarch_tdep (gdbarch);

  /* Solaris is SVR4-based.  */
  i386_svr4_init_abi (info, gdbarch);

  /* Solaris reserves space for its FPU emulator in `fpregset_t'.
     There is also some space reserved for the registers of a Weitek
     math coprocessor.  */
  tdep->gregset_reg_offset = i386_sol2_gregset_reg_offset;
  tdep->gregset_num_regs = ARRAY_SIZE (i386_sol2_gregset_reg_offset);
  tdep->sizeof_gregset = 19 * 4;
  tdep->sizeof_fpregset = 380;

  tdep->sigcontext_addr = i386_sol2_mcontext_addr;
  tdep->sc_reg_offset = tdep->gregset_reg_offset;
  tdep->sc_num_regs = tdep->gregset_num_regs;

  /* Signal trampolines are slightly different from SVR4.  */
  set_gdbarch_pc_in_sigtramp (gdbarch, i386_sol2_pc_in_sigtramp);
}