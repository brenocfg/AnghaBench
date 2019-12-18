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
#define  DT_MIPS_AUX_DYNAMIC 170 
#define  DT_MIPS_BASE_ADDRESS 169 
#define  DT_MIPS_COMPACT_SIZE 168 
#define  DT_MIPS_CONFLICT 167 
#define  DT_MIPS_CONFLICTNO 166 
#define  DT_MIPS_CXX_FLAGS 165 
#define  DT_MIPS_DELTA_CLASS 164 
#define  DT_MIPS_DELTA_CLASSSYM 163 
#define  DT_MIPS_DELTA_CLASSSYM_NO 162 
#define  DT_MIPS_DELTA_CLASS_NO 161 
#define  DT_MIPS_DELTA_INSTANCE 160 
#define  DT_MIPS_DELTA_INSTANCE_NO 159 
#define  DT_MIPS_DELTA_RELOC 158 
#define  DT_MIPS_DELTA_RELOC_NO 157 
#define  DT_MIPS_DELTA_SYM 156 
#define  DT_MIPS_DELTA_SYM_NO 155 
#define  DT_MIPS_DYNSTR_ALIGN 154 
#define  DT_MIPS_FLAGS 153 
#define  DT_MIPS_GOTSYM 152 
#define  DT_MIPS_GP_VALUE 151 
#define  DT_MIPS_HIDDEN_GOTIDX 150 
#define  DT_MIPS_HIPAGENO 149 
#define  DT_MIPS_ICHECKSUM 148 
#define  DT_MIPS_INTERFACE 147 
#define  DT_MIPS_INTERFACE_SIZE 146 
#define  DT_MIPS_IVERSION 145 
#define  DT_MIPS_LIBLIST 144 
#define  DT_MIPS_LIBLISTNO 143 
#define  DT_MIPS_LOCALPAGE_GOTIDX 142 
#define  DT_MIPS_LOCAL_GOTIDX 141 
#define  DT_MIPS_LOCAL_GOTNO 140 
#define  DT_MIPS_MSYM 139 
#define  DT_MIPS_OPTIONS 138 
#define  DT_MIPS_PERF_SUFFIX 137 
#define  DT_MIPS_PIXIE_INIT 136 
#define  DT_MIPS_PROTECTED_GOTIDX 135 
#define  DT_MIPS_RLD_MAP 134 
#define  DT_MIPS_RLD_TEXT_RESOLVE_ADDR 133 
#define  DT_MIPS_RLD_VERSION 132 
#define  DT_MIPS_SYMBOL_LIB 131 
#define  DT_MIPS_SYMTABNO 130 
#define  DT_MIPS_TIME_STAMP 129 
#define  DT_MIPS_UNREFEXTNO 128 

__attribute__((used)) static const char *
get_mips_dynamic_type (unsigned long type)
{
  switch (type)
    {
    case DT_MIPS_RLD_VERSION: return "MIPS_RLD_VERSION";
    case DT_MIPS_TIME_STAMP: return "MIPS_TIME_STAMP";
    case DT_MIPS_ICHECKSUM: return "MIPS_ICHECKSUM";
    case DT_MIPS_IVERSION: return "MIPS_IVERSION";
    case DT_MIPS_FLAGS: return "MIPS_FLAGS";
    case DT_MIPS_BASE_ADDRESS: return "MIPS_BASE_ADDRESS";
    case DT_MIPS_MSYM: return "MIPS_MSYM";
    case DT_MIPS_CONFLICT: return "MIPS_CONFLICT";
    case DT_MIPS_LIBLIST: return "MIPS_LIBLIST";
    case DT_MIPS_LOCAL_GOTNO: return "MIPS_LOCAL_GOTNO";
    case DT_MIPS_CONFLICTNO: return "MIPS_CONFLICTNO";
    case DT_MIPS_LIBLISTNO: return "MIPS_LIBLISTNO";
    case DT_MIPS_SYMTABNO: return "MIPS_SYMTABNO";
    case DT_MIPS_UNREFEXTNO: return "MIPS_UNREFEXTNO";
    case DT_MIPS_GOTSYM: return "MIPS_GOTSYM";
    case DT_MIPS_HIPAGENO: return "MIPS_HIPAGENO";
    case DT_MIPS_RLD_MAP: return "MIPS_RLD_MAP";
    case DT_MIPS_DELTA_CLASS: return "MIPS_DELTA_CLASS";
    case DT_MIPS_DELTA_CLASS_NO: return "MIPS_DELTA_CLASS_NO";
    case DT_MIPS_DELTA_INSTANCE: return "MIPS_DELTA_INSTANCE";
    case DT_MIPS_DELTA_INSTANCE_NO: return "MIPS_DELTA_INSTANCE_NO";
    case DT_MIPS_DELTA_RELOC: return "MIPS_DELTA_RELOC";
    case DT_MIPS_DELTA_RELOC_NO: return "MIPS_DELTA_RELOC_NO";
    case DT_MIPS_DELTA_SYM: return "MIPS_DELTA_SYM";
    case DT_MIPS_DELTA_SYM_NO: return "MIPS_DELTA_SYM_NO";
    case DT_MIPS_DELTA_CLASSSYM: return "MIPS_DELTA_CLASSSYM";
    case DT_MIPS_DELTA_CLASSSYM_NO: return "MIPS_DELTA_CLASSSYM_NO";
    case DT_MIPS_CXX_FLAGS: return "MIPS_CXX_FLAGS";
    case DT_MIPS_PIXIE_INIT: return "MIPS_PIXIE_INIT";
    case DT_MIPS_SYMBOL_LIB: return "MIPS_SYMBOL_LIB";
    case DT_MIPS_LOCALPAGE_GOTIDX: return "MIPS_LOCALPAGE_GOTIDX";
    case DT_MIPS_LOCAL_GOTIDX: return "MIPS_LOCAL_GOTIDX";
    case DT_MIPS_HIDDEN_GOTIDX: return "MIPS_HIDDEN_GOTIDX";
    case DT_MIPS_PROTECTED_GOTIDX: return "MIPS_PROTECTED_GOTIDX";
    case DT_MIPS_OPTIONS: return "MIPS_OPTIONS";
    case DT_MIPS_INTERFACE: return "MIPS_INTERFACE";
    case DT_MIPS_DYNSTR_ALIGN: return "MIPS_DYNSTR_ALIGN";
    case DT_MIPS_INTERFACE_SIZE: return "MIPS_INTERFACE_SIZE";
    case DT_MIPS_RLD_TEXT_RESOLVE_ADDR: return "MIPS_RLD_TEXT_RESOLVE_ADDR";
    case DT_MIPS_PERF_SUFFIX: return "MIPS_PERF_SUFFIX";
    case DT_MIPS_COMPACT_SIZE: return "MIPS_COMPACT_SIZE";
    case DT_MIPS_GP_VALUE: return "MIPS_GP_VALUE";
    case DT_MIPS_AUX_DYNAMIC: return "MIPS_AUX_DYNAMIC";
    default:
      return NULL;
    }
}