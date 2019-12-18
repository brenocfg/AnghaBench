#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct bfd_link_info {int /*<<< orphan*/  shared; } ;
struct alpha_elf_got_entry {scalar_t__ use_count; int /*<<< orphan*/  reloc_type; struct alpha_elf_got_entry* next; } ;
typedef  int /*<<< orphan*/  bfd ;
struct TYPE_10__ {int size; } ;
typedef  TYPE_2__ asection ;
struct TYPE_14__ {int /*<<< orphan*/ * got_list; } ;
struct TYPE_13__ {struct alpha_elf_got_entry** local_got_entries; int /*<<< orphan*/ * in_got_link_next; int /*<<< orphan*/ * got_link_next; } ;
struct TYPE_12__ {int /*<<< orphan*/ * dynobj; } ;
struct TYPE_9__ {int sh_info; } ;
struct TYPE_11__ {TYPE_1__ symtab_hdr; } ;
typedef  int /*<<< orphan*/  Elf64_External_Rela ;

/* Variables and functions */
 int /*<<< orphan*/  BFD_ASSERT (int) ; 
 scalar_t__ alpha_dynamic_entries_for_reloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_7__* alpha_elf_hash_table (struct bfd_link_info*) ; 
 int /*<<< orphan*/  alpha_elf_link_hash_traverse (TYPE_7__*,int /*<<< orphan*/ ,struct bfd_link_info*) ; 
 TYPE_6__* alpha_elf_tdata (int /*<<< orphan*/ *) ; 
 TYPE_2__* bfd_get_section_by_name (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  elf64_alpha_size_rela_got_1 ; 
 TYPE_4__* elf_hash_table (struct bfd_link_info*) ; 
 TYPE_3__* elf_tdata (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
elf64_alpha_size_rela_got_section (struct bfd_link_info *info)
{
  unsigned long entries;
  bfd *i, *dynobj;
  asection *srel;

  /* Shared libraries often require RELATIVE relocs, and some relocs
     require attention for the main application as well.  */

  entries = 0;
  for (i = alpha_elf_hash_table(info)->got_list;
       i ; i = alpha_elf_tdata(i)->got_link_next)
    {
      bfd *j;

      for (j = i; j ; j = alpha_elf_tdata(j)->in_got_link_next)
	{
	  struct alpha_elf_got_entry **local_got_entries, *gotent;
	  int k, n;

	  local_got_entries = alpha_elf_tdata(j)->local_got_entries;
	  if (!local_got_entries)
	    continue;

	  for (k = 0, n = elf_tdata(j)->symtab_hdr.sh_info; k < n; ++k)
	    for (gotent = local_got_entries[k];
		 gotent ; gotent = gotent->next)
	      if (gotent->use_count > 0)
		entries += (alpha_dynamic_entries_for_reloc
			    (gotent->reloc_type, 0, info->shared));
	}
    }

  dynobj = elf_hash_table(info)->dynobj;
  srel = bfd_get_section_by_name (dynobj, ".rela.got");
  if (!srel)
    {
      BFD_ASSERT (entries == 0);
      return;
    }
  srel->size = sizeof (Elf64_External_Rela) * entries;

  /* Now do the non-local symbols.  */
  alpha_elf_link_hash_traverse (alpha_elf_hash_table (info),
				elf64_alpha_size_rela_got_1, info);
}