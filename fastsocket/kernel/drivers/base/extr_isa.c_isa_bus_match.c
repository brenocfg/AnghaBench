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
struct isa_driver {scalar_t__ (* match ) (struct device*,int /*<<< orphan*/ ) ;} ;
struct device_driver {int dummy; } ;
struct device {struct isa_driver* platform_data; } ;
struct TYPE_2__ {int /*<<< orphan*/  id; } ;

/* Variables and functions */
 scalar_t__ stub1 (struct device*,int /*<<< orphan*/ ) ; 
 TYPE_1__* to_isa_dev (struct device*) ; 
 struct isa_driver* to_isa_driver (struct device_driver*) ; 

__attribute__((used)) static int isa_bus_match(struct device *dev, struct device_driver *driver)
{
	struct isa_driver *isa_driver = to_isa_driver(driver);

	if (dev->platform_data == isa_driver) {
		if (!isa_driver->match ||
			isa_driver->match(dev, to_isa_dev(dev)->id))
			return 1;
		dev->platform_data = NULL;
	}
	return 0;
}