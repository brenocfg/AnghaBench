#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {struct device* parent; } ;
struct spi_master {TYPE_1__ dev; } ;
struct TYPE_4__ {int /*<<< orphan*/  release; int /*<<< orphan*/ * bus; struct device* parent; } ;
struct spi_device {TYPE_2__ dev; struct spi_master* master; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int /*<<< orphan*/  device_initialize (TYPE_2__*) ; 
 struct spi_device* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spi_bus_type ; 
 int /*<<< orphan*/  spi_master_get (struct spi_master*) ; 
 int /*<<< orphan*/  spi_master_put (struct spi_master*) ; 
 int /*<<< orphan*/  spidev_release ; 

struct spi_device *spi_alloc_device(struct spi_master *master)
{
	struct spi_device	*spi;
	struct device		*dev = master->dev.parent;

	if (!spi_master_get(master))
		return NULL;

	spi = kzalloc(sizeof *spi, GFP_KERNEL);
	if (!spi) {
		dev_err(dev, "cannot alloc spi_device\n");
		spi_master_put(master);
		return NULL;
	}

	spi->master = master;
	spi->dev.parent = dev;
	spi->dev.bus = &spi_bus_type;
	spi->dev.release = spidev_release;
	device_initialize(&spi->dev);
	return spi;
}