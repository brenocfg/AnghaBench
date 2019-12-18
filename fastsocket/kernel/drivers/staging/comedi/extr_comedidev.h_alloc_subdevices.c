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
struct comedi_subdevice {int dummy; } ;
struct comedi_device {unsigned int n_subdevices; TYPE_1__* subdevices; } ;
struct TYPE_2__ {int minor; int /*<<< orphan*/  spin_lock; int /*<<< orphan*/  async_dma_dir; struct comedi_device* device; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_NONE ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 TYPE_1__* kcalloc (unsigned int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline int alloc_subdevices(struct comedi_device *dev,
				   unsigned int num_subdevices)
{
	unsigned i;

	dev->n_subdevices = num_subdevices;
	dev->subdevices =
	    kcalloc(num_subdevices, sizeof(struct comedi_subdevice),
		    GFP_KERNEL);
	if (!dev->subdevices)
		return -ENOMEM;
	for (i = 0; i < num_subdevices; ++i) {
		dev->subdevices[i].device = dev;
		dev->subdevices[i].async_dma_dir = DMA_NONE;
		spin_lock_init(&dev->subdevices[i].spin_lock);
		dev->subdevices[i].minor = -1;
	}
	return 0;
}