#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int st_shndx; int /*<<< orphan*/  st_size; } ;
struct TYPE_9__ {TYPE_1__ internal_elf_sym; } ;
typedef  TYPE_2__ elf_symbol_type ;
typedef  int /*<<< orphan*/  bfd ;
struct TYPE_10__ {int /*<<< orphan*/  value; TYPE_6__* section; } ;
typedef  TYPE_3__ asymbol ;
struct TYPE_12__ {char* name; TYPE_4__** symbol_ptr_ptr; TYPE_4__* symbol; struct TYPE_12__* output_section; int /*<<< orphan*/  flags; } ;
struct TYPE_11__ {char* name; TYPE_6__* section; int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  BSF_SECTION_SYM ; 
 int /*<<< orphan*/  SEC_IS_COMMON ; 
#define  SHN_COMMON 129 
#define  SHN_SCORE_SCOMMON 128 
 int /*<<< orphan*/  elf_gp_size (int /*<<< orphan*/ *) ; 
 TYPE_6__ score_elf_scom_section ; 
 TYPE_4__ score_elf_scom_symbol ; 
 TYPE_4__* score_elf_scom_symbol_ptr ; 

__attribute__((used)) static void
_bfd_score_elf_symbol_processing (bfd *abfd, asymbol *asym)
{
  elf_symbol_type *elfsym;

  elfsym = (elf_symbol_type *) asym;
  switch (elfsym->internal_elf_sym.st_shndx)
    {
    case SHN_COMMON:
      if (asym->value > elf_gp_size (abfd))
        break;
      /* Fall through.  */
    case SHN_SCORE_SCOMMON:
      if (score_elf_scom_section.name == NULL)
        {
          /* Initialize the small common section.  */
          score_elf_scom_section.name = ".scommon";
          score_elf_scom_section.flags = SEC_IS_COMMON;
          score_elf_scom_section.output_section = &score_elf_scom_section;
          score_elf_scom_section.symbol = &score_elf_scom_symbol;
          score_elf_scom_section.symbol_ptr_ptr = &score_elf_scom_symbol_ptr;
          score_elf_scom_symbol.name = ".scommon";
          score_elf_scom_symbol.flags = BSF_SECTION_SYM;
          score_elf_scom_symbol.section = &score_elf_scom_section;
          score_elf_scom_symbol_ptr = &score_elf_scom_symbol;
        }
      asym->section = &score_elf_scom_section;
      asym->value = elfsym->internal_elf_sym.st_size;
      break;
    }
}