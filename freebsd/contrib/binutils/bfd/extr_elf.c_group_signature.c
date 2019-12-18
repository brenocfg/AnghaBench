#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  bfd ;
struct TYPE_7__ {size_t sh_link; scalar_t__ sh_type; int /*<<< orphan*/  sh_info; } ;
struct TYPE_8__ {TYPE_1__ symtab_hdr; } ;
typedef  int /*<<< orphan*/  Elf_Internal_Sym ;
typedef  TYPE_1__ Elf_Internal_Shdr ;
typedef  int /*<<< orphan*/  Elf_External_Sym_Shndx ;
typedef  int /*<<< orphan*/  Elf64_External_Sym ;

/* Variables and functions */
 scalar_t__ SHT_SYMTAB ; 
 int /*<<< orphan*/ * bfd_elf_get_elf_syms (int /*<<< orphan*/ *,TYPE_1__*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,unsigned char*,int /*<<< orphan*/ *) ; 
 char const* bfd_elf_sym_name (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bfd_section_from_shdr (int /*<<< orphan*/ *,size_t) ; 
 TYPE_1__** elf_elfsections (int /*<<< orphan*/ *) ; 
 TYPE_3__* elf_tdata (int /*<<< orphan*/ *) ; 

__attribute__((used)) static const char *
group_signature (bfd *abfd, Elf_Internal_Shdr *ghdr)
{
  Elf_Internal_Shdr *hdr;
  unsigned char esym[sizeof (Elf64_External_Sym)];
  Elf_External_Sym_Shndx eshndx;
  Elf_Internal_Sym isym;

  /* First we need to ensure the symbol table is available.  Make sure
     that it is a symbol table section.  */
  hdr = elf_elfsections (abfd) [ghdr->sh_link];
  if (hdr->sh_type != SHT_SYMTAB
      || ! bfd_section_from_shdr (abfd, ghdr->sh_link))
    return NULL;

  /* Go read the symbol.  */
  hdr = &elf_tdata (abfd)->symtab_hdr;
  if (bfd_elf_get_elf_syms (abfd, hdr, 1, ghdr->sh_info,
			    &isym, esym, &eshndx) == NULL)
    return NULL;

  return bfd_elf_sym_name (abfd, hdr, &isym, NULL);
}