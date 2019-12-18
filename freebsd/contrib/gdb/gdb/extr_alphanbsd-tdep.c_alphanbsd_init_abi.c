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
struct gdbarch_tdep {int jb_pc; int jb_elt_size; int /*<<< orphan*/  sigcontext_addr; int /*<<< orphan*/  dynamic_sigtramp_offset; } ;
struct gdbarch_info {int dummy; } ;
struct gdbarch {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  alpha_dwarf2_init_abi (struct gdbarch_info,struct gdbarch*) ; 
 int /*<<< orphan*/  alpha_mdebug_init_abi (struct gdbarch_info,struct gdbarch*) ; 
 int /*<<< orphan*/  alpha_software_single_step ; 
 int /*<<< orphan*/  alphanbsd_pc_in_sigtramp ; 
 int /*<<< orphan*/  alphanbsd_sigcontext_addr ; 
 int /*<<< orphan*/  alphanbsd_sigtramp_offset ; 
 struct gdbarch_tdep* gdbarch_tdep (struct gdbarch*) ; 
 int /*<<< orphan*/  nbsd_lp64_solib_svr4_fetch_link_map_offsets ; 
 int /*<<< orphan*/  set_gdbarch_pc_in_sigtramp (struct gdbarch*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_gdbarch_software_single_step (struct gdbarch*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_solib_svr4_fetch_link_map_offsets (struct gdbarch*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
alphanbsd_init_abi (struct gdbarch_info info,
                    struct gdbarch *gdbarch)
{
  struct gdbarch_tdep *tdep = gdbarch_tdep (gdbarch);

  /* Hook into the DWARF CFI frame unwinder.  */
  alpha_dwarf2_init_abi (info, gdbarch);

  /* Hook into the MDEBUG frame unwinder.  */
  alpha_mdebug_init_abi (info, gdbarch);

  set_gdbarch_pc_in_sigtramp (gdbarch, alphanbsd_pc_in_sigtramp);

  /* NetBSD/alpha does not provide single step support via ptrace(2); we
     must use software single-stepping.  */
  set_gdbarch_software_single_step (gdbarch, alpha_software_single_step);

  set_solib_svr4_fetch_link_map_offsets (gdbarch,
                                 nbsd_lp64_solib_svr4_fetch_link_map_offsets);

  tdep->dynamic_sigtramp_offset = alphanbsd_sigtramp_offset;
  tdep->sigcontext_addr = alphanbsd_sigcontext_addr;

  tdep->jb_pc = 2;
  tdep->jb_elt_size = 8;
}