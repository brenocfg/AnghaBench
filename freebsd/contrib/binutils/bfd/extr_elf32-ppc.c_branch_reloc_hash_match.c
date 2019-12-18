#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {scalar_t__ link; } ;
struct TYPE_9__ {TYPE_1__ i; } ;
struct TYPE_10__ {scalar_t__ type; TYPE_2__ u; } ;
typedef  struct elf_link_hash_entry {TYPE_3__ root; } const elf_link_hash_entry ;
typedef  enum elf_ppc_reloc_type { ____Placeholder_elf_ppc_reloc_type } elf_ppc_reloc_type ;
typedef  int /*<<< orphan*/  bfd_boolean ;
typedef  int /*<<< orphan*/  bfd ;
struct TYPE_11__ {unsigned int sh_info; } ;
struct TYPE_13__ {TYPE_4__ symtab_hdr; } ;
struct TYPE_12__ {int /*<<< orphan*/  r_info; } ;
typedef  TYPE_4__ Elf_Internal_Shdr ;
typedef  TYPE_5__ Elf_Internal_Rela ;

/* Variables and functions */
 unsigned int ELF32_R_SYM (int /*<<< orphan*/ ) ; 
 int ELF32_R_TYPE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FALSE ; 
 int R_PPC_ADDR14 ; 
 int R_PPC_ADDR14_BRNTAKEN ; 
 int R_PPC_ADDR14_BRTAKEN ; 
 int R_PPC_ADDR24 ; 
 int R_PPC_LOCAL24PC ; 
 int R_PPC_PLTREL24 ; 
 int R_PPC_REL14 ; 
 int R_PPC_REL14_BRNTAKEN ; 
 int R_PPC_REL14_BRTAKEN ; 
 int R_PPC_REL24 ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ bfd_link_hash_indirect ; 
 scalar_t__ bfd_link_hash_warning ; 
 struct elf_link_hash_entry const** elf_sym_hashes (int /*<<< orphan*/  const*) ; 
 TYPE_6__* elf_tdata (int /*<<< orphan*/  const*) ; 

__attribute__((used)) static bfd_boolean
branch_reloc_hash_match (const bfd *ibfd,
			 const Elf_Internal_Rela *rel,
			 const struct elf_link_hash_entry *hash)
{
  Elf_Internal_Shdr *symtab_hdr = &elf_tdata (ibfd)->symtab_hdr;
  enum elf_ppc_reloc_type r_type = ELF32_R_TYPE (rel->r_info);
  unsigned int r_symndx = ELF32_R_SYM (rel->r_info);

  if (r_symndx >= symtab_hdr->sh_info
      && (r_type == R_PPC_PLTREL24
	  || r_type == R_PPC_LOCAL24PC
	  || r_type == R_PPC_REL14
	  || r_type == R_PPC_REL14_BRTAKEN
	  || r_type == R_PPC_REL14_BRNTAKEN
	  || r_type == R_PPC_REL24
	  || r_type == R_PPC_ADDR24
	  || r_type == R_PPC_ADDR14
	  || r_type == R_PPC_ADDR14_BRTAKEN
	  || r_type == R_PPC_ADDR14_BRNTAKEN))
    {
      struct elf_link_hash_entry **sym_hashes = elf_sym_hashes (ibfd);
      struct elf_link_hash_entry *h;

      h = sym_hashes[r_symndx - symtab_hdr->sh_info];
      while (h->root.type == bfd_link_hash_indirect
	     || h->root.type == bfd_link_hash_warning)
	h = (struct elf_link_hash_entry *) h->root.u.i.link;
      if (h == hash)
	return TRUE;
    }
  return FALSE;
}