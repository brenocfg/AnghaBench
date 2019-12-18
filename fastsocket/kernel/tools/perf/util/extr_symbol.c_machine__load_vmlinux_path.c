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
struct machine {struct map** vmlinux_maps; } ;
typedef  enum map_type { ____Placeholder_map_type } map_type ;

/* Variables and functions */
 int dso__load_vmlinux_path (int /*<<< orphan*/ ,struct map*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dso__set_loaded (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  map__reloc_vmlinux (struct map*) ; 

int machine__load_vmlinux_path(struct machine *machine, enum map_type type,
			       symbol_filter_t filter)
{
	struct map *map = machine->vmlinux_maps[type];
	int ret = dso__load_vmlinux_path(map->dso, map, filter);

	if (ret > 0) {
		dso__set_loaded(map->dso, type);
		map__reloc_vmlinux(map);
	}

	return ret;
}