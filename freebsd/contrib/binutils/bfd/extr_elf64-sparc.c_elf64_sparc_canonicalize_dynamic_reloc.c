#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {TYPE_3__* sections; } ;
typedef  TYPE_2__ bfd ;
typedef  int /*<<< orphan*/  asymbol ;
struct TYPE_13__ {int /*<<< orphan*/ * relocation; struct TYPE_13__* next; } ;
typedef  TYPE_3__ asection ;
typedef  int /*<<< orphan*/  arelent ;
struct TYPE_11__ {scalar_t__ sh_link; scalar_t__ sh_type; } ;
struct TYPE_14__ {TYPE_1__ this_hdr; } ;

/* Variables and functions */
 scalar_t__ SHT_RELA ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  bfd_error_invalid_operation ; 
 int /*<<< orphan*/  bfd_set_error (int /*<<< orphan*/ ) ; 
 long canon_reloc_count (TYPE_3__*) ; 
 int /*<<< orphan*/  elf64_sparc_slurp_reloc_table (TYPE_2__*,TYPE_3__*,int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 scalar_t__ elf_dynsymtab (TYPE_2__*) ; 
 TYPE_4__* elf_section_data (TYPE_3__*) ; 

__attribute__((used)) static long
elf64_sparc_canonicalize_dynamic_reloc (bfd *abfd, arelent **storage,
					asymbol **syms)
{
  asection *s;
  long ret;

  if (elf_dynsymtab (abfd) == 0)
    {
      bfd_set_error (bfd_error_invalid_operation);
      return -1;
    }

  ret = 0;
  for (s = abfd->sections; s != NULL; s = s->next)
    {
      if (elf_section_data (s)->this_hdr.sh_link == elf_dynsymtab (abfd)
	  && (elf_section_data (s)->this_hdr.sh_type == SHT_RELA))
	{
	  arelent *p;
	  long count, i;

	  if (! elf64_sparc_slurp_reloc_table (abfd, s, syms, TRUE))
	    return -1;
	  count = canon_reloc_count (s);
	  p = s->relocation;
	  for (i = 0; i < count; i++)
	    *storage++ = p++;
	  ret += count;
	}
    }

  *storage = NULL;

  return ret;
}