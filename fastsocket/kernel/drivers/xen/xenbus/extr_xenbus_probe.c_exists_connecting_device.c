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
struct device_driver {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  bus; } ;

/* Variables and functions */
 int bus_for_each_dev (int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct device_driver*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  is_device_connecting ; 
 TYPE_1__ xenbus_frontend ; 

__attribute__((used)) static int exists_connecting_device(struct device_driver *drv)
{
	return bus_for_each_dev(&xenbus_frontend.bus, NULL, drv,
				is_device_connecting);
}