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
#define  SHT_MIPS_AUXSYM 166 
#define  SHT_MIPS_CONFLICT 165 
#define  SHT_MIPS_CONTENT 164 
#define  SHT_MIPS_DEBUG 163 
#define  SHT_MIPS_DELTACLASS 162 
#define  SHT_MIPS_DELTADECL 161 
#define  SHT_MIPS_DELTAINST 160 
#define  SHT_MIPS_DELTASYM 159 
#define  SHT_MIPS_DENSE 158 
#define  SHT_MIPS_DWARF 157 
#define  SHT_MIPS_EH_REGION 156 
#define  SHT_MIPS_EVENTS 155 
#define  SHT_MIPS_EXTSYM 154 
#define  SHT_MIPS_FDESC 153 
#define  SHT_MIPS_GPTAB 152 
#define  SHT_MIPS_IFACE 151 
#define  SHT_MIPS_LIBLIST 150 
#define  SHT_MIPS_LINE 149 
#define  SHT_MIPS_LOCSTR 148 
#define  SHT_MIPS_LOCSYM 147 
#define  SHT_MIPS_MSYM 146 
#define  SHT_MIPS_OPTIONS 145 
#define  SHT_MIPS_OPTSYM 144 
#define  SHT_MIPS_PACKAGE 143 
#define  SHT_MIPS_PACKSYM 142 
#define  SHT_MIPS_PDESC 141 
#define  SHT_MIPS_PDR_EXCEPTION 140 
#define  SHT_MIPS_PIXIE 139 
#define  SHT_MIPS_REGINFO 138 
#define  SHT_MIPS_RELD 137 
#define  SHT_MIPS_RFDESC 136 
#define  SHT_MIPS_SHDR 135 
#define  SHT_MIPS_SYMBOL_LIB 134 
#define  SHT_MIPS_TRANSLATE 133 
#define  SHT_MIPS_UCODE 132 
#define  SHT_MIPS_WHIRL 131 
#define  SHT_MIPS_XLATE 130 
#define  SHT_MIPS_XLATE_DEBUG 129 
#define  SHT_MIPS_XLATE_OLD 128 

__attribute__((used)) static const char *
get_mips_section_type_name (unsigned int sh_type)
{
  switch (sh_type)
    {
    case SHT_MIPS_LIBLIST:	 return "MIPS_LIBLIST";
    case SHT_MIPS_MSYM:		 return "MIPS_MSYM";
    case SHT_MIPS_CONFLICT:	 return "MIPS_CONFLICT";
    case SHT_MIPS_GPTAB:	 return "MIPS_GPTAB";
    case SHT_MIPS_UCODE:	 return "MIPS_UCODE";
    case SHT_MIPS_DEBUG:	 return "MIPS_DEBUG";
    case SHT_MIPS_REGINFO:	 return "MIPS_REGINFO";
    case SHT_MIPS_PACKAGE:	 return "MIPS_PACKAGE";
    case SHT_MIPS_PACKSYM:	 return "MIPS_PACKSYM";
    case SHT_MIPS_RELD:		 return "MIPS_RELD";
    case SHT_MIPS_IFACE:	 return "MIPS_IFACE";
    case SHT_MIPS_CONTENT:	 return "MIPS_CONTENT";
    case SHT_MIPS_OPTIONS:	 return "MIPS_OPTIONS";
    case SHT_MIPS_SHDR:		 return "MIPS_SHDR";
    case SHT_MIPS_FDESC:	 return "MIPS_FDESC";
    case SHT_MIPS_EXTSYM:	 return "MIPS_EXTSYM";
    case SHT_MIPS_DENSE:	 return "MIPS_DENSE";
    case SHT_MIPS_PDESC:	 return "MIPS_PDESC";
    case SHT_MIPS_LOCSYM:	 return "MIPS_LOCSYM";
    case SHT_MIPS_AUXSYM:	 return "MIPS_AUXSYM";
    case SHT_MIPS_OPTSYM:	 return "MIPS_OPTSYM";
    case SHT_MIPS_LOCSTR:	 return "MIPS_LOCSTR";
    case SHT_MIPS_LINE:		 return "MIPS_LINE";
    case SHT_MIPS_RFDESC:	 return "MIPS_RFDESC";
    case SHT_MIPS_DELTASYM:	 return "MIPS_DELTASYM";
    case SHT_MIPS_DELTAINST:	 return "MIPS_DELTAINST";
    case SHT_MIPS_DELTACLASS:	 return "MIPS_DELTACLASS";
    case SHT_MIPS_DWARF:	 return "MIPS_DWARF";
    case SHT_MIPS_DELTADECL:	 return "MIPS_DELTADECL";
    case SHT_MIPS_SYMBOL_LIB:	 return "MIPS_SYMBOL_LIB";
    case SHT_MIPS_EVENTS:	 return "MIPS_EVENTS";
    case SHT_MIPS_TRANSLATE:	 return "MIPS_TRANSLATE";
    case SHT_MIPS_PIXIE:	 return "MIPS_PIXIE";
    case SHT_MIPS_XLATE:	 return "MIPS_XLATE";
    case SHT_MIPS_XLATE_DEBUG:	 return "MIPS_XLATE_DEBUG";
    case SHT_MIPS_WHIRL:	 return "MIPS_WHIRL";
    case SHT_MIPS_EH_REGION:	 return "MIPS_EH_REGION";
    case SHT_MIPS_XLATE_OLD:	 return "MIPS_XLATE_OLD";
    case SHT_MIPS_PDR_EXCEPTION: return "MIPS_PDR_EXCEPTION";
    default:
      break;
    }
  return NULL;
}