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
struct ni_gpct {int /*<<< orphan*/  lock; TYPE_2__* mite_chan; TYPE_1__* counter_dev; } ;
struct TYPE_4__ {int /*<<< orphan*/  dir; } ;
struct TYPE_3__ {int variant; } ;

/* Variables and functions */
 int /*<<< orphan*/  COMEDI_INPUT ; 
 int /*<<< orphan*/  mite_done (TYPE_2__*) ; 
#define  ni_gpct_variant_660x 130 
#define  ni_gpct_variant_e_series 129 
#define  ni_gpct_variant_m_series 128 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int should_ack_gate(struct ni_gpct *counter)
{
	unsigned long flags;
	int retval = 0;

	switch (counter->counter_dev->variant) {
	case ni_gpct_variant_m_series:
	case ni_gpct_variant_660x:	/*  not sure if 660x really supports gate interrupts (the bits are not listed in register-level manual) */
		return 1;
		break;
	case ni_gpct_variant_e_series:
		spin_lock_irqsave(&counter->lock, flags);
		{
			if (counter->mite_chan == NULL ||
			    counter->mite_chan->dir != COMEDI_INPUT ||
			    (mite_done(counter->mite_chan))) {
				retval = 1;
			}
		}
		spin_unlock_irqrestore(&counter->lock, flags);
		break;
	}
	return retval;
}