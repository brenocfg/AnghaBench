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

/* Variables and functions */
 scalar_t__ bus_register (int /*<<< orphan*/ *) ; 
 scalar_t__ device_register (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  get_device (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  panic (char*) ; 
 int /*<<< orphan*/  parisc_bus_type ; 
 int /*<<< orphan*/  root ; 

void init_parisc_bus(void)
{
	if (bus_register(&parisc_bus_type))
		panic("Could not register PA-RISC bus type\n");
	if (device_register(&root))
		panic("Could not register PA-RISC root device\n");
	get_device(&root);
}