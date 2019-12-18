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
typedef  int /*<<< orphan*/  u16 ;
struct mii_bus {int (* read ) (struct mii_bus*,int,int /*<<< orphan*/ ) ;int /*<<< orphan*/  mdio_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  in_interrupt () ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int stub1 (struct mii_bus*,int,int /*<<< orphan*/ ) ; 

int mdiobus_read(struct mii_bus *bus, int addr, u16 regnum)
{
	int retval;

	BUG_ON(in_interrupt());

	mutex_lock(&bus->mdio_lock);
	retval = bus->read(bus, addr, regnum);
	mutex_unlock(&bus->mdio_lock);

	return retval;
}