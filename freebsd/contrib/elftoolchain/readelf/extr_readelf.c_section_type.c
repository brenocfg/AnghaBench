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
typedef  int /*<<< orphan*/  s_stype ;

/* Variables and functions */
#define  EM_ARM 195 
#define  EM_MIPS 194 
#define  EM_MIPS_RS3_LE 193 
#define  EM_X86_64 192 
#define  SHT_ARM_ATTRIBUTES 191 
#define  SHT_ARM_DEBUGOVERLAY 190 
#define  SHT_ARM_EXIDX 189 
#define  SHT_ARM_OVERLAYSECTION 188 
#define  SHT_ARM_PREEMPTMAP 187 
#define  SHT_DYNAMIC 186 
#define  SHT_DYNSYM 185 
#define  SHT_FINI_ARRAY 184 
#define  SHT_GNU_HASH 183 
#define  SHT_GROUP 182 
#define  SHT_HASH 181 
 unsigned int SHT_HIOS ; 
 unsigned int SHT_HIPROC ; 
#define  SHT_INIT_ARRAY 180 
 unsigned int SHT_LOOS ; 
 unsigned int SHT_LOPROC ; 
 unsigned int SHT_LOUSER ; 
#define  SHT_MIPS_ABIFLAGS 179 
#define  SHT_MIPS_CONFLICT 178 
#define  SHT_MIPS_CONTENT 177 
#define  SHT_MIPS_DEBUG 176 
#define  SHT_MIPS_DELTACLASS 175 
#define  SHT_MIPS_DELTADECL 174 
#define  SHT_MIPS_DELTAINST 173 
#define  SHT_MIPS_DELTASYM 172 
#define  SHT_MIPS_DWARF 171 
#define  SHT_MIPS_EH_REGION 170 
#define  SHT_MIPS_EVENTS 169 
#define  SHT_MIPS_GPTAB 168 
#define  SHT_MIPS_IFACE 167 
#define  SHT_MIPS_LIBLIST 166 
#define  SHT_MIPS_MSYM 165 
#define  SHT_MIPS_OPTIONS 164 
#define  SHT_MIPS_PACKAGE 163 
#define  SHT_MIPS_PACKSYM 162 
#define  SHT_MIPS_PDR_EXCEPTION 161 
#define  SHT_MIPS_PIXIE 160 
#define  SHT_MIPS_REGINFO 159 
#define  SHT_MIPS_RELD 158 
#define  SHT_MIPS_SYMBOL_LIB 157 
#define  SHT_MIPS_TRANSLATE 156 
#define  SHT_MIPS_UCODE 155 
#define  SHT_MIPS_WHIRL 154 
#define  SHT_MIPS_XLATE 153 
#define  SHT_MIPS_XLATE_DEBUG 152 
#define  SHT_MIPS_XLATE_OLD 151 
#define  SHT_NOBITS 150 
#define  SHT_NOTE 149 
#define  SHT_NULL 148 
#define  SHT_PREINIT_ARRAY 147 
#define  SHT_PROGBITS 146 
#define  SHT_REL 145 
#define  SHT_RELA 144 
#define  SHT_SHLIB 143 
#define  SHT_STRTAB 142 
#define  SHT_SUNW_ANNOTATE 141 
#define  SHT_SUNW_COMDAT 140 
#define  SHT_SUNW_DEBUG 139 
#define  SHT_SUNW_DEBUGSTR 138 
#define  SHT_SUNW_cap 137 
#define  SHT_SUNW_dof 136 
#define  SHT_SUNW_move 135 
#define  SHT_SUNW_syminfo 134 
#define  SHT_SUNW_verdef 133 
#define  SHT_SUNW_verneed 132 
#define  SHT_SUNW_versym 131 
#define  SHT_SYMTAB 130 
#define  SHT_SYMTAB_SHNDX 129 
#define  SHT_X86_64_UNWIND 128 
 int /*<<< orphan*/  snprintf (char*,int,char*,unsigned int) ; 

__attribute__((used)) static const char *
section_type(unsigned int mach, unsigned int stype)
{
	static char s_stype[32];

	if (stype >= SHT_LOPROC && stype <= SHT_HIPROC) {
		switch (mach) {
		case EM_ARM:
			switch (stype) {
			case SHT_ARM_EXIDX: return "ARM_EXIDX";
			case SHT_ARM_PREEMPTMAP: return "ARM_PREEMPTMAP";
			case SHT_ARM_ATTRIBUTES: return "ARM_ATTRIBUTES";
			case SHT_ARM_DEBUGOVERLAY: return "ARM_DEBUGOVERLAY";
			case SHT_ARM_OVERLAYSECTION: return "ARM_OVERLAYSECTION";
			}
			break;
		case EM_X86_64:
			switch (stype) {
			case SHT_X86_64_UNWIND: return "X86_64_UNWIND";
			default:
				break;
			}
			break;
		case EM_MIPS:
		case EM_MIPS_RS3_LE:
			switch (stype) {
			case SHT_MIPS_LIBLIST: return "MIPS_LIBLIST";
			case SHT_MIPS_MSYM: return "MIPS_MSYM";
			case SHT_MIPS_CONFLICT: return "MIPS_CONFLICT";
			case SHT_MIPS_GPTAB: return "MIPS_GPTAB";
			case SHT_MIPS_UCODE: return "MIPS_UCODE";
			case SHT_MIPS_DEBUG: return "MIPS_DEBUG";
			case SHT_MIPS_REGINFO: return "MIPS_REGINFO";
			case SHT_MIPS_PACKAGE: return "MIPS_PACKAGE";
			case SHT_MIPS_PACKSYM: return "MIPS_PACKSYM";
			case SHT_MIPS_RELD: return "MIPS_RELD";
			case SHT_MIPS_IFACE: return "MIPS_IFACE";
			case SHT_MIPS_CONTENT: return "MIPS_CONTENT";
			case SHT_MIPS_OPTIONS: return "MIPS_OPTIONS";
			case SHT_MIPS_DELTASYM: return "MIPS_DELTASYM";
			case SHT_MIPS_DELTAINST: return "MIPS_DELTAINST";
			case SHT_MIPS_DELTACLASS: return "MIPS_DELTACLASS";
			case SHT_MIPS_DWARF: return "MIPS_DWARF";
			case SHT_MIPS_DELTADECL: return "MIPS_DELTADECL";
			case SHT_MIPS_SYMBOL_LIB: return "MIPS_SYMBOL_LIB";
			case SHT_MIPS_EVENTS: return "MIPS_EVENTS";
			case SHT_MIPS_TRANSLATE: return "MIPS_TRANSLATE";
			case SHT_MIPS_PIXIE: return "MIPS_PIXIE";
			case SHT_MIPS_XLATE: return "MIPS_XLATE";
			case SHT_MIPS_XLATE_DEBUG: return "MIPS_XLATE_DEBUG";
			case SHT_MIPS_WHIRL: return "MIPS_WHIRL";
			case SHT_MIPS_EH_REGION: return "MIPS_EH_REGION";
			case SHT_MIPS_XLATE_OLD: return "MIPS_XLATE_OLD";
			case SHT_MIPS_PDR_EXCEPTION: return "MIPS_PDR_EXCEPTION";
			case SHT_MIPS_ABIFLAGS: return "MIPS_ABIFLAGS";
			default:
				break;
			}
			break;
		default:
			break;
		}

		snprintf(s_stype, sizeof(s_stype), "LOPROC+%#x",
		    stype - SHT_LOPROC);
		return (s_stype);
	}

	switch (stype) {
	case SHT_NULL: return "NULL";
	case SHT_PROGBITS: return "PROGBITS";
	case SHT_SYMTAB: return "SYMTAB";
	case SHT_STRTAB: return "STRTAB";
	case SHT_RELA: return "RELA";
	case SHT_HASH: return "HASH";
	case SHT_DYNAMIC: return "DYNAMIC";
	case SHT_NOTE: return "NOTE";
	case SHT_NOBITS: return "NOBITS";
	case SHT_REL: return "REL";
	case SHT_SHLIB: return "SHLIB";
	case SHT_DYNSYM: return "DYNSYM";
	case SHT_INIT_ARRAY: return "INIT_ARRAY";
	case SHT_FINI_ARRAY: return "FINI_ARRAY";
	case SHT_PREINIT_ARRAY: return "PREINIT_ARRAY";
	case SHT_GROUP: return "GROUP";
	case SHT_SYMTAB_SHNDX: return "SYMTAB_SHNDX";
	case SHT_SUNW_dof: return "SUNW_dof";
	case SHT_SUNW_cap: return "SUNW_cap";
	case SHT_GNU_HASH: return "GNU_HASH";
	case SHT_SUNW_ANNOTATE: return "SUNW_ANNOTATE";
	case SHT_SUNW_DEBUGSTR: return "SUNW_DEBUGSTR";
	case SHT_SUNW_DEBUG: return "SUNW_DEBUG";
	case SHT_SUNW_move: return "SUNW_move";
	case SHT_SUNW_COMDAT: return "SUNW_COMDAT";
	case SHT_SUNW_syminfo: return "SUNW_syminfo";
	case SHT_SUNW_verdef: return "SUNW_verdef";
	case SHT_SUNW_verneed: return "SUNW_verneed";
	case SHT_SUNW_versym: return "SUNW_versym";
	default:
		if (stype >= SHT_LOOS && stype <= SHT_HIOS)
			snprintf(s_stype, sizeof(s_stype), "LOOS+%#x",
			    stype - SHT_LOOS);
		else if (stype >= SHT_LOUSER)
			snprintf(s_stype, sizeof(s_stype), "LOUSER+%#x",
			    stype - SHT_LOUSER);
		else
			snprintf(s_stype, sizeof(s_stype), "<unknown: %#x>",
			    stype);
		return (s_stype);
	}
}