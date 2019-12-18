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
struct dio_private {int /*<<< orphan*/  WRCapSel; int /*<<< orphan*/  RDCapSel; int /*<<< orphan*/  WRIntSel; int /*<<< orphan*/  RDIntSel; int /*<<< orphan*/  WREdgSel; int /*<<< orphan*/  RDEdgSel; } ;
struct comedi_device {TYPE_1__* subdevices; } ;
struct TYPE_2__ {scalar_t__ private; } ;

/* Variables and functions */
 unsigned int DEBIread (struct comedi_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DEBIwrite (struct comedi_device*,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  DEBUG (char*,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  LP_MISC1 ; 
 unsigned int MISC1_EDCAP ; 

__attribute__((used)) static int s626_dio_set_irq(struct comedi_device *dev, unsigned int chan)
{
	unsigned int group;
	unsigned int bitmask;
	unsigned int status;

	/* select dio bank */
	group = chan / 16;
	bitmask = 1 << (chan - (16 * group));
	DEBUG("s626_dio_set_irq: enable interrupt on dio channel %d group %d\n",
	      chan - (16 * group), group);

	/* set channel to capture positive edge */
	status = DEBIread(dev,
			  ((struct dio_private *)(dev->subdevices + 2 +
						  group)->private)->RDEdgSel);
	DEBIwrite(dev,
		  ((struct dio_private *)(dev->subdevices + 2 +
					  group)->private)->WREdgSel,
		  bitmask | status);

	/* enable interrupt on selected channel */
	status = DEBIread(dev,
			  ((struct dio_private *)(dev->subdevices + 2 +
						  group)->private)->RDIntSel);
	DEBIwrite(dev,
		  ((struct dio_private *)(dev->subdevices + 2 +
					  group)->private)->WRIntSel,
		  bitmask | status);

	/* enable edge capture write command */
	DEBIwrite(dev, LP_MISC1, MISC1_EDCAP);

	/* enable edge capture on selected channel */
	status = DEBIread(dev,
			  ((struct dio_private *)(dev->subdevices + 2 +
						  group)->private)->RDCapSel);
	DEBIwrite(dev,
		  ((struct dio_private *)(dev->subdevices + 2 +
					  group)->private)->WRCapSel,
		  bitmask | status);

	return 0;
}