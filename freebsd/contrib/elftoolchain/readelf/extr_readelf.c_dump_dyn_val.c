#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uintmax_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_6__ {int /*<<< orphan*/  e_machine; } ;
struct readelf {TYPE_1__ ehdr; } ;
struct TYPE_7__ {int /*<<< orphan*/  d_val; } ;
struct TYPE_8__ {int d_tag; TYPE_2__ d_un; } ;
typedef  TYPE_3__ GElf_Dyn ;

/* Variables and functions */
#define  DT_AUXILIARY 172 
#define  DT_DEBUG 171 
#define  DT_FILTER 170 
#define  DT_FINI 169 
#define  DT_FINI_ARRAYSZ 168 
#define  DT_FLAGS 167 
#define  DT_FLAGS_1 166 
#define  DT_GNU_CONFLICT 165 
#define  DT_GNU_CONFLICTSZ 164 
#define  DT_GNU_HASH 163 
#define  DT_GNU_LIBLIST 162 
#define  DT_GNU_LIBLISTSZ 161 
#define  DT_GNU_PRELINKED 160 
#define  DT_HASH 159 
 int DT_HIPROC ; 
#define  DT_INIT 158 
#define  DT_INIT_ARRAYSZ 157 
#define  DT_JMPREL 156 
 int DT_LOPROC ; 
#define  DT_NEEDED 155 
#define  DT_NULL 154 
#define  DT_PLTGOT 153 
#define  DT_PLTREL 152 
#define  DT_PLTRELSZ 151 
#define  DT_PREINIT_ARRAYSZ 150 
#define  DT_REL 149 
#define  DT_RELA 148 
#define  DT_RELACOUNT 147 
#define  DT_RELAENT 146 
#define  DT_RELASZ 145 
#define  DT_RELCOUNT 144 
#define  DT_RELENT 143 
#define  DT_RELSZ 142 
#define  DT_RPATH 141 
#define  DT_RUNPATH 140 
#define  DT_SONAME 139 
#define  DT_STRSZ 138 
#define  DT_STRTAB 137 
#define  DT_SYMBOLIC 136 
#define  DT_SYMENT 135 
#define  DT_SYMTAB 134 
#define  DT_TEXTREL 133 
#define  DT_VERDEF 132 
#define  DT_VERDEFNUM 131 
#define  DT_VERNEED 130 
#define  DT_VERNEEDNUM 129 
#define  DT_VERSYM 128 
 int /*<<< orphan*/  dt_flags ; 
 int /*<<< orphan*/  dt_flags_1 ; 
 char* dt_type (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dump_arch_dyn_val (struct readelf*,TYPE_3__*) ; 
 int /*<<< orphan*/  dump_flags (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* dyn_str (struct readelf*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 char* timestamp (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
dump_dyn_val(struct readelf *re, GElf_Dyn *dyn, uint32_t stab)
{
	const char *name;

	if (dyn->d_tag >= DT_LOPROC && dyn->d_tag <= DT_HIPROC &&
	    dyn->d_tag != DT_AUXILIARY && dyn->d_tag != DT_FILTER) {
		dump_arch_dyn_val(re, dyn);
		return;
	}

	/* These entry values are index into the string table. */
	name = NULL;
	if (dyn->d_tag == DT_AUXILIARY || dyn->d_tag == DT_FILTER ||
	    dyn->d_tag == DT_NEEDED || dyn->d_tag == DT_SONAME ||
	    dyn->d_tag == DT_RPATH || dyn->d_tag == DT_RUNPATH)
		name = dyn_str(re, stab, dyn->d_un.d_val);

	switch(dyn->d_tag) {
	case DT_NULL:
	case DT_PLTGOT:
	case DT_HASH:
	case DT_STRTAB:
	case DT_SYMTAB:
	case DT_RELA:
	case DT_INIT:
	case DT_SYMBOLIC:
	case DT_REL:
	case DT_DEBUG:
	case DT_TEXTREL:
	case DT_JMPREL:
	case DT_FINI:
	case DT_VERDEF:
	case DT_VERNEED:
	case DT_VERSYM:
	case DT_GNU_HASH:
	case DT_GNU_LIBLIST:
	case DT_GNU_CONFLICT:
		printf(" 0x%jx\n", (uintmax_t) dyn->d_un.d_val);
		break;
	case DT_PLTRELSZ:
	case DT_RELASZ:
	case DT_RELAENT:
	case DT_STRSZ:
	case DT_SYMENT:
	case DT_RELSZ:
	case DT_RELENT:
	case DT_PREINIT_ARRAYSZ:
	case DT_INIT_ARRAYSZ:
	case DT_FINI_ARRAYSZ:
	case DT_GNU_CONFLICTSZ:
	case DT_GNU_LIBLISTSZ:
		printf(" %ju (bytes)\n", (uintmax_t) dyn->d_un.d_val);
		break;
 	case DT_RELACOUNT:
	case DT_RELCOUNT:
	case DT_VERDEFNUM:
	case DT_VERNEEDNUM:
		printf(" %ju\n", (uintmax_t) dyn->d_un.d_val);
		break;
	case DT_AUXILIARY:
		printf(" Auxiliary library: [%s]\n", name);
		break;
	case DT_FILTER:
		printf(" Filter library: [%s]\n", name);
		break;
	case DT_NEEDED:
		printf(" Shared library: [%s]\n", name);
		break;
	case DT_SONAME:
		printf(" Library soname: [%s]\n", name);
		break;
	case DT_RPATH:
		printf(" Library rpath: [%s]\n", name);
		break;
	case DT_RUNPATH:
		printf(" Library runpath: [%s]\n", name);
		break;
	case DT_PLTREL:
		printf(" %s\n", dt_type(re->ehdr.e_machine, dyn->d_un.d_val));
		break;
	case DT_GNU_PRELINKED:
		printf(" %s\n", timestamp(dyn->d_un.d_val));
		break;
	case DT_FLAGS:
		dump_flags(dt_flags, dyn->d_un.d_val);
		break;
	case DT_FLAGS_1:
		dump_flags(dt_flags_1, dyn->d_un.d_val);
		break;
	default:
		printf("\n");
	}
}