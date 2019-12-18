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
typedef  int uint8_t ;
typedef  uintptr_t uint64_t ;
typedef  unsigned int uint32_t ;
struct modctl {int /*<<< orphan*/  mod_modname; } ;
typedef  int /*<<< orphan*/  machine_inst_t ;
struct TYPE_7__ {uintptr_t addr; int flags; scalar_t__ size; } ;
typedef  TYPE_2__ kernel_section_t ;
struct TYPE_6__ {int n_strx; } ;
struct TYPE_8__ {int n_type; uintptr_t n_value; int n_sect; int n_desc; TYPE_1__ n_un; } ;
typedef  TYPE_3__ kernel_nlist_t ;

/* Variables and functions */
 scalar_t__ MOD_IS_MACH_KERNEL (struct modctl*) ; 
 int N_ABS ; 
 int N_ARM_THUMB_DEF ; 
 int N_EXT ; 
 int N_SECT ; 
 int N_TYPE ; 
 int S_ATTR_PURE_INSTRUCTIONS ; 
 scalar_t__ fbt_excluded (char const*) ; 
 int /*<<< orphan*/  fbt_provide_probe (struct modctl*,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
fbt_provide_kernel_section(struct modctl *ctl, kernel_section_t *sect, kernel_nlist_t *sym, uint32_t nsyms, const char *strings)
{
	uintptr_t sect_start = (uintptr_t)sect->addr;
	uintptr_t sect_end = (uintptr_t)sect->size + sect->addr;
	unsigned int i;

	if ((sect->flags & S_ATTR_PURE_INSTRUCTIONS) != S_ATTR_PURE_INSTRUCTIONS) {
		return;
	}

	for (i = 0; i < nsyms; i++) {
		uint8_t         n_type = sym[i].n_type & (N_TYPE | N_EXT);
		const char           *name = strings + sym[i].n_un.n_strx;
		uint64_t limit;

		if (sym[i].n_value < sect_start || sym[i].n_value > sect_end)
			continue;

		/* Check that the symbol is a global and that it has a name. */
		if (((N_SECT | N_EXT) != n_type && (N_ABS | N_EXT) != n_type))
			continue;

		if (0 == sym[i].n_un.n_strx)	/* iff a null, "", name. */
			continue;

		/* Lop off omnipresent leading underscore. */
		if (*name == '_')
			name += 1;

#if defined(__arm__)
		// Skip non-thumb functions on arm32
		if (sym[i].n_sect == 1 && !(sym[i].n_desc & N_ARM_THUMB_DEF)) {
			continue;
		}
#endif /* defined(__arm__) */

		if (MOD_IS_MACH_KERNEL(ctl) && fbt_excluded(name))
			continue;

		/*
		 * Find the function boundary by looking at either the
		 * end of the section or the beginning of the next symbol
		 */
		if (i == nsyms - 1) {
			limit = sect_end;
		}
		else {
			limit = sym[i + 1].n_value;
		}

		fbt_provide_probe(ctl, ctl->mod_modname, name, (machine_inst_t*)sym[i].n_value, (machine_inst_t*)limit);
	}

}