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
struct comedi_device {scalar_t__ private; scalar_t__ irq; } ;
struct TYPE_2__ {scalar_t__ mite; int /*<<< orphan*/ * gpct_mite_ring; int /*<<< orphan*/  cdo_mite_ring; int /*<<< orphan*/  ao_mite_ring; int /*<<< orphan*/  ai_mite_ring; } ;

/* Variables and functions */
 TYPE_1__* devpriv ; 
 int /*<<< orphan*/  free_irq (scalar_t__,struct comedi_device*) ; 
 int /*<<< orphan*/  mio_common_detach (struct comedi_device*) ; 
 int /*<<< orphan*/  mite_free_ring (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mite_unsetup (scalar_t__) ; 

__attribute__((used)) static int pcimio_detach(struct comedi_device *dev)
{
	mio_common_detach(dev);
	if (dev->irq) {
		free_irq(dev->irq, dev);
	}
	if (dev->private) {
		mite_free_ring(devpriv->ai_mite_ring);
		mite_free_ring(devpriv->ao_mite_ring);
		mite_free_ring(devpriv->cdo_mite_ring);
		mite_free_ring(devpriv->gpct_mite_ring[0]);
		mite_free_ring(devpriv->gpct_mite_ring[1]);
		if (devpriv->mite)
			mite_unsetup(devpriv->mite);
	}

	return 0;
}