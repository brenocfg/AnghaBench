#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {int flags; } ;
typedef  TYPE_1__ bfd ;
typedef  int /*<<< orphan*/  asection ;
struct TYPE_15__ {unsigned int sh_info; int /*<<< orphan*/  sh_link; } ;
struct TYPE_16__ {TYPE_3__ symtab_hdr; } ;
struct TYPE_14__ {int /*<<< orphan*/  st_value; int /*<<< orphan*/  st_name; int /*<<< orphan*/  st_info; int /*<<< orphan*/  st_shndx; } ;
typedef  TYPE_2__ Elf_Internal_Sym ;
typedef  TYPE_3__ Elf_Internal_Shdr ;

/* Variables and functions */
 int /*<<< orphan*/  BFD_ARM_SPECIAL_SYM_TYPE_MAP ; 
 int DYNAMIC ; 
 scalar_t__ ELF_ST_BIND (int /*<<< orphan*/ ) ; 
 scalar_t__ STB_LOCAL ; 
 TYPE_2__* bfd_elf_get_elf_syms (TYPE_1__*,TYPE_3__*,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 char* bfd_elf_string_from_elf_section (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ bfd_get_flavour (TYPE_1__*) ; 
 scalar_t__ bfd_is_arm_special_symbol_name (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * bfd_section_from_elf_index (TYPE_1__*,int /*<<< orphan*/ ) ; 
 scalar_t__ bfd_target_elf_flavour ; 
 int /*<<< orphan*/  elf32_arm_section_map_add (int /*<<< orphan*/ *,char const,int /*<<< orphan*/ ) ; 
 TYPE_4__* elf_tdata (TYPE_1__*) ; 

void
bfd_elf32_arm_init_maps (bfd *abfd)
{
  Elf_Internal_Sym *isymbuf;
  Elf_Internal_Shdr *hdr;
  unsigned int i, localsyms;

  if (bfd_get_flavour (abfd) != bfd_target_elf_flavour || elf_tdata (abfd) == NULL)
    return;

  if ((abfd->flags & DYNAMIC) != 0)
    return;

  hdr = &elf_tdata (abfd)->symtab_hdr;
  localsyms = hdr->sh_info;

  /* Obtain a buffer full of symbols for this BFD. The hdr->sh_info field
     should contain the number of local symbols, which should come before any
     global symbols.  Mapping symbols are always local.  */
  isymbuf = bfd_elf_get_elf_syms (abfd, hdr, localsyms, 0, NULL, NULL,
				  NULL);

  /* No internal symbols read?  Skip this BFD.  */
  if (isymbuf == NULL)
    return;

  for (i = 0; i < localsyms; i++)
    {
      Elf_Internal_Sym *isym = &isymbuf[i];
      asection *sec = bfd_section_from_elf_index (abfd, isym->st_shndx);
      const char *name;
      
      if (sec != NULL
          && ELF_ST_BIND (isym->st_info) == STB_LOCAL)
        {
          name = bfd_elf_string_from_elf_section (abfd,
            hdr->sh_link, isym->st_name);
          
          if (bfd_is_arm_special_symbol_name (name,
					      BFD_ARM_SPECIAL_SYM_TYPE_MAP))
            elf32_arm_section_map_add (sec, name[1], isym->st_value);
        }
    }
}