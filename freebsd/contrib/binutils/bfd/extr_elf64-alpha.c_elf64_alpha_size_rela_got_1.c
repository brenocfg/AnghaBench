#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_7__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct bfd_link_info {int /*<<< orphan*/  shared; } ;
struct TYPE_8__ {scalar_t__ link; } ;
struct TYPE_9__ {TYPE_1__ i; } ;
struct TYPE_10__ {scalar_t__ type; TYPE_2__ u; } ;
struct TYPE_13__ {TYPE_3__ root; scalar_t__ needs_plt; } ;
struct alpha_elf_link_hash_entry {struct alpha_elf_got_entry* got_entries; TYPE_7__ root; } ;
struct alpha_elf_got_entry {scalar_t__ use_count; int /*<<< orphan*/  reloc_type; struct alpha_elf_got_entry* next; } ;
typedef  int /*<<< orphan*/  bfd_boolean ;
typedef  int /*<<< orphan*/  bfd ;
struct TYPE_11__ {int size; } ;
typedef  TYPE_4__ asection ;
struct TYPE_12__ {int /*<<< orphan*/ * dynobj; } ;
typedef  int /*<<< orphan*/  Elf64_External_Rela ;

/* Variables and functions */
 int /*<<< orphan*/  BFD_ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ alpha_dynamic_entries_for_reloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  alpha_elf_dynamic_symbol_p (TYPE_7__*,struct bfd_link_info*) ; 
 TYPE_4__* bfd_get_section_by_name (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ bfd_link_hash_undefweak ; 
 scalar_t__ bfd_link_hash_warning ; 
 TYPE_5__* elf_hash_table (struct bfd_link_info*) ; 

__attribute__((used)) static bfd_boolean
elf64_alpha_size_rela_got_1 (struct alpha_elf_link_hash_entry *h,
			     struct bfd_link_info *info)
{
  bfd_boolean dynamic;
  struct alpha_elf_got_entry *gotent;
  unsigned long entries;

  if (h->root.root.type == bfd_link_hash_warning)
    h = (struct alpha_elf_link_hash_entry *) h->root.root.u.i.link;

  /* If we're using a plt for this symbol, then all of its relocations
     for its got entries go into .rela.plt.  */
  if (h->root.needs_plt)
    return TRUE;

  /* If the symbol is dynamic, we'll need all the relocations in their
     natural form.  If this is a shared object, and it has been forced
     local, we'll need the same number of RELATIVE relocations.  */
  dynamic = alpha_elf_dynamic_symbol_p (&h->root, info);

  /* If the symbol is a hidden undefined weak, then we never have any
     relocations.  Avoid the loop which may want to add RELATIVE relocs
     based on info->shared.  */
  if (h->root.root.type == bfd_link_hash_undefweak && !dynamic)
    return TRUE;

  entries = 0;
  for (gotent = h->got_entries; gotent ; gotent = gotent->next)
    if (gotent->use_count > 0)
      entries += alpha_dynamic_entries_for_reloc (gotent->reloc_type,
						  dynamic, info->shared);

  if (entries > 0)
    {
      bfd *dynobj = elf_hash_table(info)->dynobj;
      asection *srel = bfd_get_section_by_name (dynobj, ".rela.got");
      BFD_ASSERT (srel != NULL);
      srel->size += sizeof (Elf64_External_Rela) * entries;
    }

  return TRUE;
}