#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u64 ;
struct machine {TYPE_1__** vmlinux_maps; int /*<<< orphan*/  kmaps; } ;
struct kmap {int /*<<< orphan*/ * kmaps; } ;
struct dso {int dummy; } ;
typedef  enum map_type { ____Placeholder_map_type } map_type ;
struct TYPE_4__ {int /*<<< orphan*/  unmap_ip; int /*<<< orphan*/  map_ip; } ;

/* Variables and functions */
 int MAP__NR_TYPES ; 
 int /*<<< orphan*/  identity__map_ip ; 
 int /*<<< orphan*/  machine__get_kernel_start_addr (struct machine*) ; 
 struct kmap* map__kmap (TYPE_1__*) ; 
 TYPE_1__* map__new2 (int /*<<< orphan*/ ,struct dso*,int) ; 
 int /*<<< orphan*/  map_groups__insert (int /*<<< orphan*/ *,TYPE_1__*) ; 

int __machine__create_kernel_maps(struct machine *machine, struct dso *kernel)
{
	enum map_type type;
	u64 start = machine__get_kernel_start_addr(machine);

	for (type = 0; type < MAP__NR_TYPES; ++type) {
		struct kmap *kmap;

		machine->vmlinux_maps[type] = map__new2(start, kernel, type);
		if (machine->vmlinux_maps[type] == NULL)
			return -1;

		machine->vmlinux_maps[type]->map_ip =
			machine->vmlinux_maps[type]->unmap_ip =
				identity__map_ip;
		kmap = map__kmap(machine->vmlinux_maps[type]);
		kmap->kmaps = &machine->kmaps;
		map_groups__insert(&machine->kmaps,
				   machine->vmlinux_maps[type]);
	}

	return 0;
}