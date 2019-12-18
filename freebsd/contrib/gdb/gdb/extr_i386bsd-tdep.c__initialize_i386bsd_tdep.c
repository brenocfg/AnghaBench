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
 int /*<<< orphan*/  bfd_arch_i386 ; 
 int /*<<< orphan*/  bfd_arch_unknown ; 
 int /*<<< orphan*/  bfd_target_aout_flavour ; 
 int /*<<< orphan*/  bfd_target_unknown_flavour ; 
 int /*<<< orphan*/  gdbarch_register_osabi_sniffer (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i386bsd_aout_osabi_sniffer ; 
 int /*<<< orphan*/  i386bsd_core_osabi_sniffer ; 

void
_initialize_i386bsd_tdep (void)
{
  gdbarch_register_osabi_sniffer (bfd_arch_i386, bfd_target_aout_flavour,
				  i386bsd_aout_osabi_sniffer);

  /* BFD doesn't set the architecture for NetBSD style a.out core
     files.  */
  gdbarch_register_osabi_sniffer (bfd_arch_unknown, bfd_target_unknown_flavour,
				  i386bsd_core_osabi_sniffer);
}