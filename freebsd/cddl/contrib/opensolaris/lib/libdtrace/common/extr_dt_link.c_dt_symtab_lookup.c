#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint_t ;
typedef  uintptr_t uint64_t ;
struct TYPE_9__ {scalar_t__ d_buf; } ;
struct TYPE_8__ {uintptr_t st_value; scalar_t__ st_shndx; uintptr_t st_size; int /*<<< orphan*/  st_info; } ;
typedef  TYPE_1__ GElf_Sym ;
typedef  int /*<<< orphan*/  Elf_Scn ;
typedef  TYPE_2__ Elf_Data ;
typedef  uintptr_t Elf64_Addr ;
typedef  int /*<<< orphan*/  Elf ;

/* Variables and functions */
 scalar_t__ GELF_ST_TYPE (int /*<<< orphan*/ ) ; 
 scalar_t__ STT_FUNC ; 
 int /*<<< orphan*/ * elf_getscn (int /*<<< orphan*/ *,scalar_t__) ; 
 TYPE_2__* elf_rawdata (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * gelf_getsym (TYPE_2__*,int,TYPE_1__*) ; 

__attribute__((used)) static int
dt_symtab_lookup(Elf_Data *data_sym, int start, int end, uintptr_t addr,
    uint_t shn, GElf_Sym *sym, int uses_funcdesc, Elf *elf)
{
	Elf64_Addr symval;
	Elf_Scn *opd_scn;
	Elf_Data *opd_desc;
	int i;

	for (i = start; i < end && gelf_getsym(data_sym, i, sym) != NULL; i++) {
		if (GELF_ST_TYPE(sym->st_info) == STT_FUNC) {
			symval = sym->st_value;
			if (uses_funcdesc) {
				opd_scn = elf_getscn(elf, sym->st_shndx);
				opd_desc = elf_rawdata(opd_scn, NULL);
				symval =
				    *(uint64_t*)((char *)opd_desc->d_buf + symval);
			}
			if ((uses_funcdesc || shn == sym->st_shndx) &&
			    symval <= addr && addr < symval + sym->st_size)
				return (0);
		}
	}

	return (-1);
}