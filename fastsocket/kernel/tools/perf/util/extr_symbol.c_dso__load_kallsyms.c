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
typedef  int /*<<< orphan*/  symbol_filter_t ;
struct map {size_t type; } ;
struct dso {scalar_t__ kernel; int /*<<< orphan*/  symtab_type; int /*<<< orphan*/ * symbols; } ;

/* Variables and functions */
 int /*<<< orphan*/  DSO_BINARY_TYPE__GUEST_KALLSYMS ; 
 int /*<<< orphan*/  DSO_BINARY_TYPE__KALLSYMS ; 
 scalar_t__ DSO_TYPE_GUEST_KERNEL ; 
 scalar_t__ dso__load_all_kallsyms (struct dso*,char const*,struct map*) ; 
 int dso__split_kallsyms (struct dso*,struct map*,int /*<<< orphan*/ ) ; 
 scalar_t__ symbol__restricted_filename (char const*,char*) ; 
 int /*<<< orphan*/  symbols__fixup_duplicate (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  symbols__fixup_end (int /*<<< orphan*/ *) ; 

int dso__load_kallsyms(struct dso *dso, const char *filename,
		       struct map *map, symbol_filter_t filter)
{
	if (symbol__restricted_filename(filename, "/proc/kallsyms"))
		return -1;

	if (dso__load_all_kallsyms(dso, filename, map) < 0)
		return -1;

	symbols__fixup_duplicate(&dso->symbols[map->type]);
	symbols__fixup_end(&dso->symbols[map->type]);

	if (dso->kernel == DSO_TYPE_GUEST_KERNEL)
		dso->symtab_type = DSO_BINARY_TYPE__GUEST_KALLSYMS;
	else
		dso->symtab_type = DSO_BINARY_TYPE__KALLSYMS;

	return dso__split_kallsyms(dso, map, filter);
}