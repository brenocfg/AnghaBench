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
struct vlynq_driver {int /*<<< orphan*/  (* remove ) (int /*<<< orphan*/ ) ;} ;
struct device {int /*<<< orphan*/  driver; } ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  to_vlynq_device (struct device*) ; 
 struct vlynq_driver* to_vlynq_driver (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int vlynq_device_remove(struct device *dev)
{
	struct vlynq_driver *drv = to_vlynq_driver(dev->driver);

	if (drv->remove)
		drv->remove(to_vlynq_device(dev));

	return 0;
}