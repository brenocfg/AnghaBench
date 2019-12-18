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
struct comedi_device {int /*<<< orphan*/  attached; } ;

/* Variables and functions */
 int /*<<< orphan*/  __comedi_device_detach (struct comedi_device*) ; 

void comedi_device_detach(struct comedi_device *dev)
{
	if (!dev->attached)
		return;
	__comedi_device_detach(dev);
}