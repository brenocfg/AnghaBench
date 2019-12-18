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
typedef  int /*<<< orphan*/  s_dtype ;

/* Variables and functions */
#define  DT_ARM_SYMTABSZ 252 
#define  DT_AUDIT 251 
#define  DT_AUXILIARY 250 
#define  DT_BIND_NOW 249 
#define  DT_CHECKSUM 248 
#define  DT_CONFIG 247 
#define  DT_DEBUG 246 
#define  DT_DEPAUDIT 245 
#define  DT_FEATURE 244 
#define  DT_FILTER 243 
#define  DT_FINI 242 
#define  DT_FINI_ARRAY 241 
#define  DT_FINI_ARRAYSZ 240 
#define  DT_FLAGS 239 
#define  DT_FLAGS_1 238 
#define  DT_GNU_CONFLICT 237 
#define  DT_GNU_CONFLICTSZ 236 
#define  DT_GNU_HASH 235 
#define  DT_GNU_LIBLIST 234 
#define  DT_GNU_LIBLISTSZ 233 
#define  DT_GNU_PRELINKED 232 
#define  DT_HASH 231 
 unsigned int DT_HIPROC ; 
#define  DT_INIT 230 
#define  DT_INIT_ARRAY 229 
#define  DT_INIT_ARRAYSZ 228 
#define  DT_JMPREL 227 
 unsigned int DT_LOPROC ; 
#define  DT_MAXPOSTAGS 226 
#define  DT_MIPS_AUX_DYNAMIC 225 
#define  DT_MIPS_BASE_ADDRESS 224 
#define  DT_MIPS_COMPACT_SIZE 223 
#define  DT_MIPS_CONFLICT 222 
#define  DT_MIPS_CONFLICTNO 221 
#define  DT_MIPS_CXX_FLAGS 220 
#define  DT_MIPS_DELTA_CLASS 219 
#define  DT_MIPS_DELTA_CLASSSYM 218 
#define  DT_MIPS_DELTA_CLASSSYM_NO 217 
#define  DT_MIPS_DELTA_CLASS_NO 216 
#define  DT_MIPS_DELTA_INSTANCE 215 
#define  DT_MIPS_DELTA_INSTANCE_NO 214 
#define  DT_MIPS_DELTA_RELOC 213 
#define  DT_MIPS_DELTA_RELOC_NO 212 
#define  DT_MIPS_DELTA_SYM 211 
#define  DT_MIPS_DELTA_SYM_NO 210 
#define  DT_MIPS_DYNSTR_ALIGN 209 
#define  DT_MIPS_FLAGS 208 
#define  DT_MIPS_GOTSYM 207 
#define  DT_MIPS_GP_VALUE 206 
#define  DT_MIPS_HIDDEN_GOTIDX 205 
#define  DT_MIPS_HIPAGENO 204 
#define  DT_MIPS_ICHECKSUM 203 
#define  DT_MIPS_INTERFACE 202 
#define  DT_MIPS_INTERFACE_SIZE 201 
#define  DT_MIPS_IVERSION 200 
#define  DT_MIPS_LIBLIST 199 
#define  DT_MIPS_LIBLISTNO 198 
#define  DT_MIPS_LOCALPAGE_GOTIDX 197 
#define  DT_MIPS_LOCAL_GOTIDX 196 
#define  DT_MIPS_LOCAL_GOTNO 195 
#define  DT_MIPS_OPTIONS 194 
#define  DT_MIPS_PERF_SUFFIX 193 
#define  DT_MIPS_PIXIE_INIT 192 
#define  DT_MIPS_PLTGOT 191 
#define  DT_MIPS_PROTECTED_GOTIDX 190 
#define  DT_MIPS_RLD_MAP 189 
#define  DT_MIPS_RLD_OBJ_UPDATE 188 
#define  DT_MIPS_RLD_TEXT_RESOLVE_ADDR 187 
#define  DT_MIPS_RLD_VERSION 186 
#define  DT_MIPS_RWPLT 185 
#define  DT_MIPS_SYMBOL_LIB 184 
#define  DT_MIPS_SYMTABNO 183 
#define  DT_MIPS_TIME_STAMP 182 
#define  DT_MIPS_UNREFEXTNO 181 
#define  DT_MOVEENT 180 
#define  DT_MOVESZ 179 
#define  DT_MOVETAB 178 
#define  DT_NEEDED 177 
#define  DT_NULL 176 
#define  DT_PLTGOT 175 
#define  DT_PLTPAD 174 
#define  DT_PLTPADSZ 173 
#define  DT_PLTREL 172 
#define  DT_PLTRELSZ 171 
#define  DT_POSFLAG_1 170 
#define  DT_PREINIT_ARRAY 169 
#define  DT_PREINIT_ARRAYSZ 168 
#define  DT_REL 167 
#define  DT_RELA 166 
#define  DT_RELACOUNT 165 
#define  DT_RELAENT 164 
#define  DT_RELASZ 163 
#define  DT_RELCOUNT 162 
#define  DT_RELENT 161 
#define  DT_RELSZ 160 
#define  DT_RPATH 159 
#define  DT_RUNPATH 158 
#define  DT_SONAME 157 
#define  DT_SPARC_REGISTER 156 
#define  DT_STRSZ 155 
#define  DT_STRTAB 154 
#define  DT_SUNW_ASLR 153 
#define  DT_SUNW_AUXILIARY 152 
#define  DT_SUNW_CAP 151 
#define  DT_SUNW_FILTER 150 
#define  DT_SUNW_RTLDINF 149 
#define  DT_SYMBOLIC 148 
#define  DT_SYMENT 147 
#define  DT_SYMINENT 146 
#define  DT_SYMINFO 145 
#define  DT_SYMINSZ 144 
#define  DT_SYMTAB 143 
#define  DT_TEXTREL 142 
#define  DT_TLSDESC_GOT 141 
#define  DT_TLSDESC_PLT 140 
#define  DT_USED 139 
#define  DT_VERDEF 138 
#define  DT_VERDEFNUM 137 
#define  DT_VERNEED 136 
#define  DT_VERNEEDNUM 135 
#define  DT_VERSYM 134 
#define  EM_ARM 133 
#define  EM_MIPS 132 
#define  EM_MIPS_RS3_LE 131 
#define  EM_SPARC 130 
#define  EM_SPARC32PLUS 129 
#define  EM_SPARCV9 128 
 int /*<<< orphan*/  snprintf (char*,int,char*,unsigned int) ; 

__attribute__((used)) static const char *
dt_type(unsigned int mach, unsigned int dtype)
{
	static char s_dtype[32];

	switch (dtype) {
	case DT_NULL: return "NULL";
	case DT_NEEDED: return "NEEDED";
	case DT_PLTRELSZ: return "PLTRELSZ";
	case DT_PLTGOT: return "PLTGOT";
	case DT_HASH: return "HASH";
	case DT_STRTAB: return "STRTAB";
	case DT_SYMTAB: return "SYMTAB";
	case DT_RELA: return "RELA";
	case DT_RELASZ: return "RELASZ";
	case DT_RELAENT: return "RELAENT";
	case DT_STRSZ: return "STRSZ";
	case DT_SYMENT: return "SYMENT";
	case DT_INIT: return "INIT";
	case DT_FINI: return "FINI";
	case DT_SONAME: return "SONAME";
	case DT_RPATH: return "RPATH";
	case DT_SYMBOLIC: return "SYMBOLIC";
	case DT_REL: return "REL";
	case DT_RELSZ: return "RELSZ";
	case DT_RELENT: return "RELENT";
	case DT_PLTREL: return "PLTREL";
	case DT_DEBUG: return "DEBUG";
	case DT_TEXTREL: return "TEXTREL";
	case DT_JMPREL: return "JMPREL";
	case DT_BIND_NOW: return "BIND_NOW";
	case DT_INIT_ARRAY: return "INIT_ARRAY";
	case DT_FINI_ARRAY: return "FINI_ARRAY";
	case DT_INIT_ARRAYSZ: return "INIT_ARRAYSZ";
	case DT_FINI_ARRAYSZ: return "FINI_ARRAYSZ";
	case DT_RUNPATH: return "RUNPATH";
	case DT_FLAGS: return "FLAGS";
	case DT_PREINIT_ARRAY: return "PREINIT_ARRAY";
	case DT_PREINIT_ARRAYSZ: return "PREINIT_ARRAYSZ";
	case DT_MAXPOSTAGS: return "MAXPOSTAGS";
	case DT_SUNW_AUXILIARY: return "SUNW_AUXILIARY";
	case DT_SUNW_RTLDINF: return "SUNW_RTLDINF";
	case DT_SUNW_FILTER: return "SUNW_FILTER";
	case DT_SUNW_CAP: return "SUNW_CAP";
	case DT_SUNW_ASLR: return "SUNW_ASLR";
	case DT_CHECKSUM: return "CHECKSUM";
	case DT_PLTPADSZ: return "PLTPADSZ";
	case DT_MOVEENT: return "MOVEENT";
	case DT_MOVESZ: return "MOVESZ";
	case DT_FEATURE: return "FEATURE";
	case DT_POSFLAG_1: return "POSFLAG_1";
	case DT_SYMINSZ: return "SYMINSZ";
	case DT_SYMINENT: return "SYMINENT";
	case DT_GNU_HASH: return "GNU_HASH";
	case DT_TLSDESC_PLT: return "DT_TLSDESC_PLT";
	case DT_TLSDESC_GOT: return "DT_TLSDESC_GOT";
	case DT_GNU_CONFLICT: return "GNU_CONFLICT";
	case DT_GNU_LIBLIST: return "GNU_LIBLIST";
	case DT_CONFIG: return "CONFIG";
	case DT_DEPAUDIT: return "DEPAUDIT";
	case DT_AUDIT: return "AUDIT";
	case DT_PLTPAD: return "PLTPAD";
	case DT_MOVETAB: return "MOVETAB";
	case DT_SYMINFO: return "SYMINFO";
	case DT_VERSYM: return "VERSYM";
	case DT_RELACOUNT: return "RELACOUNT";
	case DT_RELCOUNT: return "RELCOUNT";
	case DT_FLAGS_1: return "FLAGS_1";
	case DT_VERDEF: return "VERDEF";
	case DT_VERDEFNUM: return "VERDEFNUM";
	case DT_VERNEED: return "VERNEED";
	case DT_VERNEEDNUM: return "VERNEEDNUM";
	case DT_AUXILIARY: return "AUXILIARY";
	case DT_USED: return "USED";
	case DT_FILTER: return "FILTER";
	case DT_GNU_PRELINKED: return "GNU_PRELINKED";
	case DT_GNU_CONFLICTSZ: return "GNU_CONFLICTSZ";
	case DT_GNU_LIBLISTSZ: return "GNU_LIBLISTSZ";
	}

	if (dtype >= DT_LOPROC && dtype <= DT_HIPROC) {
		switch (mach) {
		case EM_ARM:
			switch (dtype) {
			case DT_ARM_SYMTABSZ:
				return "ARM_SYMTABSZ";
			default:
				break;
			}
			break;
		case EM_MIPS:
		case EM_MIPS_RS3_LE:
			switch (dtype) {
			case DT_MIPS_RLD_VERSION:
				return "MIPS_RLD_VERSION";
			case DT_MIPS_TIME_STAMP:
				return "MIPS_TIME_STAMP";
			case DT_MIPS_ICHECKSUM:
				return "MIPS_ICHECKSUM";
			case DT_MIPS_IVERSION:
				return "MIPS_IVERSION";
			case DT_MIPS_FLAGS:
				return "MIPS_FLAGS";
			case DT_MIPS_BASE_ADDRESS:
				return "MIPS_BASE_ADDRESS";
			case DT_MIPS_CONFLICT:
				return "MIPS_CONFLICT";
			case DT_MIPS_LIBLIST:
				return "MIPS_LIBLIST";
			case DT_MIPS_LOCAL_GOTNO:
				return "MIPS_LOCAL_GOTNO";
			case DT_MIPS_CONFLICTNO:
				return "MIPS_CONFLICTNO";
			case DT_MIPS_LIBLISTNO:
				return "MIPS_LIBLISTNO";
			case DT_MIPS_SYMTABNO:
				return "MIPS_SYMTABNO";
			case DT_MIPS_UNREFEXTNO:
				return "MIPS_UNREFEXTNO";
			case DT_MIPS_GOTSYM:
				return "MIPS_GOTSYM";
			case DT_MIPS_HIPAGENO:
				return "MIPS_HIPAGENO";
			case DT_MIPS_RLD_MAP:
				return "MIPS_RLD_MAP";
			case DT_MIPS_DELTA_CLASS:
				return "MIPS_DELTA_CLASS";
			case DT_MIPS_DELTA_CLASS_NO:
				return "MIPS_DELTA_CLASS_NO";
			case DT_MIPS_DELTA_INSTANCE:
				return "MIPS_DELTA_INSTANCE";
			case DT_MIPS_DELTA_INSTANCE_NO:
				return "MIPS_DELTA_INSTANCE_NO";
			case DT_MIPS_DELTA_RELOC:
				return "MIPS_DELTA_RELOC";
			case DT_MIPS_DELTA_RELOC_NO:
				return "MIPS_DELTA_RELOC_NO";
			case DT_MIPS_DELTA_SYM:
				return "MIPS_DELTA_SYM";
			case DT_MIPS_DELTA_SYM_NO:
				return "MIPS_DELTA_SYM_NO";
			case DT_MIPS_DELTA_CLASSSYM:
				return "MIPS_DELTA_CLASSSYM";
			case DT_MIPS_DELTA_CLASSSYM_NO:
				return "MIPS_DELTA_CLASSSYM_NO";
			case DT_MIPS_CXX_FLAGS:
				return "MIPS_CXX_FLAGS";
			case DT_MIPS_PIXIE_INIT:
				return "MIPS_PIXIE_INIT";
			case DT_MIPS_SYMBOL_LIB:
				return "MIPS_SYMBOL_LIB";
			case DT_MIPS_LOCALPAGE_GOTIDX:
				return "MIPS_LOCALPAGE_GOTIDX";
			case DT_MIPS_LOCAL_GOTIDX:
				return "MIPS_LOCAL_GOTIDX";
			case DT_MIPS_HIDDEN_GOTIDX:
				return "MIPS_HIDDEN_GOTIDX";
			case DT_MIPS_PROTECTED_GOTIDX:
				return "MIPS_PROTECTED_GOTIDX";
			case DT_MIPS_OPTIONS:
				return "MIPS_OPTIONS";
			case DT_MIPS_INTERFACE:
				return "MIPS_INTERFACE";
			case DT_MIPS_DYNSTR_ALIGN:
				return "MIPS_DYNSTR_ALIGN";
			case DT_MIPS_INTERFACE_SIZE:
				return "MIPS_INTERFACE_SIZE";
			case DT_MIPS_RLD_TEXT_RESOLVE_ADDR:
				return "MIPS_RLD_TEXT_RESOLVE_ADDR";
			case DT_MIPS_PERF_SUFFIX:
				return "MIPS_PERF_SUFFIX";
			case DT_MIPS_COMPACT_SIZE:
				return "MIPS_COMPACT_SIZE";
			case DT_MIPS_GP_VALUE:
				return "MIPS_GP_VALUE";
			case DT_MIPS_AUX_DYNAMIC:
				return "MIPS_AUX_DYNAMIC";
			case DT_MIPS_PLTGOT:
				return "MIPS_PLTGOT";
			case DT_MIPS_RLD_OBJ_UPDATE:
				return "MIPS_RLD_OBJ_UPDATE";
			case DT_MIPS_RWPLT:
				return "MIPS_RWPLT";
			default:
				break;
			}
			break;
		case EM_SPARC:
		case EM_SPARC32PLUS:
		case EM_SPARCV9:
			switch (dtype) {
			case DT_SPARC_REGISTER:
				return "DT_SPARC_REGISTER";
			default:
				break;
			}
			break;
		default:
			break;
		}
	}

	snprintf(s_dtype, sizeof(s_dtype), "<unknown: %#x>", dtype);
	return (s_dtype);
}