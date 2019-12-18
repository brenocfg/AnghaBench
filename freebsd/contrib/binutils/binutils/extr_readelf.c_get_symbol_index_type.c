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
struct TYPE_2__ {int /*<<< orphan*/  e_machine; int /*<<< orphan*/ * e_ident; } ;

/* Variables and functions */
 size_t EI_OSABI ; 
 int /*<<< orphan*/  ELFOSABI_HPUX ; 
 int /*<<< orphan*/  EM_IA_64 ; 
 int /*<<< orphan*/  EM_MIPS ; 
 int /*<<< orphan*/  EM_X86_64 ; 
#define  SHN_ABS 130 
#define  SHN_COMMON 129 
 unsigned int SHN_HIOS ; 
 unsigned int SHN_HIPROC ; 
 unsigned int SHN_HIRESERVE ; 
 unsigned int SHN_IA_64_ANSI_COMMON ; 
 unsigned int SHN_LOOS ; 
 unsigned int SHN_LOPROC ; 
 unsigned int SHN_LORESERVE ; 
 unsigned int SHN_MIPS_SCOMMON ; 
 unsigned int SHN_MIPS_SUNDEFINED ; 
#define  SHN_UNDEF 128 
 unsigned int SHN_X86_64_LCOMMON ; 
 TYPE_1__ elf_header ; 
 int /*<<< orphan*/  sprintf (char*,char*,unsigned int) ; 

__attribute__((used)) static const char *
get_symbol_index_type (unsigned int type)
{
  static char buff[32];

  switch (type)
    {
    case SHN_UNDEF:	return "UND";
    case SHN_ABS:	return "ABS";
    case SHN_COMMON:	return "COM";
    default:
      if (type == SHN_IA_64_ANSI_COMMON
	  && elf_header.e_machine == EM_IA_64
	  && elf_header.e_ident[EI_OSABI] == ELFOSABI_HPUX)
	return "ANSI_COM";
      else if (elf_header.e_machine == EM_X86_64
	       && type == SHN_X86_64_LCOMMON)
	return "LARGE_COM";
      else if (type == SHN_MIPS_SCOMMON
	       && elf_header.e_machine == EM_MIPS)
	return "SCOM";
      else if (type == SHN_MIPS_SUNDEFINED
	       && elf_header.e_machine == EM_MIPS)
	return "SUND";
      else if (type >= SHN_LOPROC && type <= SHN_HIPROC)
	sprintf (buff, "PRC[0x%04x]", type);
      else if (type >= SHN_LOOS && type <= SHN_HIOS)
	sprintf (buff, "OS [0x%04x]", type);
      else if (type >= SHN_LORESERVE && type <= SHN_HIRESERVE)
	sprintf (buff, "RSV[0x%04x]", type);
      else
	sprintf (buff, "%3d", type);
      break;
    }

  return buff;
}