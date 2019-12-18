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
struct device_driver {int dummy; } ;
struct device {int dummy; } ;
struct amba_driver {int /*<<< orphan*/  id_table; } ;
struct amba_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/ * amba_lookup (int /*<<< orphan*/ ,struct amba_device*) ; 
 struct amba_device* to_amba_device (struct device*) ; 
 struct amba_driver* to_amba_driver (struct device_driver*) ; 

__attribute__((used)) static int amba_match(struct device *dev, struct device_driver *drv)
{
	struct amba_device *pcdev = to_amba_device(dev);
	struct amba_driver *pcdrv = to_amba_driver(drv);

	return amba_lookup(pcdrv->id_table, pcdev) != NULL;
}