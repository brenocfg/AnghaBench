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
struct bus_type {char const* name; int /*<<< orphan*/  dev_attrs; int /*<<< orphan*/  shutdown; int /*<<< orphan*/  resume; int /*<<< orphan*/  suspend; int /*<<< orphan*/  remove; int /*<<< orphan*/  probe; int /*<<< orphan*/  match; } ;

/* Variables and functions */
 int bus_register (struct bus_type*) ; 
 int /*<<< orphan*/  of_platform_bus_match ; 
 int /*<<< orphan*/  of_platform_device_attrs ; 
 int /*<<< orphan*/  of_platform_device_probe ; 
 int /*<<< orphan*/  of_platform_device_remove ; 
 int /*<<< orphan*/  of_platform_device_resume ; 
 int /*<<< orphan*/  of_platform_device_shutdown ; 
 int /*<<< orphan*/  of_platform_device_suspend ; 

int of_bus_type_init(struct bus_type *bus, const char *name)
{
	bus->name = name;
	bus->match = of_platform_bus_match;
	bus->probe = of_platform_device_probe;
	bus->remove = of_platform_device_remove;
	bus->suspend = of_platform_device_suspend;
	bus->resume = of_platform_device_resume;
	bus->shutdown = of_platform_device_shutdown;
	bus->dev_attrs = of_platform_device_attrs;
	return bus_register(bus);
}