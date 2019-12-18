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
 int /*<<< orphan*/  nbsd_ilp32_solib_svr4_fetch_link_map_offsets ; 
 int /*<<< orphan*/  ppcnbsd_pc_in_sigtramp ; 
 int /*<<< orphan*/  ppcnbsd_return_value ; 
 int /*<<< orphan*/  set_gdbarch_pc_in_sigtramp (struct gdbarch*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_gdbarch_return_value (struct gdbarch*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_solib_svr4_fetch_link_map_offsets (struct gdbarch*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
ppcnbsd_init_abi (struct gdbarch_info info,
                  struct gdbarch *gdbarch)
{
  set_gdbarch_pc_in_sigtramp (gdbarch, ppcnbsd_pc_in_sigtramp);
  /* For NetBSD, this is an on again, off again thing.  Some systems
     do use the broken struct convention, and some don't.  */
  set_gdbarch_return_value (gdbarch, ppcnbsd_return_value);
  set_solib_svr4_fetch_link_map_offsets (gdbarch,
                                nbsd_ilp32_solib_svr4_fetch_link_map_offsets);
}