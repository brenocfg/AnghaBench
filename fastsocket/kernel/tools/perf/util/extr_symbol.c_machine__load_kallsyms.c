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
struct map {int /*<<< orphan*/  dso; } ;
struct machine {int /*<<< orphan*/  kmaps; struct map** vmlinux_maps; } ;
typedef  enum map_type { ____Placeholder_map_type } map_type ;

/* Variables and functions */
 int /*<<< orphan*/  __map_groups__fixup_end (int /*<<< orphan*/ *,int) ; 
 int dso__load_kallsyms (int /*<<< orphan*/ ,char const*,struct map*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dso__set_loaded (int /*<<< orphan*/ ,int) ; 

int machine__load_kallsyms(struct machine *machine, const char *filename,
			   enum map_type type, symbol_filter_t filter)
{
	struct map *map = machine->vmlinux_maps[type];
	int ret = dso__load_kallsyms(map->dso, filename, map, filter);

	if (ret > 0) {
		dso__set_loaded(map->dso, type);
		/*
		 * Since /proc/kallsyms will have multiple sessions for the
		 * kernel, with modules between them, fixup the end of all
		 * sections.
		 */
		__map_groups__fixup_end(&machine->kmaps, type);
	}

	return ret;
}