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
typedef  int u32 ;
struct temac_local {int /*<<< orphan*/  indirect_mutex; int /*<<< orphan*/  dev; struct mii_bus* mii_bus; int /*<<< orphan*/  mdio_irqs; } ;
struct resource {scalar_t__ start; } ;
struct mii_bus {char* name; int /*<<< orphan*/  irq; int /*<<< orphan*/  parent; int /*<<< orphan*/  write; int /*<<< orphan*/  read; struct temac_local* priv; int /*<<< orphan*/  id; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  MII_BUS_ID_SIZE ; 
 int /*<<< orphan*/  XTE_MC_OFFSET ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 struct mii_bus* mdiobus_alloc () ; 
 int /*<<< orphan*/  mdiobus_free (struct mii_bus*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  of_address_to_resource (struct device_node*,int /*<<< orphan*/ ,struct resource*) ; 
 int* of_get_property (struct device_node*,char*,int*) ; 
 int of_mdiobus_register (struct mii_bus*,struct device_node*) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,unsigned long long) ; 
 int /*<<< orphan*/  temac_indirect_in32 (struct temac_local*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  temac_indirect_out32 (struct temac_local*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  temac_mdio_read ; 
 int /*<<< orphan*/  temac_mdio_write ; 

int temac_mdio_setup(struct temac_local *lp, struct device_node *np)
{
	struct mii_bus *bus;
	const u32 *bus_hz;
	int clk_div;
	int rc, size;
	struct resource res;

	/* Calculate a reasonable divisor for the clock rate */
	clk_div = 0x3f; /* worst-case default setting */
	bus_hz = of_get_property(np, "clock-frequency", &size);
	if (bus_hz && size >= sizeof(*bus_hz)) {
		clk_div = (*bus_hz) / (2500 * 1000 * 2) - 1;
		if (clk_div < 1)
			clk_div = 1;
		if (clk_div > 0x3f)
			clk_div = 0x3f;
	}

	/* Enable the MDIO bus by asserting the enable bit and writing
	 * in the clock config */
	mutex_lock(&lp->indirect_mutex);
	temac_indirect_out32(lp, XTE_MC_OFFSET, 1 << 6 | clk_div);
	mutex_unlock(&lp->indirect_mutex);

	bus = mdiobus_alloc();
	if (!bus)
		return -ENOMEM;

	of_address_to_resource(np, 0, &res);
	snprintf(bus->id, MII_BUS_ID_SIZE, "%.8llx",
		 (unsigned long long)res.start);
	bus->priv = lp;
	bus->name = "Xilinx TEMAC MDIO";
	bus->read = temac_mdio_read;
	bus->write = temac_mdio_write;
	bus->parent = lp->dev;
	bus->irq = lp->mdio_irqs; /* preallocated IRQ table */

	lp->mii_bus = bus;

	rc = of_mdiobus_register(bus, np);
	if (rc)
		goto err_register;

	mutex_lock(&lp->indirect_mutex);
	dev_dbg(lp->dev, "MDIO bus registered;  MC:%x\n",
		temac_indirect_in32(lp, XTE_MC_OFFSET));
	mutex_unlock(&lp->indirect_mutex);
	return 0;

 err_register:
	mdiobus_free(bus);
	return rc;
}