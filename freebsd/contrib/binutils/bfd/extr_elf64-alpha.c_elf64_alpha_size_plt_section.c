#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct bfd_link_info {int dummy; } ;
typedef  int /*<<< orphan*/  bfd ;
struct TYPE_5__ {unsigned long size; } ;
typedef  TYPE_1__ asection ;
struct TYPE_6__ {int /*<<< orphan*/ * dynobj; } ;
typedef  int /*<<< orphan*/  Elf64_External_Rela ;

/* Variables and functions */
 unsigned long NEW_PLT_ENTRY_SIZE ; 
 unsigned long NEW_PLT_HEADER_SIZE ; 
 unsigned long OLD_PLT_ENTRY_SIZE ; 
 unsigned long OLD_PLT_HEADER_SIZE ; 
 int /*<<< orphan*/  alpha_elf_hash_table (struct bfd_link_info*) ; 
 int /*<<< orphan*/  alpha_elf_link_hash_traverse (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 TYPE_1__* bfd_get_section_by_name (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  elf64_alpha_size_plt_section_1 ; 
 scalar_t__ elf64_alpha_use_secureplt ; 
 TYPE_2__* elf_hash_table (struct bfd_link_info*) ; 

__attribute__((used)) static void
elf64_alpha_size_plt_section (struct bfd_link_info *info)
{
  asection *splt, *spltrel, *sgotplt;
  unsigned long entries;
  bfd *dynobj;

  dynobj = elf_hash_table(info)->dynobj;
  splt = bfd_get_section_by_name (dynobj, ".plt");
  if (splt == NULL)
    return;

  splt->size = 0;

  alpha_elf_link_hash_traverse (alpha_elf_hash_table (info),
				elf64_alpha_size_plt_section_1, splt);

  /* Every plt entry requires a JMP_SLOT relocation.  */
  spltrel = bfd_get_section_by_name (dynobj, ".rela.plt");
  entries = 0;
  if (splt->size)
    {
      if (elf64_alpha_use_secureplt)
	entries = (splt->size - NEW_PLT_HEADER_SIZE) / NEW_PLT_ENTRY_SIZE;
      else
	entries = (splt->size - OLD_PLT_HEADER_SIZE) / OLD_PLT_ENTRY_SIZE;
    }
  spltrel->size = entries * sizeof (Elf64_External_Rela);

  /* When using the secureplt, we need two words somewhere in the data
     segment for the dynamic linker to tell us where to go.  This is the
     entire contents of the .got.plt section.  */
  if (elf64_alpha_use_secureplt)
    {
      sgotplt = bfd_get_section_by_name (dynobj, ".got.plt");
      sgotplt->size = entries ? 16 : 0;
    }
}