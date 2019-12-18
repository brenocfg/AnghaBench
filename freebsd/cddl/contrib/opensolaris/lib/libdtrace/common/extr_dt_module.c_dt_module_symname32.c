#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint_t ;
struct TYPE_10__ {size_t ds_next; int ds_symid; } ;
typedef  TYPE_3__ dt_sym_t ;
struct TYPE_9__ {char* cts_data; } ;
struct TYPE_8__ {TYPE_5__* cts_data; } ;
struct TYPE_11__ {scalar_t__ dm_nsymelems; size_t dm_nsymbuckets; size_t* dm_symbuckets; TYPE_3__* dm_symchains; TYPE_2__ dm_strtab; TYPE_1__ dm_symtab; } ;
typedef  TYPE_4__ dt_module_t ;
struct TYPE_12__ {int st_name; } ;
typedef  int /*<<< orphan*/  GElf_Sym ;
typedef  TYPE_5__ Elf32_Sym ;

/* Variables and functions */
 int /*<<< orphan*/ * dt_module_symgelf32 (TYPE_5__ const*,int /*<<< orphan*/ *) ; 
 size_t dt_strtab_hash (char const*,int /*<<< orphan*/ *) ; 
 scalar_t__ strcmp (char const*,char const*) ; 

__attribute__((used)) static GElf_Sym *
dt_module_symname32(dt_module_t *dmp, const char *name,
    GElf_Sym *symp, uint_t *idp)
{
	const Elf32_Sym *symtab = dmp->dm_symtab.cts_data;
	const char *strtab = dmp->dm_strtab.cts_data;

	const Elf32_Sym *sym;
	const dt_sym_t *dsp;
	uint_t i, h;

	if (dmp->dm_nsymelems == 0)
		return (NULL);

	h = dt_strtab_hash(name, NULL) % dmp->dm_nsymbuckets;

	for (i = dmp->dm_symbuckets[h]; i != 0; i = dsp->ds_next) {
		dsp = &dmp->dm_symchains[i];
		sym = symtab + dsp->ds_symid;

		if (strcmp(name, strtab + sym->st_name) == 0) {
			if (idp != NULL)
				*idp = dsp->ds_symid;
			return (dt_module_symgelf32(sym, symp));
		}
	}

	return (NULL);
}