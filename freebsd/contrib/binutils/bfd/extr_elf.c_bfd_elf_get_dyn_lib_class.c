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
typedef  int /*<<< orphan*/  bfd ;

/* Variables and functions */
 scalar_t__ bfd_get_flavour (int /*<<< orphan*/ *) ; 
 scalar_t__ bfd_get_format (int /*<<< orphan*/ *) ; 
 scalar_t__ bfd_object ; 
 scalar_t__ bfd_target_elf_flavour ; 
 int elf_dyn_lib_class (int /*<<< orphan*/ *) ; 

int
bfd_elf_get_dyn_lib_class (bfd *abfd)
{
  int lib_class;
  if (bfd_get_flavour (abfd) == bfd_target_elf_flavour
      && bfd_get_format (abfd) == bfd_object)
    lib_class = elf_dyn_lib_class (abfd);
  else
    lib_class = 0;
  return lib_class;
}