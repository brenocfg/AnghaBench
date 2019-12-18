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
struct ni_660x_private {int dummy; } ;
struct comedi_device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/ * pfi_output_selects; int /*<<< orphan*/  soft_reg_copy_lock; int /*<<< orphan*/  interrupt_lock; int /*<<< orphan*/  mite_channel_lock; } ;

/* Variables and functions */
 unsigned int NUM_PFI_CHANNELS ; 
 int alloc_private (struct comedi_device*,int) ; 
 int /*<<< orphan*/  pfi_output_select_counter ; 
 TYPE_1__* private (struct comedi_device*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ni_660x_allocate_private(struct comedi_device *dev)
{
	int retval;
	unsigned i;

	retval = alloc_private(dev, sizeof(struct ni_660x_private));
	if (retval < 0)
		return retval;

	spin_lock_init(&private(dev)->mite_channel_lock);
	spin_lock_init(&private(dev)->interrupt_lock);
	spin_lock_init(&private(dev)->soft_reg_copy_lock);
	for (i = 0; i < NUM_PFI_CHANNELS; ++i) {
		private(dev)->pfi_output_selects[i] = pfi_output_select_counter;
	}
	return 0;
}