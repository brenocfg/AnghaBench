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
struct poll_delay_t {int min; int max; } ;
struct jr3_pci_subdev_private {unsigned long next_time_min; void* next_time_max; } ;
struct TYPE_4__ {void* expires; } ;
struct jr3_pci_dev_private {int n_channels; TYPE_2__ timer; } ;
struct comedi_device {int /*<<< orphan*/  spinlock; TYPE_1__* subdevices; struct jr3_pci_dev_private* private; } ;
struct TYPE_3__ {struct jr3_pci_subdev_private* private; } ;

/* Variables and functions */
 int /*<<< orphan*/  add_timer (TYPE_2__*) ; 
 unsigned long jiffies ; 
 struct poll_delay_t jr3_pci_poll_subdevice (TYPE_1__*) ; 
 void* msecs_to_jiffies (int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void jr3_pci_poll_dev(unsigned long data)
{
	unsigned long flags;
	struct comedi_device *dev = (struct comedi_device *)data;
	struct jr3_pci_dev_private *devpriv = dev->private;
	unsigned long now;
	int delay;
	int i;

	spin_lock_irqsave(&dev->spinlock, flags);
	delay = 1000;
	now = jiffies;
	/*  Poll all channels that are ready to be polled */
	for (i = 0; i < devpriv->n_channels; i++) {
		struct jr3_pci_subdev_private *subdevpriv =
		    dev->subdevices[i].private;
		if (now > subdevpriv->next_time_min) {
			struct poll_delay_t sub_delay;

			sub_delay = jr3_pci_poll_subdevice(&dev->subdevices[i]);
			subdevpriv->next_time_min =
			    jiffies + msecs_to_jiffies(sub_delay.min);
			subdevpriv->next_time_max =
			    jiffies + msecs_to_jiffies(sub_delay.max);
			if (sub_delay.max && sub_delay.max < delay) {
/*
* Wake up as late as possible -> poll as many channels as possible
* at once
*/
				delay = sub_delay.max;
			}
		}
	}
	spin_unlock_irqrestore(&dev->spinlock, flags);

	devpriv->timer.expires = jiffies + msecs_to_jiffies(delay);
	add_timer(&devpriv->timer);
}