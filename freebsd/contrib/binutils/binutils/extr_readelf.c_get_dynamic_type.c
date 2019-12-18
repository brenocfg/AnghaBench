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
struct TYPE_2__ {int e_machine; } ;

/* Variables and functions */
#define  DT_ADDRRNGLO 203 
#define  DT_AUDIT 202 
#define  DT_AUXILIARY 201 
#define  DT_BIND_NOW 200 
#define  DT_CHECKSUM 199 
#define  DT_CONFIG 198 
#define  DT_DEBUG 197 
#define  DT_DEPAUDIT 196 
#define  DT_FEATURE 195 
#define  DT_FILTER 194 
#define  DT_FINI 193 
#define  DT_FINI_ARRAY 192 
#define  DT_FINI_ARRAYSZ 191 
#define  DT_FLAGS 190 
#define  DT_FLAGS_1 189 
#define  DT_GNU_CONFLICT 188 
#define  DT_GNU_CONFLICTSZ 187 
#define  DT_GNU_HASH 186 
#define  DT_GNU_LIBLIST 185 
#define  DT_GNU_LIBLISTSZ 184 
#define  DT_GNU_PRELINKED 183 
#define  DT_HASH 182 
 unsigned long DT_HIOS ; 
 unsigned long DT_HIPROC ; 
#define  DT_INIT 181 
#define  DT_INIT_ARRAY 180 
#define  DT_INIT_ARRAYSZ 179 
#define  DT_JMPREL 178 
 unsigned long DT_LOOS ; 
 unsigned long DT_LOPROC ; 
#define  DT_MOVEENT 177 
#define  DT_MOVESZ 176 
#define  DT_MOVETAB 175 
#define  DT_NEEDED 174 
#define  DT_NULL 173 
#define  DT_PLTGOT 172 
#define  DT_PLTPAD 171 
#define  DT_PLTPADSZ 170 
#define  DT_PLTREL 169 
#define  DT_PLTRELSZ 168 
#define  DT_POSFLAG_1 167 
#define  DT_PREINIT_ARRAY 166 
#define  DT_PREINIT_ARRAYSZ 165 
#define  DT_REL 164 
#define  DT_RELA 163 
#define  DT_RELACOUNT 162 
#define  DT_RELAENT 161 
#define  DT_RELASZ 160 
#define  DT_RELCOUNT 159 
#define  DT_RELENT 158 
#define  DT_RELSZ 157 
#define  DT_RPATH 156 
#define  DT_RUNPATH 155 
#define  DT_SONAME 154 
#define  DT_STRSZ 153 
#define  DT_STRTAB 152 
#define  DT_SYMBOLIC 151 
#define  DT_SYMENT 150 
#define  DT_SYMINENT 149 
#define  DT_SYMINFO 148 
#define  DT_SYMINSZ 147 
#define  DT_SYMTAB 146 
#define  DT_TEXTREL 145 
#define  DT_TLSDESC_GOT 144 
#define  DT_TLSDESC_PLT 143 
#define  DT_USED 142 
#define  DT_VERDEF 141 
#define  DT_VERDEFNUM 140 
#define  DT_VERNEED 139 
#define  DT_VERNEEDNUM 138 
#define  DT_VERSYM 137 
#define  EM_ALPHA 136 
#define  EM_IA_64 135 
#define  EM_MIPS 134 
#define  EM_MIPS_RS3_LE 133 
#define  EM_PARISC 132 
#define  EM_PPC 131 
#define  EM_PPC64 130 
#define  EM_SCORE 129 
#define  EM_SPARCV9 128 
 unsigned long OLD_DT_HIOS ; 
 unsigned long OLD_DT_LOOS ; 
 char* _ (char*) ; 
 TYPE_1__ elf_header ; 
 char* get_alpha_dynamic_type (unsigned long) ; 
 char* get_ia64_dynamic_type (unsigned long) ; 
 char* get_mips_dynamic_type (unsigned long) ; 
 char* get_parisc_dynamic_type (unsigned long) ; 
 char* get_ppc64_dynamic_type (unsigned long) ; 
 char* get_ppc_dynamic_type (unsigned long) ; 
 char* get_score_dynamic_type (unsigned long) ; 
 char* get_sparc64_dynamic_type (unsigned long) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,unsigned long) ; 

__attribute__((used)) static const char *
get_dynamic_type (unsigned long type)
{
  static char buff[64];

  switch (type)
    {
    case DT_NULL:	return "NULL";
    case DT_NEEDED:	return "NEEDED";
    case DT_PLTRELSZ:	return "PLTRELSZ";
    case DT_PLTGOT:	return "PLTGOT";
    case DT_HASH:	return "HASH";
    case DT_STRTAB:	return "STRTAB";
    case DT_SYMTAB:	return "SYMTAB";
    case DT_RELA:	return "RELA";
    case DT_RELASZ:	return "RELASZ";
    case DT_RELAENT:	return "RELAENT";
    case DT_STRSZ:	return "STRSZ";
    case DT_SYMENT:	return "SYMENT";
    case DT_INIT:	return "INIT";
    case DT_FINI:	return "FINI";
    case DT_SONAME:	return "SONAME";
    case DT_RPATH:	return "RPATH";
    case DT_SYMBOLIC:	return "SYMBOLIC";
    case DT_REL:	return "REL";
    case DT_RELSZ:	return "RELSZ";
    case DT_RELENT:	return "RELENT";
    case DT_PLTREL:	return "PLTREL";
    case DT_DEBUG:	return "DEBUG";
    case DT_TEXTREL:	return "TEXTREL";
    case DT_JMPREL:	return "JMPREL";
    case DT_BIND_NOW:   return "BIND_NOW";
    case DT_INIT_ARRAY: return "INIT_ARRAY";
    case DT_FINI_ARRAY: return "FINI_ARRAY";
    case DT_INIT_ARRAYSZ: return "INIT_ARRAYSZ";
    case DT_FINI_ARRAYSZ: return "FINI_ARRAYSZ";
    case DT_RUNPATH:    return "RUNPATH";
    case DT_FLAGS:      return "FLAGS";

    case DT_PREINIT_ARRAY: return "PREINIT_ARRAY";
    case DT_PREINIT_ARRAYSZ: return "PREINIT_ARRAYSZ";

    case DT_CHECKSUM:	return "CHECKSUM";
    case DT_PLTPADSZ:	return "PLTPADSZ";
    case DT_MOVEENT:	return "MOVEENT";
    case DT_MOVESZ:	return "MOVESZ";
    case DT_FEATURE:	return "FEATURE";
    case DT_POSFLAG_1:	return "POSFLAG_1";
    case DT_SYMINSZ:	return "SYMINSZ";
    case DT_SYMINENT:	return "SYMINENT"; /* aka VALRNGHI */

    case DT_ADDRRNGLO:  return "ADDRRNGLO";
    case DT_CONFIG:	return "CONFIG";
    case DT_DEPAUDIT:	return "DEPAUDIT";
    case DT_AUDIT:	return "AUDIT";
    case DT_PLTPAD:	return "PLTPAD";
    case DT_MOVETAB:	return "MOVETAB";
    case DT_SYMINFO:	return "SYMINFO"; /* aka ADDRRNGHI */

    case DT_VERSYM:	return "VERSYM";

    case DT_TLSDESC_GOT: return "TLSDESC_GOT";
    case DT_TLSDESC_PLT: return "TLSDESC_PLT";
    case DT_RELACOUNT:	return "RELACOUNT";
    case DT_RELCOUNT:	return "RELCOUNT";
    case DT_FLAGS_1:	return "FLAGS_1";
    case DT_VERDEF:	return "VERDEF";
    case DT_VERDEFNUM:	return "VERDEFNUM";
    case DT_VERNEED:	return "VERNEED";
    case DT_VERNEEDNUM:	return "VERNEEDNUM";

    case DT_AUXILIARY:	return "AUXILIARY";
    case DT_USED:	return "USED";
    case DT_FILTER:	return "FILTER";

    case DT_GNU_PRELINKED: return "GNU_PRELINKED";
    case DT_GNU_CONFLICT: return "GNU_CONFLICT";
    case DT_GNU_CONFLICTSZ: return "GNU_CONFLICTSZ";
    case DT_GNU_LIBLIST: return "GNU_LIBLIST";
    case DT_GNU_LIBLISTSZ: return "GNU_LIBLISTSZ";
    case DT_GNU_HASH:	return "GNU_HASH";

    default:
      if ((type >= DT_LOPROC) && (type <= DT_HIPROC))
	{
	  const char *result;

	  switch (elf_header.e_machine)
	    {
	    case EM_MIPS:
	    case EM_MIPS_RS3_LE:
	      result = get_mips_dynamic_type (type);
	      break;
	    case EM_SPARCV9:
	      result = get_sparc64_dynamic_type (type);
	      break;
	    case EM_PPC:
	      result = get_ppc_dynamic_type (type);
	      break;
	    case EM_PPC64:
	      result = get_ppc64_dynamic_type (type);
	      break;
	    case EM_IA_64:
	      result = get_ia64_dynamic_type (type);
	      break;
	    case EM_ALPHA:
	      result = get_alpha_dynamic_type (type);
	      break;
	    case EM_SCORE:
	      result = get_score_dynamic_type (type);
	      break;
	    default:
	      result = NULL;
	      break;
	    }

	  if (result != NULL)
	    return result;

	  snprintf (buff, sizeof (buff), _("Processor Specific: %lx"), type);
	}
      else if (((type >= DT_LOOS) && (type <= DT_HIOS))
	       || (elf_header.e_machine == EM_PARISC
		   && (type >= OLD_DT_LOOS) && (type <= OLD_DT_HIOS)))
	{
	  const char *result;

	  switch (elf_header.e_machine)
	    {
	    case EM_PARISC:
	      result = get_parisc_dynamic_type (type);
	      break;
	    default:
	      result = NULL;
	      break;
	    }

	  if (result != NULL)
	    return result;

	  snprintf (buff, sizeof (buff), _("Operating System specific: %lx"),
		    type);
	}
      else
	snprintf (buff, sizeof (buff), _("<unknown>: %lx"), type);

      return buff;
    }
}