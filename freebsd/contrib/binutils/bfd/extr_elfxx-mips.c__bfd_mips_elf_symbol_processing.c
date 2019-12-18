#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {int st_shndx; int /*<<< orphan*/  st_size; int /*<<< orphan*/  st_info; } ;
struct TYPE_15__ {TYPE_1__ internal_elf_sym; } ;
typedef  TYPE_2__ elf_symbol_type ;
typedef  int /*<<< orphan*/  bfd ;
struct TYPE_16__ {int /*<<< orphan*/  value; TYPE_4__* section; } ;
typedef  TYPE_3__ asymbol ;
struct TYPE_17__ {char* name; int /*<<< orphan*/  vma; TYPE_5__** symbol_ptr_ptr; TYPE_5__* symbol; struct TYPE_17__* output_section; int /*<<< orphan*/  flags; } ;
typedef  TYPE_4__ asection ;
struct TYPE_18__ {char* name; TYPE_4__* section; void* flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  BFD_ASSERT (int /*<<< orphan*/ ) ; 
 void* BSF_SECTION_SYM ; 
 int /*<<< orphan*/  ELF_ST_TYPE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IRIX_COMPAT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SEC_ALLOC ; 
 int /*<<< orphan*/  SEC_IS_COMMON ; 
 int /*<<< orphan*/  SGI_COMPAT (int /*<<< orphan*/ *) ; 
#define  SHN_COMMON 133 
#define  SHN_MIPS_ACOMMON 132 
#define  SHN_MIPS_DATA 131 
#define  SHN_MIPS_SCOMMON 130 
#define  SHN_MIPS_SUNDEFINED 129 
#define  SHN_MIPS_TEXT 128 
 int /*<<< orphan*/  STT_TLS ; 
 TYPE_4__* bfd_get_section_by_name (int /*<<< orphan*/ *,char*) ; 
 TYPE_4__* bfd_und_section_ptr ; 
 int /*<<< orphan*/  elf_gp_size (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ict_irix6 ; 
 TYPE_4__ mips_elf_acom_section ; 
 TYPE_5__ mips_elf_acom_symbol ; 
 TYPE_5__* mips_elf_acom_symbol_ptr ; 
 TYPE_4__ mips_elf_scom_section ; 
 TYPE_5__ mips_elf_scom_symbol ; 
 TYPE_5__* mips_elf_scom_symbol_ptr ; 

void
_bfd_mips_elf_symbol_processing (bfd *abfd, asymbol *asym)
{
  elf_symbol_type *elfsym;

  elfsym = (elf_symbol_type *) asym;
  switch (elfsym->internal_elf_sym.st_shndx)
    {
    case SHN_MIPS_ACOMMON:
      /* This section is used in a dynamically linked executable file.
	 It is an allocated common section.  The dynamic linker can
	 either resolve these symbols to something in a shared
	 library, or it can just leave them here.  For our purposes,
	 we can consider these symbols to be in a new section.  */
      if (mips_elf_acom_section.name == NULL)
	{
	  /* Initialize the acommon section.  */
	  mips_elf_acom_section.name = ".acommon";
	  mips_elf_acom_section.flags = SEC_ALLOC;
	  mips_elf_acom_section.output_section = &mips_elf_acom_section;
	  mips_elf_acom_section.symbol = &mips_elf_acom_symbol;
	  mips_elf_acom_section.symbol_ptr_ptr = &mips_elf_acom_symbol_ptr;
	  mips_elf_acom_symbol.name = ".acommon";
	  mips_elf_acom_symbol.flags = BSF_SECTION_SYM;
	  mips_elf_acom_symbol.section = &mips_elf_acom_section;
	  mips_elf_acom_symbol_ptr = &mips_elf_acom_symbol;
	}
      asym->section = &mips_elf_acom_section;
      break;

    case SHN_COMMON:
      /* Common symbols less than the GP size are automatically
	 treated as SHN_MIPS_SCOMMON symbols on IRIX5.  */
      if (asym->value > elf_gp_size (abfd)
	  || ELF_ST_TYPE (elfsym->internal_elf_sym.st_info) == STT_TLS
	  || IRIX_COMPAT (abfd) == ict_irix6)
	break;
      /* Fall through.  */
    case SHN_MIPS_SCOMMON:
      if (mips_elf_scom_section.name == NULL)
	{
	  /* Initialize the small common section.  */
	  mips_elf_scom_section.name = ".scommon";
	  mips_elf_scom_section.flags = SEC_IS_COMMON;
	  mips_elf_scom_section.output_section = &mips_elf_scom_section;
	  mips_elf_scom_section.symbol = &mips_elf_scom_symbol;
	  mips_elf_scom_section.symbol_ptr_ptr = &mips_elf_scom_symbol_ptr;
	  mips_elf_scom_symbol.name = ".scommon";
	  mips_elf_scom_symbol.flags = BSF_SECTION_SYM;
	  mips_elf_scom_symbol.section = &mips_elf_scom_section;
	  mips_elf_scom_symbol_ptr = &mips_elf_scom_symbol;
	}
      asym->section = &mips_elf_scom_section;
      asym->value = elfsym->internal_elf_sym.st_size;
      break;

    case SHN_MIPS_SUNDEFINED:
      asym->section = bfd_und_section_ptr;
      break;

    case SHN_MIPS_TEXT:
      {
	asection *section = bfd_get_section_by_name (abfd, ".text");

	BFD_ASSERT (SGI_COMPAT (abfd));
	if (section != NULL)
	  {
	    asym->section = section;
	    /* MIPS_TEXT is a bit special, the address is not an offset
	       to the base of the .text section.  So substract the section
	       base address to make it an offset.  */
	    asym->value -= section->vma;
	  }
      }
      break;

    case SHN_MIPS_DATA:
      {
	asection *section = bfd_get_section_by_name (abfd, ".data");

	BFD_ASSERT (SGI_COMPAT (abfd));
	if (section != NULL)
	  {
	    asym->section = section;
	    /* MIPS_DATA is a bit special, the address is not an offset
	       to the base of the .data section.  So substract the section
	       base address to make it an offset.  */
	    asym->value -= section->vma;
	  }
      }
      break;
    }
}