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
struct gdbarch_tdep {int sc_pc_offset; int sc_regs_offset; int sc_fpregs_offset; int jb_pc; int jb_elt_size; int /*<<< orphan*/  sigcontext_addr; int /*<<< orphan*/  dynamic_sigtramp_offset; } ;
struct gdbarch_info {int dummy; } ;
struct gdbarch {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  alpha_dwarf2_init_abi (struct gdbarch_info,struct gdbarch*) ; 
 int /*<<< orphan*/  alpha_mdebug_init_abi (struct gdbarch_info,struct gdbarch*) ; 
 int /*<<< orphan*/  alphafbsd_pc_in_sigtramp ; 
 int /*<<< orphan*/  alphafbsd_sigcontext_addr ; 
 int /*<<< orphan*/  alphafbsd_sigtramp_offset ; 
 int /*<<< orphan*/  alphafbsd_use_struct_convention ; 
 struct gdbarch_tdep* gdbarch_tdep (struct gdbarch*) ; 
 int /*<<< orphan*/  set_gdbarch_pc_in_sigtramp (struct gdbarch*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_gdbarch_use_struct_convention (struct gdbarch*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
alphafbsd_init_abi (struct gdbarch_info info,
                    struct gdbarch *gdbarch)
{
  struct gdbarch_tdep *tdep = gdbarch_tdep (gdbarch);

  /* Hook into the DWARF CFI frame unwinder.  */
  alpha_dwarf2_init_abi (info, gdbarch);

  /* Hook into the MDEBUG frame unwinder.  */
  alpha_mdebug_init_abi (info, gdbarch);

  set_gdbarch_use_struct_convention (gdbarch, alphafbsd_use_struct_convention);

  set_gdbarch_pc_in_sigtramp (gdbarch, alphafbsd_pc_in_sigtramp);

  tdep->dynamic_sigtramp_offset = alphafbsd_sigtramp_offset;
  tdep->sigcontext_addr = alphafbsd_sigcontext_addr;
  tdep->sc_pc_offset = 288;
  tdep->sc_regs_offset = 24;
  tdep->sc_fpregs_offset = 320;

  tdep->jb_pc = 2;
  tdep->jb_elt_size = 8;
}