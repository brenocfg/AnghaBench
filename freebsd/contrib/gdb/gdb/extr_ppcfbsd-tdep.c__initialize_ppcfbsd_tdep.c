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
 int /*<<< orphan*/  bfd_arch_powerpc ; 
 int /*<<< orphan*/  bfd_arch_rs6000 ; 
 int /*<<< orphan*/  bfd_mach_ppc ; 
 int /*<<< orphan*/  bfd_mach_ppc64 ; 
 int /*<<< orphan*/  gdbarch_register_osabi (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ppcfbsd_init_abi ; 

void
_initialize_ppcfbsd_tdep (void)
{
  gdbarch_register_osabi (bfd_arch_powerpc, bfd_mach_ppc,
			  GDB_OSABI_FREEBSD_ELF, ppcfbsd_init_abi);
  gdbarch_register_osabi (bfd_arch_powerpc, bfd_mach_ppc64,
			  GDB_OSABI_FREEBSD_ELF, ppcfbsd_init_abi);
  gdbarch_register_osabi (bfd_arch_rs6000, 0, GDB_OSABI_FREEBSD_ELF,
			  ppcfbsd_init_abi);
}