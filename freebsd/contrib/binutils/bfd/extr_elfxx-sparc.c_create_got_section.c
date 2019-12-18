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
struct _bfd_sparc_elf_link_hash_table {void* sgotplt; scalar_t__ is_vxworks; int /*<<< orphan*/  word_align_power; int /*<<< orphan*/ * srelgot; int /*<<< orphan*/ * sgot; } ;
typedef  int /*<<< orphan*/  bfd_boolean ;
typedef  int /*<<< orphan*/  bfd ;

/* Variables and functions */
 int /*<<< orphan*/  BFD_ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FALSE ; 
 int SEC_ALLOC ; 
 int SEC_HAS_CONTENTS ; 
 int SEC_IN_MEMORY ; 
 int SEC_LINKER_CREATED ; 
 int SEC_LOAD ; 
 int SEC_READONLY ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  _bfd_elf_create_got_section (int /*<<< orphan*/ *,struct bfd_link_info*) ; 
 struct _bfd_sparc_elf_link_hash_table* _bfd_sparc_elf_hash_table (struct bfd_link_info*) ; 
 void* bfd_get_section_by_name (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/ * bfd_make_section_with_flags (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  bfd_set_section_alignment (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bfd_boolean
create_got_section (bfd *dynobj, struct bfd_link_info *info)
{
  struct _bfd_sparc_elf_link_hash_table *htab;

  if (! _bfd_elf_create_got_section (dynobj, info))
    return FALSE;

  htab = _bfd_sparc_elf_hash_table (info);
  htab->sgot = bfd_get_section_by_name (dynobj, ".got");
  BFD_ASSERT (htab->sgot != NULL);

  htab->srelgot = bfd_make_section_with_flags (dynobj, ".rela.got",
					       SEC_ALLOC
					       | SEC_LOAD
					       | SEC_HAS_CONTENTS
					       | SEC_IN_MEMORY
					       | SEC_LINKER_CREATED
					       | SEC_READONLY);
  if (htab->srelgot == NULL
      || ! bfd_set_section_alignment (dynobj, htab->srelgot,
				      htab->word_align_power))
    return FALSE;

  if (htab->is_vxworks)
    {
      htab->sgotplt = bfd_get_section_by_name (dynobj, ".got.plt");
      if (!htab->sgotplt)
	return FALSE;
    }

  return TRUE;
}