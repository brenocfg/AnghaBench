#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_5__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ sh_type; int sh_size; } ;
struct section {TYPE_3__* symtab; TYPE_2__ shdr; TYPE_1__* link; } ;
struct TYPE_9__ {int e_shnum; } ;
struct TYPE_8__ {scalar_t__ st_shndx; int st_value; int st_size; int /*<<< orphan*/  st_other; int /*<<< orphan*/  st_info; } ;
struct TYPE_6__ {char* strtab; } ;
typedef  TYPE_3__ Elf32_Sym ;

/* Variables and functions */
 int /*<<< orphan*/  ELF32_ST_BIND (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ELF32_ST_TYPE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ELF32_ST_VISIBILITY (int /*<<< orphan*/ ) ; 
 scalar_t__ SHN_ABS ; 
 scalar_t__ SHT_SYMTAB ; 
 TYPE_5__ ehdr ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 struct section* secs ; 
 char* sym_bind (int /*<<< orphan*/ ) ; 
 char* sym_name (char*,TYPE_3__*) ; 
 char* sym_type (int /*<<< orphan*/ ) ; 
 char* sym_visibility (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void print_absolute_symbols(void)
{
	int i;
	printf("Absolute symbols\n");
	printf(" Num:    Value Size  Type       Bind        Visibility  Name\n");
	for (i = 0; i < ehdr.e_shnum; i++) {
		struct section *sec = &secs[i];
		char *sym_strtab;
		Elf32_Sym *sh_symtab;
		int j;

		if (sec->shdr.sh_type != SHT_SYMTAB) {
			continue;
		}
		sh_symtab = sec->symtab;
		sym_strtab = sec->link->strtab;
		for (j = 0; j < sec->shdr.sh_size/sizeof(Elf32_Sym); j++) {
			Elf32_Sym *sym;
			const char *name;
			sym = &sec->symtab[j];
			name = sym_name(sym_strtab, sym);
			if (sym->st_shndx != SHN_ABS) {
				continue;
			}
			printf("%5d %08x %5d %10s %10s %12s %s\n",
				j, sym->st_value, sym->st_size,
				sym_type(ELF32_ST_TYPE(sym->st_info)),
				sym_bind(ELF32_ST_BIND(sym->st_info)),
				sym_visibility(ELF32_ST_VISIBILITY(sym->st_other)),
				name);
		}
	}
	printf("\n");
}