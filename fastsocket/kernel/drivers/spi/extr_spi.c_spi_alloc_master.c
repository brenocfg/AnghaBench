#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  parent; int /*<<< orphan*/ * class; } ;
struct spi_master {TYPE_1__ dev; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  device_initialize (TYPE_1__*) ; 
 int /*<<< orphan*/  get_device (struct device*) ; 
 struct spi_master* kzalloc (unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spi_master_class ; 
 int /*<<< orphan*/  spi_master_set_devdata (struct spi_master*,struct spi_master*) ; 

struct spi_master *spi_alloc_master(struct device *dev, unsigned size)
{
	struct spi_master	*master;

	if (!dev)
		return NULL;

	master = kzalloc(size + sizeof *master, GFP_KERNEL);
	if (!master)
		return NULL;

	device_initialize(&master->dev);
	master->dev.class = &spi_master_class;
	master->dev.parent = get_device(dev);
	spi_master_set_devdata(master, &master[1]);

	return master;
}