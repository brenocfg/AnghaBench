#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct bfd_link_info {int dummy; } ;
typedef  int /*<<< orphan*/  bfd_boolean ;
typedef  int /*<<< orphan*/  bfd ;
struct TYPE_4__ {int /*<<< orphan*/  name; } ;
typedef  TYPE_1__ asection ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  _bfd_elf_link_omit_section_dynsym (int /*<<< orphan*/ *,struct bfd_link_info*,TYPE_1__*) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 

bfd_boolean
_bfd_sparc_elf_omit_section_dynsym (bfd *output_bfd,
				    struct bfd_link_info *info,
				    asection *p)
{
  /* We keep the .got section symbol so that explicit relocations
     against the _GLOBAL_OFFSET_TABLE_ symbol emitted in PIC mode
     can be turned into relocations against the .got symbol.  */
  if (strcmp (p->name, ".got") == 0)
    return FALSE;

  return _bfd_elf_link_omit_section_dynsym (output_bfd, info, p);
}