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

/* Variables and functions */
 int /*<<< orphan*/  GDB_OSABI_FREEBSD_ELF ; 
 int /*<<< orphan*/  add_core_fns (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bfd_arch_mips ; 
 int /*<<< orphan*/  gdbarch_register_osabi (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mipsfbsd_core_fns ; 
 int /*<<< orphan*/  mipsfbsd_elfcore_fns ; 
 int /*<<< orphan*/  mipsfbsd_init_abi ; 

void
_initialize_mipsfbsd_tdep (void)
{
  gdbarch_register_osabi (bfd_arch_mips, 0, GDB_OSABI_FREEBSD_ELF,
			  mipsfbsd_init_abi);
  add_core_fns (&mipsfbsd_core_fns);
  add_core_fns (&mipsfbsd_elfcore_fns);
}