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
typedef  int uint32_t ;

/* Variables and functions */
 int ELF_T_ADDR ; 
 int ELF_T_BYTE ; 
 int ELF_T_DYN ; 
 int ELF_T_GNUHASH ; 
 int ELF_T_HALF ; 
 int ELF_T_MOVE ; 
 int ELF_T_NOTE ; 
 int ELF_T_REL ; 
 int ELF_T_RELA ; 
 int ELF_T_SYM ; 
 int ELF_T_SYMINFO ; 
 int ELF_T_VDEF ; 
 int ELF_T_VNEED ; 
 int ELF_T_WORD ; 
#define  SHT_DYNAMIC 150 
#define  SHT_DYNSYM 149 
#define  SHT_FINI_ARRAY 148 
#define  SHT_GNU_HASH 147 
#define  SHT_GNU_LIBLIST 146 
#define  SHT_GROUP 145 
#define  SHT_HASH 144 
 int SHT_HIUSER ; 
#define  SHT_INIT_ARRAY 143 
 int SHT_LOOS ; 
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

int
_libelf_xlate_shtype(uint32_t sht)
{
	/*
	 * Look for known section types.
	 */
	switch (sht) {
	case SHT_DYNAMIC:
		return (ELF_T_DYN);
	case SHT_DYNSYM:
		return (ELF_T_SYM);
	case SHT_FINI_ARRAY:
		return (ELF_T_ADDR);
	case SHT_GNU_HASH:
		return (ELF_T_GNUHASH);
	case SHT_GNU_LIBLIST:
		return (ELF_T_WORD);
	case SHT_GROUP:
		return (ELF_T_WORD);
	case SHT_HASH:
		return (ELF_T_WORD);
	case SHT_INIT_ARRAY:
		return (ELF_T_ADDR);
	case SHT_NOBITS:
		return (ELF_T_BYTE);
	case SHT_NOTE:
		return (ELF_T_NOTE);
	case SHT_PREINIT_ARRAY:
		return (ELF_T_ADDR);
	case SHT_PROGBITS:
		return (ELF_T_BYTE);
	case SHT_REL:
		return (ELF_T_REL);
	case SHT_RELA:
		return (ELF_T_RELA);
	case SHT_STRTAB:
		return (ELF_T_BYTE);
	case SHT_SYMTAB:
		return (ELF_T_SYM);
	case SHT_SYMTAB_SHNDX:
		return (ELF_T_WORD);
	case SHT_SUNW_dof:
		return (ELF_T_BYTE);
	case SHT_SUNW_move:
		return (ELF_T_MOVE);
	case SHT_SUNW_syminfo:
		return (ELF_T_SYMINFO);
	case SHT_SUNW_verdef:	/* == SHT_GNU_verdef */
		return (ELF_T_VDEF);
	case SHT_SUNW_verneed:	/* == SHT_GNU_verneed */
		return (ELF_T_VNEED);
	case SHT_SUNW_versym:	/* == SHT_GNU_versym */
		return (ELF_T_HALF);
	default:
		/*
		 * Values in the range [SHT_LOOS..SHT_HIUSER] (i.e.,
		 * OS, processor and user-defined section types) are
		 * legal, but since we do not know anything more about
		 * their semantics, we return a type of ELF_T_BYTE.
		 */
		if (sht >= SHT_LOOS && sht <= SHT_HIUSER)
			return (ELF_T_BYTE);

		/*
		 * Other values are unsupported.
		 */
		return (-1);
	}
}