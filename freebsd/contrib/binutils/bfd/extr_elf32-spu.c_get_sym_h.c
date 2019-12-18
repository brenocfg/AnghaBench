#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_9__ ;
typedef  struct TYPE_17__   TYPE_6__ ;
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {int /*<<< orphan*/ * section; } ;
struct TYPE_12__ {scalar_t__ link; } ;
struct TYPE_14__ {TYPE_2__ def; TYPE_1__ i; } ;
struct TYPE_15__ {scalar_t__ type; TYPE_3__ u; } ;
struct elf_link_hash_entry {TYPE_4__ root; } ;
typedef  int /*<<< orphan*/  bfd_boolean ;
typedef  int /*<<< orphan*/  bfd ;
typedef  int /*<<< orphan*/  asection ;
struct TYPE_17__ {unsigned long sh_info; unsigned char* contents; size_t sh_size; size_t sh_entsize; } ;
struct TYPE_18__ {TYPE_6__ symtab_hdr; } ;
struct TYPE_16__ {scalar_t__ st_shndx; } ;
typedef  TYPE_5__ Elf_Internal_Sym ;
typedef  TYPE_6__ Elf_Internal_Shdr ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ SHN_HIRESERVE ; 
 scalar_t__ SHN_LORESERVE ; 
 scalar_t__ SHN_UNDEF ; 
 int /*<<< orphan*/  TRUE ; 
 TYPE_5__* bfd_elf_get_elf_syms (int /*<<< orphan*/ *,TYPE_6__*,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ bfd_link_hash_defined ; 
 scalar_t__ bfd_link_hash_defweak ; 
 scalar_t__ bfd_link_hash_indirect ; 
 scalar_t__ bfd_link_hash_warning ; 
 int /*<<< orphan*/ * bfd_section_from_elf_index (int /*<<< orphan*/ *,scalar_t__) ; 
 struct elf_link_hash_entry** elf_sym_hashes (int /*<<< orphan*/ *) ; 
 TYPE_9__* elf_tdata (int /*<<< orphan*/ *) ; 

__attribute__((used)) static bfd_boolean
get_sym_h (struct elf_link_hash_entry **hp,
	   Elf_Internal_Sym **symp,
	   asection **symsecp,
	   Elf_Internal_Sym **locsymsp,
	   unsigned long r_symndx,
	   bfd *ibfd)
{
  Elf_Internal_Shdr *symtab_hdr = &elf_tdata (ibfd)->symtab_hdr;

  if (r_symndx >= symtab_hdr->sh_info)
    {
      struct elf_link_hash_entry **sym_hashes = elf_sym_hashes (ibfd);
      struct elf_link_hash_entry *h;

      h = sym_hashes[r_symndx - symtab_hdr->sh_info];
      while (h->root.type == bfd_link_hash_indirect
	     || h->root.type == bfd_link_hash_warning)
	h = (struct elf_link_hash_entry *) h->root.u.i.link;

      if (hp != NULL)
	*hp = h;

      if (symp != NULL)
	*symp = NULL;

      if (symsecp != NULL)
	{
	  asection *symsec = NULL;
	  if (h->root.type == bfd_link_hash_defined
	      || h->root.type == bfd_link_hash_defweak)
	    symsec = h->root.u.def.section;
	  *symsecp = symsec;
	}
    }
  else
    {
      Elf_Internal_Sym *sym;
      Elf_Internal_Sym *locsyms = *locsymsp;

      if (locsyms == NULL)
	{
	  locsyms = (Elf_Internal_Sym *) symtab_hdr->contents;
	  if (locsyms == NULL)
	    {
	      size_t symcount = symtab_hdr->sh_info;

	      /* If we are reading symbols into the contents, then
		 read the global syms too.  This is done to cache
		 syms for later stack analysis.  */
	      if ((unsigned char **) locsymsp == &symtab_hdr->contents)
		symcount = symtab_hdr->sh_size / symtab_hdr->sh_entsize;
	      locsyms = bfd_elf_get_elf_syms (ibfd, symtab_hdr, symcount, 0,
					      NULL, NULL, NULL);
	    }
	  if (locsyms == NULL)
	    return FALSE;
	  *locsymsp = locsyms;
	}
      sym = locsyms + r_symndx;

      if (hp != NULL)
	*hp = NULL;

      if (symp != NULL)
	*symp = sym;

      if (symsecp != NULL)
	{
	  asection *symsec = NULL;
	  if ((sym->st_shndx != SHN_UNDEF
	       && sym->st_shndx < SHN_LORESERVE)
	      || sym->st_shndx > SHN_HIRESERVE)
	    symsec = bfd_section_from_elf_index (ibfd, sym->st_shndx);
	  *symsecp = symsec;
	}
    }

  return TRUE;
}