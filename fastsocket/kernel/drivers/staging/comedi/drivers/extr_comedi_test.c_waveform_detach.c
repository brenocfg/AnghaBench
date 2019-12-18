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
struct comedi_device {int /*<<< orphan*/  read_subdev; scalar_t__ private; int /*<<< orphan*/  minor; } ;

/* Variables and functions */
 int /*<<< orphan*/  printk (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  waveform_ai_cancel (struct comedi_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int waveform_detach(struct comedi_device *dev)
{
	printk("comedi%d: comedi_test: remove\n", dev->minor);

	if (dev->private)
		waveform_ai_cancel(dev, dev->read_subdev);

	return 0;
}