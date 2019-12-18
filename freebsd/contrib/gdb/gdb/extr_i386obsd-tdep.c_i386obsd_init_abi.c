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
struct gdbarch_tdep {int sizeof_gregset; void* sc_num_regs; void* sc_reg_offset; int /*<<< orphan*/  sigtramp_end; int /*<<< orphan*/  sigtramp_start; int /*<<< orphan*/  struct_return; void* gregset_num_regs; void* gregset_reg_offset; } ;
struct gdbarch_info {int dummy; } ;
struct gdbarch {int dummy; } ;

/* Variables and functions */
 void* ARRAY_SIZE (void*) ; 
 struct gdbarch_tdep* gdbarch_tdep (struct gdbarch*) ; 
 int /*<<< orphan*/  i386bsd_init_abi (struct gdbarch_info,struct gdbarch*) ; 
 int /*<<< orphan*/  i386obsd_pc_in_sigtramp ; 
 void* i386obsd_r_reg_offset ; 
 void* i386obsd_sc_reg_offset ; 
 int /*<<< orphan*/  i386obsd_sigtramp_end ; 
 int /*<<< orphan*/  i386obsd_sigtramp_end_addr ; 
 int /*<<< orphan*/  i386obsd_sigtramp_start ; 
 int /*<<< orphan*/  i386obsd_sigtramp_start_addr ; 
 int /*<<< orphan*/  reg_struct_return ; 
 int /*<<< orphan*/  set_gdbarch_pc_in_sigtramp (struct gdbarch*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_gdbarch_sigtramp_end (struct gdbarch*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_gdbarch_sigtramp_start (struct gdbarch*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void 
i386obsd_init_abi (struct gdbarch_info info, struct gdbarch *gdbarch)
{
  struct gdbarch_tdep *tdep = gdbarch_tdep (gdbarch);

  /* Obviously OpenBSD is BSD-based.  */
  i386bsd_init_abi (info, gdbarch);

  /* OpenBSD has a different `struct reg'.  */
  tdep->gregset_reg_offset = i386obsd_r_reg_offset;
  tdep->gregset_num_regs = ARRAY_SIZE (i386obsd_r_reg_offset);
  tdep->sizeof_gregset = 16 * 4;

  /* OpenBSD uses -freg-struct-return by default.  */
  tdep->struct_return = reg_struct_return;

  /* OpenBSD uses a different memory layout.  */
  tdep->sigtramp_start = i386obsd_sigtramp_start_addr;
  tdep->sigtramp_end = i386obsd_sigtramp_end_addr;
  set_gdbarch_pc_in_sigtramp (gdbarch, i386obsd_pc_in_sigtramp);
  set_gdbarch_sigtramp_start (gdbarch, i386obsd_sigtramp_start);
  set_gdbarch_sigtramp_end (gdbarch, i386obsd_sigtramp_end);

  /* OpenBSD has a `struct sigcontext' that's different from the
     origional 4.3 BSD.  */
  tdep->sc_reg_offset = i386obsd_sc_reg_offset;
  tdep->sc_num_regs = ARRAY_SIZE (i386obsd_sc_reg_offset);
}