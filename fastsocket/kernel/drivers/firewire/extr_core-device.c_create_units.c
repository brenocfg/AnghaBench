#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/ * parent; int /*<<< orphan*/ * type; int /*<<< orphan*/ * bus; } ;
struct TYPE_6__ {int /*<<< orphan*/  attrs; } ;
struct fw_unit {TYPE_1__ device; TYPE_2__ attribute_group; scalar_t__ directory; } ;
struct fw_device {int /*<<< orphan*/  device; int /*<<< orphan*/ * config_rom; } ;
struct fw_csr_iterator {scalar_t__ p; } ;

/* Variables and functions */
 scalar_t__ ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BUILD_BUG_ON (int) ; 
 int CSR_DIRECTORY ; 
 int CSR_UNIT ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  config_rom_attributes ; 
 int /*<<< orphan*/  dev_name (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_set_name (TYPE_1__*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ device_register (TYPE_1__*) ; 
 int /*<<< orphan*/  fw_bus_type ; 
 int /*<<< orphan*/  fw_csr_iterator_init (struct fw_csr_iterator*,int /*<<< orphan*/ *) ; 
 scalar_t__ fw_csr_iterator_next (struct fw_csr_iterator*,int*,int*) ; 
 int /*<<< orphan*/  fw_error (char*) ; 
 int /*<<< orphan*/  fw_unit_attributes ; 
 int /*<<< orphan*/  fw_unit_type ; 
 int /*<<< orphan*/  init_fw_attribute_group (TYPE_1__*,int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  kfree (struct fw_unit*) ; 
 struct fw_unit* kzalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void create_units(struct fw_device *device)
{
	struct fw_csr_iterator ci;
	struct fw_unit *unit;
	int key, value, i;

	i = 0;
	fw_csr_iterator_init(&ci, &device->config_rom[5]);
	while (fw_csr_iterator_next(&ci, &key, &value)) {
		if (key != (CSR_UNIT | CSR_DIRECTORY))
			continue;

		/*
		 * Get the address of the unit directory and try to
		 * match the drivers id_tables against it.
		 */
		unit = kzalloc(sizeof(*unit), GFP_KERNEL);
		if (unit == NULL) {
			fw_error("failed to allocate memory for unit\n");
			continue;
		}

		unit->directory = ci.p + value - 1;
		unit->device.bus = &fw_bus_type;
		unit->device.type = &fw_unit_type;
		unit->device.parent = &device->device;
		dev_set_name(&unit->device, "%s.%d", dev_name(&device->device), i++);

		BUILD_BUG_ON(ARRAY_SIZE(unit->attribute_group.attrs) <
				ARRAY_SIZE(fw_unit_attributes) +
				ARRAY_SIZE(config_rom_attributes));
		init_fw_attribute_group(&unit->device,
					fw_unit_attributes,
					&unit->attribute_group);

		if (device_register(&unit->device) < 0)
			goto skip_unit;

		continue;

	skip_unit:
		kfree(unit);
	}
}