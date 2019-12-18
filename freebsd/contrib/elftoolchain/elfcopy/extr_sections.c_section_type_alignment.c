#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */

/* Variables and functions */
 int ELFCLASS64 ; 
#define  SHT_DYNAMIC 150 
#define  SHT_DYNSYM 149 
#define  SHT_FINI_ARRAY 148 
#define  SHT_GNU_HASH 147 
#define  SHT_GNU_LIBLIST 146 
#define  SHT_GROUP 145 
#define  SHT_HASH 144 
#define  SHT_INIT_ARRAY 143 
#define  SHT_NOBITS 142 
#define  SHT_NOTE 141 
#define  SHT_PREINIT_ARRAY 140 
#define  SHT_PROGBITS 139 
#define  SHT_REL 138 
#define  SHT_RELA 137 
#define  SHT_STRTAB 136 
#define  SHT_SUNW_dof 135 
#define  SHT_SUNW_move 134 
#define  SHT_SUNW_syminfo 133 
#define  SHT_SUNW_verdef 132 
#define  SHT_SUNW_verneed 131 
#define  SHT_SUNW_versym 130 
#define  SHT_SYMTAB 129 
#define  SHT_SYMTAB_SHNDX 128 

__attribute__((used)) static int
section_type_alignment(int sht, int class)
{
	switch (sht)
	{
	case SHT_DYNAMIC:
	case SHT_DYNSYM:
	case SHT_FINI_ARRAY:
	case SHT_GNU_HASH:
	case SHT_INIT_ARRAY:
	case SHT_PREINIT_ARRAY:
	case SHT_REL:
	case SHT_RELA:
	case SHT_SYMTAB:
		return (class == ELFCLASS64 ? 8 : 4);
	case SHT_SUNW_move:
		return (8);
	case SHT_GNU_LIBLIST:
	case SHT_GROUP:
	case SHT_HASH:
	case SHT_NOTE:
	case SHT_SUNW_verdef:	/* == SHT_GNU_verdef */
	case SHT_SUNW_verneed:	/* == SHT_GNU_verneed */
	case SHT_SYMTAB_SHNDX:
		return (4);
	case SHT_SUNW_syminfo:
	case SHT_SUNW_versym:	/* == SHT_GNU_versym */
		return (2);
	case SHT_NOBITS:
	case SHT_PROGBITS:
	case SHT_STRTAB:
	case SHT_SUNW_dof:
		return (1);
	}
	return (1);
}