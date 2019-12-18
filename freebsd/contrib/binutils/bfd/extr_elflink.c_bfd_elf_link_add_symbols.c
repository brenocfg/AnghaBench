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
struct bfd_link_info {int dummy; } ;
typedef  int /*<<< orphan*/  bfd_boolean ;
typedef  int /*<<< orphan*/  bfd ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
#define  bfd_archive 129 
 int /*<<< orphan*/  bfd_error_wrong_format ; 
 int bfd_get_format (int /*<<< orphan*/ *) ; 
#define  bfd_object 128 
 int /*<<< orphan*/  bfd_set_error (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  elf_link_add_archive_symbols (int /*<<< orphan*/ *,struct bfd_link_info*) ; 
 int /*<<< orphan*/  elf_link_add_object_symbols (int /*<<< orphan*/ *,struct bfd_link_info*) ; 

bfd_boolean
bfd_elf_link_add_symbols (bfd *abfd, struct bfd_link_info *info)
{
  switch (bfd_get_format (abfd))
    {
    case bfd_object:
      return elf_link_add_object_symbols (abfd, info);
    case bfd_archive:
      return elf_link_add_archive_symbols (abfd, info);
    default:
      bfd_set_error (bfd_error_wrong_format);
      return FALSE;
    }
}