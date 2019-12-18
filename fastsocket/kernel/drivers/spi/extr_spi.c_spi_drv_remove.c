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
struct spi_driver {int (* remove ) (int /*<<< orphan*/ ) ;} ;
struct device {int /*<<< orphan*/  driver; } ;

/* Variables and functions */
 int stub1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  to_spi_device (struct device*) ; 
 struct spi_driver* to_spi_driver (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int spi_drv_remove(struct device *dev)
{
	const struct spi_driver		*sdrv = to_spi_driver(dev->driver);

	return sdrv->remove(to_spi_device(dev));
}