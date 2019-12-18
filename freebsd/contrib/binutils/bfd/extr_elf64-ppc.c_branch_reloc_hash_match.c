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
struct elf_link_hash_entry {TYPE_3__ root; } ;
struct ppc_link_hash_entry {struct elf_link_hash_entry elf; } ;
typedef  enum elf_ppc64_reloc_type { ____Placeholder_elf_ppc64_reloc_type } elf_ppc64_reloc_type ;
typedef  int /*<<< orphan*/  bfd_boolean ;
typedef  int /*<<< orphan*/  bfd ;
struct TYPE_11__ {unsigned int sh_info; } ;
struct TYPE_13__ {TYPE_4__ symtab_hdr; } ;
struct TYPE_12__ {int /*<<< orphan*/  r_info; } ;
typedef  TYPE_4__ Elf_Internal_Shdr ;
typedef  TYPE_5__ Elf_Internal_Rela ;

/* Variables and functions */
 unsigned int ELF64_R_SYM (int /*<<< orphan*/ ) ; 
 int ELF64_R_TYPE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FALSE ; 
 int R_PPC64_ADDR14 ; 
 int R_PPC64_ADDR14_BRNTAKEN ; 
 int R_PPC64_ADDR14_BRTAKEN ; 
 int R_PPC64_ADDR24 ; 
 int R_PPC64_REL14 ; 
 int R_PPC64_REL14_BRNTAKEN ; 
 int R_PPC64_REL14_BRTAKEN ; 
 int R_PPC64_REL24 ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ bfd_link_hash_indirect ; 
 scalar_t__ bfd_link_hash_warning ; 
 struct elf_link_hash_entry** elf_sym_hashes (int /*<<< orphan*/  const*) ; 
 TYPE_6__* elf_tdata (int /*<<< orphan*/  const*) ; 

__attribute__((used)) static bfd_boolean
branch_reloc_hash_match (const bfd *ibfd,
			 const Elf_Internal_Rela *rel,
			 const struct ppc_link_hash_entry *hash1,
			 const struct ppc_link_hash_entry *hash2)
{
  Elf_Internal_Shdr *symtab_hdr = &elf_tdata (ibfd)->symtab_hdr;
  enum elf_ppc64_reloc_type r_type = ELF64_R_TYPE (rel->r_info);
  unsigned int r_symndx = ELF64_R_SYM (rel->r_info);

  if (r_symndx >= symtab_hdr->sh_info
      && (r_type == R_PPC64_REL24
	  || r_type == R_PPC64_REL14
	  || r_type == R_PPC64_REL14_BRTAKEN
	  || r_type == R_PPC64_REL14_BRNTAKEN
	  || r_type == R_PPC64_ADDR24
	  || r_type == R_PPC64_ADDR14
	  || r_type == R_PPC64_ADDR14_BRTAKEN
	  || r_type == R_PPC64_ADDR14_BRNTAKEN))
    {
      struct elf_link_hash_entry **sym_hashes = elf_sym_hashes (ibfd);
      struct elf_link_hash_entry *h;

      h = sym_hashes[r_symndx - symtab_hdr->sh_info];
      while (h->root.type == bfd_link_hash_indirect
	     || h->root.type == bfd_link_hash_warning)
	h = (struct elf_link_hash_entry *) h->root.u.i.link;
      if (h == &hash1->elf || h == &hash2->elf)
	return TRUE;
    }
  return FALSE;
}