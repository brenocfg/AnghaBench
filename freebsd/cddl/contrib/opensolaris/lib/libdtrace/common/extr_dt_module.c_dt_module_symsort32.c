#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int uint_t ;
struct TYPE_9__ {int ds_symid; } ;
typedef  TYPE_3__ dt_sym_t ;
struct TYPE_8__ {int /*<<< orphan*/ * cts_data; } ;
struct TYPE_7__ {scalar_t__ cts_data; } ;
struct TYPE_10__ {int dm_symfree; int dm_aslen; scalar_t__ dm_asrsv; scalar_t__ dm_asmap; TYPE_2__ dm_strtab; TYPE_3__* dm_symchains; TYPE_1__ dm_symtab; } ;
typedef  TYPE_4__ dt_module_t ;
struct TYPE_11__ {scalar_t__ st_value; scalar_t__ st_size; int /*<<< orphan*/  st_info; } ;
typedef  TYPE_5__ Elf32_Sym ;

/* Variables and functions */
 scalar_t__ ELF32_ST_BIND (int /*<<< orphan*/ ) ; 
 scalar_t__ STB_LOCAL ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/ * dt_module_strtab ; 
 int /*<<< orphan*/  dt_module_symcomp32 ; 
 int /*<<< orphan*/  qsort (scalar_t__,scalar_t__,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
dt_module_symsort32(dt_module_t *dmp)
{
	Elf32_Sym *symtab = (Elf32_Sym *)dmp->dm_symtab.cts_data;
	Elf32_Sym **sympp = (Elf32_Sym **)dmp->dm_asmap;
	const dt_sym_t *dsp = dmp->dm_symchains + 1;
	uint_t i, n = dmp->dm_symfree;

	for (i = 1; i < n; i++, dsp++) {
		Elf32_Sym *sym = symtab + dsp->ds_symid;
		if (sym->st_value != 0 &&
		    (ELF32_ST_BIND(sym->st_info) != STB_LOCAL || sym->st_size))
			*sympp++ = sym;
	}

	dmp->dm_aslen = (uint_t)(sympp - (Elf32_Sym **)dmp->dm_asmap);
	assert(dmp->dm_aslen <= dmp->dm_asrsv);

	dt_module_strtab = dmp->dm_strtab.cts_data;
	qsort(dmp->dm_asmap, dmp->dm_aslen,
	    sizeof (Elf32_Sym *), dt_module_symcomp32);
	dt_module_strtab = NULL;
}