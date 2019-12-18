#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {unsigned int st_shndx; } ;
struct TYPE_6__ {int /*<<< orphan*/  section; } ;
struct TYPE_8__ {TYPE_2__ internal_elf_sym; TYPE_1__ symbol; } ;
typedef  TYPE_3__ elf_symbol_type ;
typedef  int /*<<< orphan*/  bfd_boolean ;
typedef  int /*<<< orphan*/  bfd ;
typedef  int /*<<< orphan*/  asymbol ;
struct TYPE_9__ {unsigned int strtab_section; unsigned int shstrtab_section; unsigned int symtab_shndx_section; } ;

/* Variables and functions */
 unsigned int MAP_DYNSYMTAB ; 
 unsigned int MAP_ONESYMTAB ; 
 unsigned int MAP_SHSTRTAB ; 
 unsigned int MAP_STRTAB ; 
 unsigned int MAP_SYM_SHNDX ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ bfd_get_flavour (int /*<<< orphan*/ *) ; 
 scalar_t__ bfd_is_abs_section (int /*<<< orphan*/ ) ; 
 scalar_t__ bfd_target_elf_flavour ; 
 unsigned int elf_dynsymtab (int /*<<< orphan*/ *) ; 
 unsigned int elf_onesymtab (int /*<<< orphan*/ *) ; 
 TYPE_3__* elf_symbol_from (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_4__* elf_tdata (int /*<<< orphan*/ *) ; 

bfd_boolean
_bfd_elf_copy_private_symbol_data (bfd *ibfd,
				   asymbol *isymarg,
				   bfd *obfd,
				   asymbol *osymarg)
{
  elf_symbol_type *isym, *osym;

  if (bfd_get_flavour (ibfd) != bfd_target_elf_flavour
      || bfd_get_flavour (obfd) != bfd_target_elf_flavour)
    return TRUE;

  isym = elf_symbol_from (ibfd, isymarg);
  osym = elf_symbol_from (obfd, osymarg);

  if (isym != NULL
      && osym != NULL
      && bfd_is_abs_section (isym->symbol.section))
    {
      unsigned int shndx;

      shndx = isym->internal_elf_sym.st_shndx;
      if (shndx == elf_onesymtab (ibfd))
	shndx = MAP_ONESYMTAB;
      else if (shndx == elf_dynsymtab (ibfd))
	shndx = MAP_DYNSYMTAB;
      else if (shndx == elf_tdata (ibfd)->strtab_section)
	shndx = MAP_STRTAB;
      else if (shndx == elf_tdata (ibfd)->shstrtab_section)
	shndx = MAP_SHSTRTAB;
      else if (shndx == elf_tdata (ibfd)->symtab_shndx_section)
	shndx = MAP_SYM_SHNDX;
      osym->internal_elf_sym.st_shndx = shndx;
    }

  return TRUE;
}