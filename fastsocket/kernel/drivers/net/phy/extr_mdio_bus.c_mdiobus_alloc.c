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
struct mii_bus {int /*<<< orphan*/  state; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  MDIOBUS_ALLOCATED ; 
 struct mii_bus* kzalloc (int,int /*<<< orphan*/ ) ; 

struct mii_bus *mdiobus_alloc(void)
{
	struct mii_bus *bus;

	bus = kzalloc(sizeof(*bus), GFP_KERNEL);
	if (bus != NULL)
		bus->state = MDIOBUS_ALLOCATED;

	return bus;
}