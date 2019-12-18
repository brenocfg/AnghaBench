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
typedef  int /*<<< orphan*/  u16 ;
struct device {char const* name; int running; struct device* next; scalar_t__ num_vq; scalar_t__ feature_len; int /*<<< orphan*/ * vq; int /*<<< orphan*/  desc; } ;
struct TYPE_2__ {struct device* lastdev; struct device* dev; } ;

/* Variables and functions */
 TYPE_1__ devices ; 
 struct device* malloc (int) ; 
 int /*<<< orphan*/  new_dev_desc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct device *new_device(const char *name, u16 type)
{
	struct device *dev = malloc(sizeof(*dev));

	/* Now we populate the fields one at a time. */
	dev->desc = new_dev_desc(type);
	dev->name = name;
	dev->vq = NULL;
	dev->feature_len = 0;
	dev->num_vq = 0;
	dev->running = false;

	/*
	 * Append to device list.  Prepending to a single-linked list is
	 * easier, but the user expects the devices to be arranged on the bus
	 * in command-line order.  The first network device on the command line
	 * is eth0, the first block device /dev/vda, etc.
	 */
	if (devices.lastdev)
		devices.lastdev->next = dev;
	else
		devices.dev = dev;
	devices.lastdev = dev;

	return dev;
}