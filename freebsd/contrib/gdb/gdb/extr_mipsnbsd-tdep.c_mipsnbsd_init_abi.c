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
struct gdbarch_info {int dummy; } ;
struct gdbarch {int dummy; } ;

/* Variables and functions */
 int gdbarch_ptr_bit (struct gdbarch*) ; 
 int /*<<< orphan*/  mips_software_single_step ; 
 int /*<<< orphan*/  mipsnbsd_cannot_fetch_register ; 
 int /*<<< orphan*/  mipsnbsd_cannot_store_register ; 
 int /*<<< orphan*/  mipsnbsd_get_longjmp_target ; 
 int /*<<< orphan*/  mipsnbsd_ilp32_solib_svr4_fetch_link_map_offsets ; 
 int /*<<< orphan*/  mipsnbsd_lp64_solib_svr4_fetch_link_map_offsets ; 
 int /*<<< orphan*/  mipsnbsd_pc_in_sigtramp ; 
 int /*<<< orphan*/  set_gdbarch_cannot_fetch_register (struct gdbarch*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_gdbarch_cannot_store_register (struct gdbarch*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_gdbarch_get_longjmp_target (struct gdbarch*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_gdbarch_pc_in_sigtramp (struct gdbarch*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_gdbarch_software_single_step (struct gdbarch*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_solib_svr4_fetch_link_map_offsets (struct gdbarch*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
mipsnbsd_init_abi (struct gdbarch_info info,
                   struct gdbarch *gdbarch)
{
  set_gdbarch_pc_in_sigtramp (gdbarch, mipsnbsd_pc_in_sigtramp);

  set_gdbarch_get_longjmp_target (gdbarch, mipsnbsd_get_longjmp_target);

  set_gdbarch_cannot_fetch_register (gdbarch, mipsnbsd_cannot_fetch_register);
  set_gdbarch_cannot_store_register (gdbarch, mipsnbsd_cannot_store_register);

  set_gdbarch_software_single_step (gdbarch, mips_software_single_step);

  set_solib_svr4_fetch_link_map_offsets (gdbarch,
					 gdbarch_ptr_bit (gdbarch) == 32 ?
                            mipsnbsd_ilp32_solib_svr4_fetch_link_map_offsets :
			    mipsnbsd_lp64_solib_svr4_fetch_link_map_offsets);
}