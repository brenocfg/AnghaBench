#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct bfd_elf_section_data {int dummy; } ;
typedef  TYPE_2__* sec_ptr ;
typedef  int file_ptr ;
typedef  int bfd_size_type ;
typedef  int /*<<< orphan*/  bfd_byte ;
typedef  int /*<<< orphan*/  bfd_boolean ;
typedef  int /*<<< orphan*/  bfd ;
struct TYPE_8__ {int /*<<< orphan*/ * tdata; } ;
struct TYPE_10__ {TYPE_1__ u; } ;
struct TYPE_9__ {int size; void* used_by_bfd; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ MIPS_ELF_OPTIONS_SECTION_NAME_P (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _bfd_elf_set_section_contents (int /*<<< orphan*/ *,TYPE_2__*,void const*,int,int) ; 
 void* bfd_zalloc (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * elf_section_data (TYPE_2__*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,void const*,int) ; 
 TYPE_3__* mips_elf_section_data (TYPE_2__*) ; 

bfd_boolean
_bfd_mips_elf_set_section_contents (bfd *abfd, sec_ptr section,
				    const void *location,
				    file_ptr offset, bfd_size_type count)
{
  if (MIPS_ELF_OPTIONS_SECTION_NAME_P (section->name))
    {
      bfd_byte *c;

      if (elf_section_data (section) == NULL)
	{
	  bfd_size_type amt = sizeof (struct bfd_elf_section_data);
	  section->used_by_bfd = bfd_zalloc (abfd, amt);
	  if (elf_section_data (section) == NULL)
	    return FALSE;
	}
      c = mips_elf_section_data (section)->u.tdata;
      if (c == NULL)
	{
	  c = bfd_zalloc (abfd, section->size);
	  if (c == NULL)
	    return FALSE;
	  mips_elf_section_data (section)->u.tdata = c;
	}

      memcpy (c + offset, location, count);
    }

  return _bfd_elf_set_section_contents (abfd, section, location, offset,
					count);
}