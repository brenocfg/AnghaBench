#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {TYPE_3__* sections; } ;
typedef  TYPE_2__ bfd ;
struct TYPE_10__ {int flags; int size; struct TYPE_10__* next; } ;
typedef  TYPE_3__ asection ;
typedef  int /*<<< orphan*/  arelent ;
struct TYPE_8__ {scalar_t__ sh_link; scalar_t__ sh_type; int sh_entsize; } ;
struct TYPE_11__ {TYPE_1__ this_hdr; } ;

/* Variables and functions */
 int SEC_LOAD ; 
 scalar_t__ SHT_REL ; 
 scalar_t__ SHT_RELA ; 
 int /*<<< orphan*/  bfd_error_invalid_operation ; 
 int /*<<< orphan*/  bfd_set_error (int /*<<< orphan*/ ) ; 
 scalar_t__ elf_dynsymtab (TYPE_2__*) ; 
 TYPE_4__* elf_section_data (TYPE_3__*) ; 

long
_bfd_elf_get_dynamic_reloc_upper_bound (bfd *abfd)
{
  long ret;
  asection *s;

  if (elf_dynsymtab (abfd) == 0)
    {
      bfd_set_error (bfd_error_invalid_operation);
      return -1;
    }

  ret = sizeof (arelent *);
  for (s = abfd->sections; s != NULL; s = s->next)
    if ((s->flags & SEC_LOAD) != 0
	&& elf_section_data (s)->this_hdr.sh_link == elf_dynsymtab (abfd)
	&& (elf_section_data (s)->this_hdr.sh_type == SHT_REL
	    || elf_section_data (s)->this_hdr.sh_type == SHT_RELA))
      ret += ((s->size / elf_section_data (s)->this_hdr.sh_entsize)
	      * sizeof (arelent *));

  return ret;
}