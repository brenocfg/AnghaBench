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
struct gdbarch_tdep {int sizeof_gregset; int jb_pc_offset; void* sc_num_regs; void* sc_reg_offset; int /*<<< orphan*/  sigcontext_addr; void* gregset_num_regs; void* gregset_reg_offset; } ;
struct gdbarch_info {int dummy; } ;
struct gdbarch {int dummy; } ;

/* Variables and functions */
 void* ARRAY_SIZE (void*) ; 
 int /*<<< orphan*/  amd64_init_abi (struct gdbarch_info,struct gdbarch*) ; 
 int /*<<< orphan*/  amd64obsd_pc_in_sigtramp ; 
 void* amd64obsd_r_reg_offset ; 
 int /*<<< orphan*/  amd64obsd_regset_from_core_section ; 
 void* amd64obsd_sc_reg_offset ; 
 int /*<<< orphan*/  amd64obsd_sigcontext_addr ; 
 struct gdbarch_tdep* gdbarch_tdep (struct gdbarch*) ; 
 int /*<<< orphan*/  set_gdbarch_pc_in_sigtramp (struct gdbarch*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_gdbarch_regset_from_core_section (struct gdbarch*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_solib_svr4_fetch_link_map_offsets (struct gdbarch*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svr4_lp64_fetch_link_map_offsets ; 

__attribute__((used)) static void
amd64obsd_init_abi (struct gdbarch_info info, struct gdbarch *gdbarch)
{
  struct gdbarch_tdep *tdep = gdbarch_tdep (gdbarch);

  amd64_init_abi (info, gdbarch);

  /* Initialize general-purpose register set details.  */
  tdep->gregset_reg_offset = amd64obsd_r_reg_offset;
  tdep->gregset_num_regs = ARRAY_SIZE (amd64obsd_r_reg_offset);
  tdep->sizeof_gregset = 24 * 8;

  set_gdbarch_regset_from_core_section (gdbarch,
					amd64obsd_regset_from_core_section);

  tdep->jb_pc_offset = 7 * 8;

  set_gdbarch_pc_in_sigtramp (gdbarch, amd64obsd_pc_in_sigtramp);
  tdep->sigcontext_addr = amd64obsd_sigcontext_addr;
  tdep->sc_reg_offset = amd64obsd_sc_reg_offset;
  tdep->sc_num_regs = ARRAY_SIZE (amd64obsd_sc_reg_offset);

  /* OpenBSD uses SVR4-style shared libraries.  */
  set_solib_svr4_fetch_link_map_offsets
    (gdbarch, svr4_lp64_fetch_link_map_offsets);
}