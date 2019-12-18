#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct ssb_device {int dummy; } ;
struct TYPE_4__ {struct ssb_device* dev; } ;
struct TYPE_3__ {struct ssb_device* dev; } ;
struct ssb_bus {TYPE_2__ chipco; TYPE_1__ pcicore; } ;

/* Variables and functions */
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  ssb_broadcast_value (struct ssb_device*,int,int /*<<< orphan*/ ) ; 

void ssb_commit_settings(struct ssb_bus *bus)
{
	struct ssb_device *dev;

#ifdef CONFIG_SSB_DRIVER_PCICORE
	dev = bus->chipco.dev ? bus->chipco.dev : bus->pcicore.dev;
#else
	dev = bus->chipco.dev;
#endif
	if (WARN_ON(!dev))
		return;
	/* This forces an update of the cached registers. */
	ssb_broadcast_value(dev, 0xFD8, 0);
}