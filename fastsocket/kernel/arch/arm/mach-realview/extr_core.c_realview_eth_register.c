#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct resource {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/ * platform_data; } ;
struct TYPE_5__ {char const* name; TYPE_1__ dev; struct resource* resource; } ;

/* Variables and functions */
 int platform_device_register (TYPE_2__*) ; 
 TYPE_2__ realview_eth_device ; 
 int /*<<< orphan*/  smsc911x_config ; 
 scalar_t__ strcmp (char const*,char*) ; 

int realview_eth_register(const char *name, struct resource *res)
{
	if (name)
		realview_eth_device.name = name;
	realview_eth_device.resource = res;
	if (strcmp(realview_eth_device.name, "smsc911x") == 0)
		realview_eth_device.dev.platform_data = &smsc911x_config;

	return platform_device_register(&realview_eth_device);
}