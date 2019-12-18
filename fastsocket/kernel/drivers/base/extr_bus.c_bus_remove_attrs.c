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
 int /*<<< orphan*/  bus_remove_file (struct bus_type*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void bus_remove_attrs(struct bus_type *bus)
{
	int i;

	if (bus->bus_attrs) {
		for (i = 0; attr_name(bus->bus_attrs[i]); i++)
			bus_remove_file(bus, &bus->bus_attrs[i]);
	}
}