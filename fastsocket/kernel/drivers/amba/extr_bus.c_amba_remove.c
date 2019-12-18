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
struct device {int /*<<< orphan*/  driver; } ;
struct amba_driver {int (* remove ) (int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int stub1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  to_amba_device (struct device*) ; 
 struct amba_driver* to_amba_driver (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int amba_remove(struct device *dev)
{
	struct amba_driver *drv = to_amba_driver(dev->driver);
	return drv->remove(to_amba_device(dev));
}