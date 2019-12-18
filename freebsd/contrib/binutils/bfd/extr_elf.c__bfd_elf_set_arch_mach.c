#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  enum bfd_architecture { ____Placeholder_bfd_architecture } bfd_architecture ;
typedef  int /*<<< orphan*/  bfd_boolean ;
typedef  int /*<<< orphan*/  bfd ;
struct TYPE_2__ {int arch; } ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int bfd_arch_unknown ; 
 int /*<<< orphan*/  bfd_default_set_arch_mach (int /*<<< orphan*/ *,int,unsigned long) ; 
 TYPE_1__* get_elf_backend_data (int /*<<< orphan*/ *) ; 

bfd_boolean
_bfd_elf_set_arch_mach (bfd *abfd,
			enum bfd_architecture arch,
			unsigned long machine)
{
  /* If this isn't the right architecture for this backend, and this
     isn't the generic backend, fail.  */
  if (arch != get_elf_backend_data (abfd)->arch
      && arch != bfd_arch_unknown
      && get_elf_backend_data (abfd)->arch != bfd_arch_unknown)
    return FALSE;

  return bfd_default_set_arch_mach (abfd, arch, machine);
}