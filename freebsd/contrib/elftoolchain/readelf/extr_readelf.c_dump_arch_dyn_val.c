#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uintmax_t ;
struct TYPE_5__ {int e_machine; } ;
struct readelf {TYPE_1__ ehdr; } ;
struct TYPE_6__ {int /*<<< orphan*/  d_val; } ;
struct TYPE_7__ {TYPE_2__ d_un; int /*<<< orphan*/  d_tag; } ;
typedef  TYPE_3__ GElf_Dyn ;

/* Variables and functions */
#define  DT_MIPS_AUX_DYNAMIC 174 
#define  DT_MIPS_BASE_ADDRESS 173 
#define  DT_MIPS_COMPACT_SIZE 172 
#define  DT_MIPS_CONFLICT 171 
#define  DT_MIPS_CONFLICTNO 170 
#define  DT_MIPS_CXX_FLAGS 169 
#define  DT_MIPS_DELTA_CLASS 168 
#define  DT_MIPS_DELTA_CLASSSYM 167 
#define  DT_MIPS_DELTA_CLASSSYM_NO 166 
#define  DT_MIPS_DELTA_CLASS_NO 165 
#define  DT_MIPS_DELTA_INSTANCE 164 
#define  DT_MIPS_DELTA_INSTANCE_NO 163 
#define  DT_MIPS_DELTA_RELOC 162 
#define  DT_MIPS_DELTA_RELOC_NO 161 
#define  DT_MIPS_DELTA_SYM 160 
#define  DT_MIPS_DELTA_SYM_NO 159 
#define  DT_MIPS_DYNSTR_ALIGN 158 
#define  DT_MIPS_FLAGS 157 
#define  DT_MIPS_GOTSYM 156 
#define  DT_MIPS_GP_VALUE 155 
#define  DT_MIPS_HIDDEN_GOTIDX 154 
#define  DT_MIPS_HIPAGENO 153 
#define  DT_MIPS_ICHECKSUM 152 
#define  DT_MIPS_INTERFACE 151 
#define  DT_MIPS_INTERFACE_SIZE 150 
#define  DT_MIPS_IVERSION 149 
#define  DT_MIPS_LIBLIST 148 
#define  DT_MIPS_LIBLISTNO 147 
#define  DT_MIPS_LOCALPAGE_GOTIDX 146 
#define  DT_MIPS_LOCAL_GOTIDX 145 
#define  DT_MIPS_LOCAL_GOTNO 144 
#define  DT_MIPS_OPTIONS 143 
#define  DT_MIPS_PERF_SUFFIX 142 
#define  DT_MIPS_PIXIE_INIT 141 
#define  DT_MIPS_PLTGOT 140 
#define  DT_MIPS_PROTECTED_GOTIDX 139 
#define  DT_MIPS_RLD_MAP 138 
#define  DT_MIPS_RLD_OBJ_UPDATE 137 
#define  DT_MIPS_RLD_TEXT_RESOLVE_ADDR 136 
#define  DT_MIPS_RLD_VERSION 135 
#define  DT_MIPS_RWPLT 134 
#define  DT_MIPS_SYMBOL_LIB 133 
#define  DT_MIPS_SYMTABNO 132 
#define  DT_MIPS_TIME_STAMP 131 
#define  DT_MIPS_UNREFEXTNO 130 
#define  EM_MIPS 129 
#define  EM_MIPS_RS3_LE 128 
 int /*<<< orphan*/  printf (char*,...) ; 
 char* timestamp (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
dump_arch_dyn_val(struct readelf *re, GElf_Dyn *dyn)
{
	switch (re->ehdr.e_machine) {
	case EM_MIPS:
	case EM_MIPS_RS3_LE:
		switch (dyn->d_tag) {
		case DT_MIPS_RLD_VERSION:
		case DT_MIPS_LOCAL_GOTNO:
		case DT_MIPS_CONFLICTNO:
		case DT_MIPS_LIBLISTNO:
		case DT_MIPS_SYMTABNO:
		case DT_MIPS_UNREFEXTNO:
		case DT_MIPS_GOTSYM:
		case DT_MIPS_HIPAGENO:
		case DT_MIPS_DELTA_CLASS_NO:
		case DT_MIPS_DELTA_INSTANCE_NO:
		case DT_MIPS_DELTA_RELOC_NO:
		case DT_MIPS_DELTA_SYM_NO:
		case DT_MIPS_DELTA_CLASSSYM_NO:
		case DT_MIPS_LOCALPAGE_GOTIDX:
		case DT_MIPS_LOCAL_GOTIDX:
		case DT_MIPS_HIDDEN_GOTIDX:
		case DT_MIPS_PROTECTED_GOTIDX:
			printf(" %ju\n", (uintmax_t) dyn->d_un.d_val);
			break;
		case DT_MIPS_ICHECKSUM:
		case DT_MIPS_FLAGS:
		case DT_MIPS_BASE_ADDRESS:
		case DT_MIPS_CONFLICT:
		case DT_MIPS_LIBLIST:
		case DT_MIPS_RLD_MAP:
		case DT_MIPS_DELTA_CLASS:
		case DT_MIPS_DELTA_INSTANCE:
		case DT_MIPS_DELTA_RELOC:
		case DT_MIPS_DELTA_SYM:
		case DT_MIPS_DELTA_CLASSSYM:
		case DT_MIPS_CXX_FLAGS:
		case DT_MIPS_PIXIE_INIT:
		case DT_MIPS_SYMBOL_LIB:
		case DT_MIPS_OPTIONS:
		case DT_MIPS_INTERFACE:
		case DT_MIPS_DYNSTR_ALIGN:
		case DT_MIPS_INTERFACE_SIZE:
		case DT_MIPS_RLD_TEXT_RESOLVE_ADDR:
		case DT_MIPS_COMPACT_SIZE:
		case DT_MIPS_GP_VALUE:
		case DT_MIPS_AUX_DYNAMIC:
		case DT_MIPS_PLTGOT:
		case DT_MIPS_RLD_OBJ_UPDATE:
		case DT_MIPS_RWPLT:
			printf(" 0x%jx\n", (uintmax_t) dyn->d_un.d_val);
			break;
		case DT_MIPS_IVERSION:
		case DT_MIPS_PERF_SUFFIX:
		case DT_MIPS_TIME_STAMP:
			printf(" %s\n", timestamp(dyn->d_un.d_val));
			break;
		default:
			printf("\n");
			break;
		}
		break;
	default:
		printf("\n");
		break;
	}
}