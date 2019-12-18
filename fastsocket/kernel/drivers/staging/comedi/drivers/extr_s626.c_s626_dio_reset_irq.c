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
struct dio_private {int /*<<< orphan*/  WRCapSel; } ;
struct comedi_device {TYPE_1__* subdevices; } ;
struct TYPE_2__ {scalar_t__ private; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEBIwrite (struct comedi_device*,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  DEBUG (char*,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  LP_MISC1 ; 
 unsigned int MISC1_NOEDCAP ; 

__attribute__((used)) static int s626_dio_reset_irq(struct comedi_device *dev, unsigned int group,
			      unsigned int mask)
{
	DEBUG
	    ("s626_dio_reset_irq: disable  interrupt on dio channel %d group %d\n",
	     mask, group);

	/* disable edge capture write command */
	DEBIwrite(dev, LP_MISC1, MISC1_NOEDCAP);

	/* enable edge capture on selected channel */
	DEBIwrite(dev,
		  ((struct dio_private *)(dev->subdevices + 2 +
					  group)->private)->WRCapSel, mask);

	return 0;
}