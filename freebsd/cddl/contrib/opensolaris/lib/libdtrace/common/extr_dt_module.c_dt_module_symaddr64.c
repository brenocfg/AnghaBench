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
typedef  int uint_t ;
struct TYPE_6__ {TYPE_3__* cts_data; } ;
struct TYPE_7__ {int dm_aslen; TYPE_1__ dm_symtab; scalar_t__ dm_asmap; } ;
typedef  TYPE_2__ dt_module_t ;
struct TYPE_8__ {scalar_t__ st_value; int /*<<< orphan*/  st_size; } ;
typedef  int /*<<< orphan*/  GElf_Sym ;
typedef  scalar_t__ GElf_Addr ;
typedef  TYPE_3__ Elf64_Sym ;
typedef  scalar_t__ Elf64_Addr ;

/* Variables and functions */
 scalar_t__ MAX (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * dt_module_symgelf64 (TYPE_3__ const*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static GElf_Sym *
dt_module_symaddr64(dt_module_t *dmp, GElf_Addr addr,
    GElf_Sym *symp, uint_t *idp)
{
	const Elf64_Sym **asmap = (const Elf64_Sym **)dmp->dm_asmap;
	const Elf64_Sym *symtab = dmp->dm_symtab.cts_data;
	const Elf64_Sym *sym;

	uint_t i, mid, lo = 0, hi = dmp->dm_aslen - 1;
	Elf64_Addr v;

	if (dmp->dm_aslen == 0)
		return (NULL);

	while (hi - lo > 1) {
		mid = (lo + hi) / 2;
		if (addr >= asmap[mid]->st_value)
			lo = mid;
		else
			hi = mid;
	}

	i = addr < asmap[hi]->st_value ? lo : hi;
	sym = asmap[i];
	v = sym->st_value;

	/*
	 * If the previous entry has the same value, improve our choice.  The
	 * order of equal-valued symbols is determined by the comparison func.
	 */
	while (i-- != 0 && asmap[i]->st_value == v)
		sym = asmap[i];

	if (addr - sym->st_value < MAX(sym->st_size, 1)) {
		if (idp != NULL)
			*idp = (uint_t)(sym - symtab);
		return (dt_module_symgelf64(sym, symp));
	}

	return (NULL);
}