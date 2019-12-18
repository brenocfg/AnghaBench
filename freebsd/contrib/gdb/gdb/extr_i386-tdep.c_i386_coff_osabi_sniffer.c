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
typedef  enum gdb_osabi { ____Placeholder_gdb_osabi } gdb_osabi ;
typedef  int /*<<< orphan*/  bfd ;

/* Variables and functions */
 int GDB_OSABI_GO32 ; 
 int GDB_OSABI_UNKNOWN ; 
 int /*<<< orphan*/  bfd_get_target (int /*<<< orphan*/ *) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static enum gdb_osabi
i386_coff_osabi_sniffer (bfd *abfd)
{
  if (strcmp (bfd_get_target (abfd), "coff-go32-exe") == 0
      || strcmp (bfd_get_target (abfd), "coff-go32") == 0)
    return GDB_OSABI_GO32;

  return GDB_OSABI_UNKNOWN;
}