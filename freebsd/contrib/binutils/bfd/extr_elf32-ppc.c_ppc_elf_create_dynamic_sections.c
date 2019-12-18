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
struct ppc_elf_link_hash_table {scalar_t__ plt_type; int /*<<< orphan*/ * plt; void* relplt; int /*<<< orphan*/  srelplt2; scalar_t__ is_vxworks; int /*<<< orphan*/ * relsbss; void* relbss; int /*<<< orphan*/ * dynsbss; void* dynbss; int /*<<< orphan*/ * glink; int /*<<< orphan*/ * got; } ;
struct bfd_link_info {int /*<<< orphan*/  shared; } ;
typedef  int flagword ;
typedef  int /*<<< orphan*/  bfd_boolean ;
typedef  int /*<<< orphan*/  bfd ;
typedef  int /*<<< orphan*/  asection ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ PLT_VXWORKS ; 
 int SEC_ALLOC ; 
 int SEC_CODE ; 
 int SEC_HAS_CONTENTS ; 
 int SEC_IN_MEMORY ; 
 int SEC_LINKER_CREATED ; 
 int SEC_LOAD ; 
 int SEC_READONLY ; 
 int /*<<< orphan*/  _bfd_elf_create_dynamic_sections (int /*<<< orphan*/ *,struct bfd_link_info*) ; 
 int /*<<< orphan*/  abort () ; 
 void* bfd_get_section_by_name (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/ * bfd_make_section_anyway_with_flags (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/ * bfd_make_section_with_flags (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  bfd_set_section_alignment (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  bfd_set_section_flags (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  elf_vxworks_create_dynamic_sections (int /*<<< orphan*/ *,struct bfd_link_info*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ppc_elf_create_got (int /*<<< orphan*/ *,struct bfd_link_info*) ; 
 struct ppc_elf_link_hash_table* ppc_elf_hash_table (struct bfd_link_info*) ; 

__attribute__((used)) static bfd_boolean
ppc_elf_create_dynamic_sections (bfd *abfd, struct bfd_link_info *info)
{
  struct ppc_elf_link_hash_table *htab;
  asection *s;
  flagword flags;

  htab = ppc_elf_hash_table (info);

  if (htab->got == NULL
      && !ppc_elf_create_got (abfd, info))
    return FALSE;

  if (!_bfd_elf_create_dynamic_sections (abfd, info))
    return FALSE;

  flags = (SEC_ALLOC | SEC_LOAD | SEC_READONLY | SEC_HAS_CONTENTS
	   | SEC_IN_MEMORY | SEC_LINKER_CREATED);

  s = bfd_make_section_anyway_with_flags (abfd, ".glink", flags | SEC_CODE);
  htab->glink = s;
  if (s == NULL
      || !bfd_set_section_alignment (abfd, s, 4))
    return FALSE;

  htab->dynbss = bfd_get_section_by_name (abfd, ".dynbss");
  s = bfd_make_section_with_flags (abfd, ".dynsbss",
				   SEC_ALLOC | SEC_LINKER_CREATED);
  htab->dynsbss = s;
  if (s == NULL)
    return FALSE;

  if (! info->shared)
    {
      htab->relbss = bfd_get_section_by_name (abfd, ".rela.bss");
      s = bfd_make_section_with_flags (abfd, ".rela.sbss", flags);
      htab->relsbss = s;
      if (s == NULL
	  || ! bfd_set_section_alignment (abfd, s, 2))
	return FALSE;
    }

  if (htab->is_vxworks
      && !elf_vxworks_create_dynamic_sections (abfd, info, &htab->srelplt2))
    return FALSE;

  htab->relplt = bfd_get_section_by_name (abfd, ".rela.plt");
  htab->plt = s = bfd_get_section_by_name (abfd, ".plt");
  if (s == NULL)
    abort ();

  flags = SEC_ALLOC | SEC_CODE | SEC_LINKER_CREATED;
  if (htab->plt_type == PLT_VXWORKS)
    /* The VxWorks PLT is a loaded section with contents.  */
    flags |= SEC_HAS_CONTENTS | SEC_LOAD | SEC_READONLY;
  return bfd_set_section_flags (abfd, s, flags);
}