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
struct gdbarch_tdep {int sizeof_gregset; void* sc_num_regs; void* sc_reg_offset; int /*<<< orphan*/  sigcontext_addr; int /*<<< orphan*/  sigtramp_end; int /*<<< orphan*/  sigtramp_start; void* gregset_num_regs; void* gregset_reg_offset; } ;
struct gdbarch_info {int dummy; } ;
struct gdbarch {int dummy; } ;

/* Variables and functions */
 void* ARRAY_SIZE (void*) ; 
 int /*<<< orphan*/  amd64_init_abi (struct gdbarch_info,struct gdbarch*) ; 
 void* amd64fbsd_r_reg_offset ; 
 void* amd64fbsd_sc_reg_offset ; 
 int /*<<< orphan*/  amd64fbsd_sigcontext_addr ; 
 int /*<<< orphan*/  amd64fbsd_sigtramp_end_addr ; 
 int /*<<< orphan*/  amd64fbsd_sigtramp_start_addr ; 
 struct gdbarch_tdep* gdbarch_tdep (struct gdbarch*) ; 
 int /*<<< orphan*/  i386bsd_init_abi (struct gdbarch_info,struct gdbarch*) ; 
 int /*<<< orphan*/  set_solib_svr4_fetch_link_map_offsets (struct gdbarch*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svr4_lp64_fetch_link_map_offsets ; 

void
amd64fbsd_init_abi (struct gdbarch_info info, struct gdbarch *gdbarch)
{
  struct gdbarch_tdep *tdep = gdbarch_tdep (gdbarch);

  /* Obviously FreeBSD is BSD-based.  */
  i386bsd_init_abi (info, gdbarch);

  tdep->gregset_reg_offset = amd64fbsd_r_reg_offset;
  tdep->gregset_num_regs = ARRAY_SIZE (amd64fbsd_r_reg_offset);
  tdep->sizeof_gregset = 22 * 8;

  amd64_init_abi (info, gdbarch);

  tdep->sigtramp_start = amd64fbsd_sigtramp_start_addr;
  tdep->sigtramp_end = amd64fbsd_sigtramp_end_addr;
  tdep->sigcontext_addr = amd64fbsd_sigcontext_addr;
  tdep->sc_reg_offset = amd64fbsd_sc_reg_offset;
  tdep->sc_num_regs = ARRAY_SIZE (amd64fbsd_sc_reg_offset);

  /* FreeBSD uses SVR4-style shared libraries.  */
  set_solib_svr4_fetch_link_map_offsets
    (gdbarch, svr4_lp64_fetch_link_map_offsets);
}