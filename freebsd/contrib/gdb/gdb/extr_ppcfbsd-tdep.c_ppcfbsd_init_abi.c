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
struct gdbarch_tdep {int wordsize; } ;
struct gdbarch_info {int dummy; } ;
struct gdbarch {int dummy; } ;

/* Variables and functions */
 struct gdbarch_tdep* gdbarch_tdep (struct gdbarch*) ; 
 int /*<<< orphan*/  ppc64_fbsd_convert_from_func_ptr_addr ; 
 int /*<<< orphan*/  ppc64_fbsd_pc_in_sigtramp ; 
 int /*<<< orphan*/  ppc64_skip_trampoline_code ; 
 int /*<<< orphan*/  ppcfbsd_pc_in_sigtramp ; 
 int /*<<< orphan*/  ppcfbsd_regset_from_core_section ; 
 int /*<<< orphan*/  ppcfbsd_return_value ; 
 int /*<<< orphan*/  set_gdbarch_convert_from_func_ptr_addr (struct gdbarch*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_gdbarch_long_double_bit (struct gdbarch*,int) ; 
 int /*<<< orphan*/  set_gdbarch_pc_in_sigtramp (struct gdbarch*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_gdbarch_regset_from_core_section (struct gdbarch*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_gdbarch_return_value (struct gdbarch*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_gdbarch_skip_trampoline_code (struct gdbarch*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_solib_svr4_fetch_link_map_offsets (struct gdbarch*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svr4_ilp32_fetch_link_map_offsets ; 
 int /*<<< orphan*/  svr4_lp64_fetch_link_map_offsets ; 

__attribute__((used)) static void
ppcfbsd_init_abi (struct gdbarch_info info,
                  struct gdbarch *gdbarch)
{
  struct gdbarch_tdep *tdep = gdbarch_tdep (gdbarch);

  /* FreeBSD doesn't support the 128-bit `long double' from the psABI. */
  set_gdbarch_long_double_bit (gdbarch, 64);

  if (tdep->wordsize == 4)
    {
      set_gdbarch_pc_in_sigtramp (gdbarch, ppcfbsd_pc_in_sigtramp);
      set_gdbarch_return_value (gdbarch, ppcfbsd_return_value);
      set_solib_svr4_fetch_link_map_offsets (gdbarch,
					     svr4_ilp32_fetch_link_map_offsets);
    }

  if (tdep->wordsize == 8)
    {
      set_gdbarch_pc_in_sigtramp (gdbarch, ppc64_fbsd_pc_in_sigtramp);
      set_gdbarch_convert_from_func_ptr_addr
        (gdbarch, ppc64_fbsd_convert_from_func_ptr_addr);

      set_gdbarch_skip_trampoline_code (gdbarch, ppc64_skip_trampoline_code);

      set_solib_svr4_fetch_link_map_offsets (gdbarch,
					     svr4_lp64_fetch_link_map_offsets);
    }

  set_gdbarch_regset_from_core_section (gdbarch,
					ppcfbsd_regset_from_core_section);
}