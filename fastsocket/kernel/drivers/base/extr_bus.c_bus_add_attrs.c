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
struct bus_type {int /*<<< orphan*/ * bus_attrs; } ;

/* Variables and functions */
 scalar_t__ attr_name (int /*<<< orphan*/ ) ; 
 int bus_create_file (struct bus_type*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_remove_file (struct bus_type*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int bus_add_attrs(struct bus_type *bus)
{
	int error = 0;
	int i;

	if (bus->bus_attrs) {
		for (i = 0; attr_name(bus->bus_attrs[i]); i++) {
			error = bus_create_file(bus, &bus->bus_attrs[i]);
			if (error)
				goto err;
		}
	}
done:
	return error;
err:
	while (--i >= 0)
		bus_remove_file(bus, &bus->bus_attrs[i]);
	goto done;
}