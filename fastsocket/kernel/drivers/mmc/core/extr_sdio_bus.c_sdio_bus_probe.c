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
struct sdio_func {int dummy; } ;
struct sdio_driver {int (* probe ) (struct sdio_func*,struct sdio_device_id const*) ;} ;
struct sdio_device_id {int dummy; } ;
struct device {int /*<<< orphan*/  driver; } ;

/* Variables and functions */
 int ENODEV ; 
 struct sdio_func* dev_to_sdio_func (struct device*) ; 
 int /*<<< orphan*/  sdio_claim_host (struct sdio_func*) ; 
 struct sdio_device_id* sdio_match_device (struct sdio_func*,struct sdio_driver*) ; 
 int /*<<< orphan*/  sdio_release_host (struct sdio_func*) ; 
 int sdio_set_block_size (struct sdio_func*,int /*<<< orphan*/ ) ; 
 int stub1 (struct sdio_func*,struct sdio_device_id const*) ; 
 struct sdio_driver* to_sdio_driver (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int sdio_bus_probe(struct device *dev)
{
	struct sdio_driver *drv = to_sdio_driver(dev->driver);
	struct sdio_func *func = dev_to_sdio_func(dev);
	const struct sdio_device_id *id;
	int ret;

	id = sdio_match_device(func, drv);
	if (!id)
		return -ENODEV;

	/* Set the default block size so the driver is sure it's something
	 * sensible. */
	sdio_claim_host(func);
	ret = sdio_set_block_size(func, 0);
	sdio_release_host(func);
	if (ret)
		return ret;

	return drv->probe(func, id);
}