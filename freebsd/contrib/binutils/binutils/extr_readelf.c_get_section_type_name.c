#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  buff ;
struct TYPE_2__ {int /*<<< orphan*/  e_machine; } ;

/* Variables and functions */
#define  EM_ARM 155 
#define  EM_IA_64 154 
#define  EM_MIPS 153 
#define  EM_MIPS_RS3_LE 152 
#define  EM_PARISC 151 
#define  EM_X86_64 150 
#define  SHT_DYNAMIC 149 
#define  SHT_DYNSYM 148 
#define  SHT_FINI_ARRAY 147 
#define  SHT_GNU_HASH 146 
#define  SHT_GNU_LIBLIST 145 
#define  SHT_GNU_verdef 144 
#define  SHT_GNU_verneed 143 
#define  SHT_GNU_versym 142 
#define  SHT_GROUP 141 
#define  SHT_HASH 140 
 unsigned int SHT_HIOS ; 
 unsigned int SHT_HIPROC ; 
 unsigned int SHT_HIUSER ; 
#define  SHT_INIT_ARRAY 139 
 unsigned int SHT_LOOS ; 
 unsigned int SHT_LOPROC ; 
 unsigned int SHT_LOUSER ; 
#define  SHT_NOBITS 138 
#define  SHT_NOTE 137 
#define  SHT_NULL 136 
#define  SHT_PREINIT_ARRAY 135 
#define  SHT_PROGBITS 134 
#define  SHT_REL 133 
#define  SHT_RELA 132 
#define  SHT_SHLIB 131 
#define  SHT_STRTAB 130 
#define  SHT_SYMTAB 129 
#define  SHT_SYMTAB_SHNDX 128 
 char* _ (char*) ; 
 TYPE_1__ elf_header ; 
 char* get_arm_section_type_name (unsigned int) ; 
 char* get_ia64_section_type_name (unsigned int) ; 
 char* get_mips_section_type_name (unsigned int) ; 
 char* get_parisc_section_type_name (unsigned int) ; 
 char* get_x86_64_section_type_name (unsigned int) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,unsigned int) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static const char *
get_section_type_name (unsigned int sh_type)
{
  static char buff[32];

  switch (sh_type)
    {
    case SHT_NULL:		return "NULL";
    case SHT_PROGBITS:		return "PROGBITS";
    case SHT_SYMTAB:		return "SYMTAB";
    case SHT_STRTAB:		return "STRTAB";
    case SHT_RELA:		return "RELA";
    case SHT_HASH:		return "HASH";
    case SHT_DYNAMIC:		return "DYNAMIC";
    case SHT_NOTE:		return "NOTE";
    case SHT_NOBITS:		return "NOBITS";
    case SHT_REL:		return "REL";
    case SHT_SHLIB:		return "SHLIB";
    case SHT_DYNSYM:		return "DYNSYM";
    case SHT_INIT_ARRAY:	return "INIT_ARRAY";
    case SHT_FINI_ARRAY:	return "FINI_ARRAY";
    case SHT_PREINIT_ARRAY:	return "PREINIT_ARRAY";
    case SHT_GNU_HASH:		return "GNU_HASH";
    case SHT_GROUP:		return "GROUP";
    case SHT_SYMTAB_SHNDX:	return "SYMTAB SECTION INDICIES";
    case SHT_GNU_verdef:	return "VERDEF";
    case SHT_GNU_verneed:	return "VERNEED";
    case SHT_GNU_versym:	return "VERSYM";
    case 0x6ffffff0:		return "VERSYM";
    case 0x6ffffffc:		return "VERDEF";
    case 0x7ffffffd:		return "AUXILIARY";
    case 0x7fffffff:		return "FILTER";
    case SHT_GNU_LIBLIST:	return "GNU_LIBLIST";

    default:
      if ((sh_type >= SHT_LOPROC) && (sh_type <= SHT_HIPROC))
	{
	  const char *result;

	  switch (elf_header.e_machine)
	    {
	    case EM_MIPS:
	    case EM_MIPS_RS3_LE:
	      result = get_mips_section_type_name (sh_type);
	      break;
	    case EM_PARISC:
	      result = get_parisc_section_type_name (sh_type);
	      break;
	    case EM_IA_64:
	      result = get_ia64_section_type_name (sh_type);
	      break;
	    case EM_X86_64:
	      result = get_x86_64_section_type_name (sh_type);
	      break;
	    case EM_ARM:
	      result = get_arm_section_type_name (sh_type);
	      break;
	    default:
	      result = NULL;
	      break;
	    }

	  if (result != NULL)
	    return result;

	  sprintf (buff, "LOPROC+%x", sh_type - SHT_LOPROC);
	}
      else if ((sh_type >= SHT_LOOS) && (sh_type <= SHT_HIOS))
	sprintf (buff, "LOOS+%x", sh_type - SHT_LOOS);
      else if ((sh_type >= SHT_LOUSER) && (sh_type <= SHT_HIUSER))
	sprintf (buff, "LOUSER+%x", sh_type - SHT_LOUSER);
      else
	snprintf (buff, sizeof (buff), _("<unknown>: %x"), sh_type);

      return buff;
    }
}