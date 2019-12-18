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
struct pcmcia_device {struct cm4000_dev* priv; } ;
struct cm4000_dev {int dummy; } ;

/* Variables and functions */
 int CM4000_MAX_DEV ; 
 int /*<<< orphan*/  MKDEV (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  cm4000_release (struct pcmcia_device*) ; 
 int /*<<< orphan*/  cmm_class ; 
 struct pcmcia_device** dev_table ; 
 int /*<<< orphan*/  device_destroy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct cm4000_dev*) ; 
 int /*<<< orphan*/  major ; 
 int /*<<< orphan*/  stop_monitor (struct cm4000_dev*) ; 

__attribute__((used)) static void cm4000_detach(struct pcmcia_device *link)
{
	struct cm4000_dev *dev = link->priv;
	int devno;

	/* find device */
	for (devno = 0; devno < CM4000_MAX_DEV; devno++)
		if (dev_table[devno] == link)
			break;
	if (devno == CM4000_MAX_DEV)
		return;

	stop_monitor(dev);

	cm4000_release(link);

	dev_table[devno] = NULL;
	kfree(dev);

	device_destroy(cmm_class, MKDEV(major, devno));

	return;
}