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
struct gameport_driver {int /*<<< orphan*/  ignore; } ;
struct device_driver {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 struct gameport_driver* to_gameport_driver (struct device_driver*) ; 

__attribute__((used)) static int gameport_bus_match(struct device *dev, struct device_driver *drv)
{
	struct gameport_driver *gameport_drv = to_gameport_driver(drv);

	return !gameport_drv->ignore;
}