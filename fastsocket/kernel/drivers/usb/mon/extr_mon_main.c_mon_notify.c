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
struct notifier_block {int dummy; } ;

/* Variables and functions */
 int NOTIFY_OK ; 
#define  USB_BUS_ADD 129 
#define  USB_BUS_REMOVE 128 
 int /*<<< orphan*/  mon_bus_add (void*) ; 
 int /*<<< orphan*/  mon_bus_remove (void*) ; 

__attribute__((used)) static int mon_notify(struct notifier_block *self, unsigned long action,
		      void *dev)
{
	switch (action) {
	case USB_BUS_ADD:
		mon_bus_add(dev);
		break;
	case USB_BUS_REMOVE:
		mon_bus_remove(dev);
	}
	return NOTIFY_OK;
}