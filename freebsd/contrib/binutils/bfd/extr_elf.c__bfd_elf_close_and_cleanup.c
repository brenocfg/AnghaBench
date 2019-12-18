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
typedef  int /*<<< orphan*/  bfd_boolean ;
typedef  int /*<<< orphan*/  bfd ;

/* Variables and functions */
 int /*<<< orphan*/  _bfd_dwarf2_cleanup_debug_info (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _bfd_elf_strtab_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _bfd_generic_close_and_cleanup (int /*<<< orphan*/ *) ; 
 scalar_t__ bfd_get_format (int /*<<< orphan*/ *) ; 
 scalar_t__ bfd_object ; 
 int /*<<< orphan*/ * elf_shstrtab (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * elf_tdata (int /*<<< orphan*/ *) ; 

bfd_boolean
_bfd_elf_close_and_cleanup (bfd *abfd)
{
  if (bfd_get_format (abfd) == bfd_object)
    {
      if (elf_tdata (abfd) != NULL && elf_shstrtab (abfd) != NULL)
	_bfd_elf_strtab_free (elf_shstrtab (abfd));
      _bfd_dwarf2_cleanup_debug_info (abfd);
    }

  return _bfd_generic_close_and_cleanup (abfd);
}