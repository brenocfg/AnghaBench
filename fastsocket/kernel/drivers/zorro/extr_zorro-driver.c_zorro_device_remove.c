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
struct zorro_driver {int /*<<< orphan*/  (* remove ) (struct zorro_dev*) ;} ;
struct zorro_dev {int /*<<< orphan*/ * driver; } ;
struct device {int /*<<< orphan*/  driver; } ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct zorro_dev*) ; 
 struct zorro_dev* to_zorro_dev (struct device*) ; 
 struct zorro_driver* to_zorro_driver (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int zorro_device_remove(struct device *dev)
{
	struct zorro_dev *z = to_zorro_dev(dev);
	struct zorro_driver *drv = to_zorro_driver(dev->driver);

	if (drv) {
		if (drv->remove)
			drv->remove(z);
		z->driver = NULL;
	}
	return 0;
}