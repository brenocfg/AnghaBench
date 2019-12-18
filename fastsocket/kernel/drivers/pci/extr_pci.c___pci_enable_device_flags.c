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
struct pci_dev {int /*<<< orphan*/  enable_cnt; TYPE_1__* resource; } ;
typedef  int resource_size_t ;
struct TYPE_2__ {int flags; } ;

/* Variables and functions */
 int DEVICE_COUNT_RESOURCE ; 
 int atomic_add_return (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 int do_pci_enable_device (struct pci_dev*,int) ; 

__attribute__((used)) static int __pci_enable_device_flags(struct pci_dev *dev,
				     resource_size_t flags)
{
	int err;
	int i, bars = 0;

	if (atomic_add_return(1, &dev->enable_cnt) > 1)
		return 0;		/* already enabled */

	for (i = 0; i < DEVICE_COUNT_RESOURCE; i++)
		if (dev->resource[i].flags & flags)
			bars |= (1 << i);

	err = do_pci_enable_device(dev, bars);
	if (err < 0)
		atomic_dec(&dev->enable_cnt);
	return err;
}