#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_6__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct elf_link_hash_entry {int dummy; } ;
struct bfd_link_info {scalar_t__ relocatable; } ;
typedef  int /*<<< orphan*/  bfd_boolean ;
typedef  int /*<<< orphan*/  bfd ;
struct TYPE_7__ {int reloc_count; } ;
typedef  TYPE_1__ asection ;
struct TYPE_8__ {int sh_size; unsigned long sh_info; } ;
struct TYPE_10__ {TYPE_2__ symtab_hdr; } ;
struct TYPE_9__ {int /*<<< orphan*/  r_info; } ;
typedef  TYPE_2__ Elf_Internal_Shdr ;
typedef  TYPE_3__ Elf_Internal_Rela ;
typedef  int /*<<< orphan*/  Elf32_External_Sym ;

/* Variables and functions */
 unsigned long ELF32_R_SYM (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  elf_bad_symtab (int /*<<< orphan*/ *) ; 
 struct elf_link_hash_entry** elf_sym_hashes (int /*<<< orphan*/ *) ; 
 TYPE_6__* elf_tdata (int /*<<< orphan*/ *) ; 

__attribute__((used)) static bfd_boolean
mep_elf_check_relocs
    (bfd *                     abfd,
     struct bfd_link_info *    info,
     asection *                sec,
     const Elf_Internal_Rela * relocs)
{
  Elf_Internal_Shdr *           symtab_hdr;
  struct elf_link_hash_entry ** sym_hashes;
  struct elf_link_hash_entry ** sym_hashes_end;
  const Elf_Internal_Rela *     rel;
  const Elf_Internal_Rela *     rel_end;

  if (info->relocatable)
    return TRUE;

  symtab_hdr = &elf_tdata (abfd)->symtab_hdr;
  sym_hashes = elf_sym_hashes (abfd);
  sym_hashes_end = sym_hashes + symtab_hdr->sh_size / sizeof (Elf32_External_Sym);
  if (!elf_bad_symtab (abfd))
    sym_hashes_end -= symtab_hdr->sh_info;

  rel_end = relocs + sec->reloc_count;
  for (rel = relocs; rel < rel_end; rel++)
    {
      struct elf_link_hash_entry *h;
      unsigned long r_symndx;

      r_symndx = ELF32_R_SYM (rel->r_info);
      if (r_symndx < symtab_hdr->sh_info)
        h = NULL;
      else
        h = sym_hashes[r_symndx - symtab_hdr->sh_info];
    }
  return TRUE;
}