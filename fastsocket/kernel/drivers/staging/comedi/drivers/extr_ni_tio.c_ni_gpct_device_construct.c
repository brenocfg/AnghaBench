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
struct ni_gpct_device {void (* write_register ) (struct ni_gpct*,unsigned int,int) ;unsigned int (* read_register ) (struct ni_gpct*,int) ;int variant; unsigned int num_counters; TYPE_1__* counters; int /*<<< orphan*/  regs_lock; struct comedi_device* dev; } ;
struct ni_gpct {int dummy; } ;
struct comedi_device {int dummy; } ;
typedef  enum ni_gpct_variant { ____Placeholder_ni_gpct_variant } ni_gpct_variant ;
struct TYPE_2__ {int /*<<< orphan*/  lock; struct ni_gpct_device* counter_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  kfree (struct ni_gpct_device*) ; 
 void* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

struct ni_gpct_device *ni_gpct_device_construct(struct comedi_device *dev,
						void (*write_register) (struct
									ni_gpct
									*
									counter,
									unsigned
									bits,
									enum
									ni_gpct_register
									reg),
						unsigned (*read_register)
						(struct ni_gpct * counter,
						 enum ni_gpct_register reg),
						enum ni_gpct_variant variant,
						unsigned num_counters)
{
	unsigned i;

	struct ni_gpct_device *counter_dev =
	    kzalloc(sizeof(struct ni_gpct_device), GFP_KERNEL);
	if (counter_dev == NULL)
		return NULL;
	counter_dev->dev = dev;
	counter_dev->write_register = write_register;
	counter_dev->read_register = read_register;
	counter_dev->variant = variant;
	spin_lock_init(&counter_dev->regs_lock);
	BUG_ON(num_counters == 0);
	counter_dev->counters =
	    kzalloc(sizeof(struct ni_gpct) * num_counters, GFP_KERNEL);
	if (counter_dev->counters == NULL) {
		kfree(counter_dev);
		return NULL;
	}
	for (i = 0; i < num_counters; ++i) {
		counter_dev->counters[i].counter_dev = counter_dev;
		spin_lock_init(&counter_dev->counters[i].lock);
	}
	counter_dev->num_counters = num_counters;
	return counter_dev;
}