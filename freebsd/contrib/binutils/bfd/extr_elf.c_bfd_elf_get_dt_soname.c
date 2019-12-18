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
 char const* elf_dt_name (int /*<<< orphan*/ *) ; 

const char *
bfd_elf_get_dt_soname (bfd *abfd)
{
  if (bfd_get_flavour (abfd) == bfd_target_elf_flavour
      && bfd_get_format (abfd) == bfd_object)
    return elf_dt_name (abfd);
  return NULL;
}