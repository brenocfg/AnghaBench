#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct dsa_switch {TYPE_3__* master_mii_bus; TYPE_2__* slave_mii_bus; TYPE_1__* pd; } ;
struct TYPE_6__ {char* id; int /*<<< orphan*/  dev; } ;
struct TYPE_5__ {char* name; int /*<<< orphan*/ * parent; int /*<<< orphan*/  id; int /*<<< orphan*/  write; int /*<<< orphan*/  read; void* priv; } ;
struct TYPE_4__ {int sw_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  MII_BUS_ID_SIZE ; 
 int /*<<< orphan*/  dsa_slave_phy_read ; 
 int /*<<< orphan*/  dsa_slave_phy_write ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char*,int) ; 

void dsa_slave_mii_bus_init(struct dsa_switch *ds)
{
	ds->slave_mii_bus->priv = (void *)ds;
	ds->slave_mii_bus->name = "dsa slave smi";
	ds->slave_mii_bus->read = dsa_slave_phy_read;
	ds->slave_mii_bus->write = dsa_slave_phy_write;
	snprintf(ds->slave_mii_bus->id, MII_BUS_ID_SIZE, "%s:%.2x",
			ds->master_mii_bus->id, ds->pd->sw_addr);
	ds->slave_mii_bus->parent = &ds->master_mii_bus->dev;
}