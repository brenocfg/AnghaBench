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
struct device {struct bus_type* bus; } ;
struct bus_type {TYPE_1__* p; } ;
struct TYPE_2__ {scalar_t__ drivers_autoprobe; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int) ; 
 int device_attach (struct device*) ; 

void bus_probe_device(struct device *dev)
{
	struct bus_type *bus = dev->bus;
	int ret;

	if (bus && bus->p->drivers_autoprobe) {
		ret = device_attach(dev);
		WARN_ON(ret < 0);
	}
}