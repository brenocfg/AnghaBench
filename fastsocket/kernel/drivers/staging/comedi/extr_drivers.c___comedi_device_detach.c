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
struct comedi_device {TYPE_1__* driver; scalar_t__ attached; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* detach ) (struct comedi_device*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  cleanup_device (struct comedi_device*) ; 
 int /*<<< orphan*/  printk (char*) ; 
 int /*<<< orphan*/  stub1 (struct comedi_device*) ; 

__attribute__((used)) static void __comedi_device_detach(struct comedi_device *dev)
{
	dev->attached = 0;
	if (dev->driver) {
		dev->driver->detach(dev);
	} else {
		printk("BUG: dev->driver=NULL in comedi_device_detach()\n");
	}
	cleanup_device(dev);
}