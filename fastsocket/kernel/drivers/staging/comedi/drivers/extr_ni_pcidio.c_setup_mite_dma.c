#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct comedi_subdevice {int dummy; } ;
struct comedi_device {int dummy; } ;
struct TYPE_5__ {TYPE_1__* di_mite_chan; } ;
struct TYPE_4__ {int /*<<< orphan*/  dir; } ;

/* Variables and functions */
 int /*<<< orphan*/  COMEDI_INPUT ; 
 TYPE_3__* devpriv ; 
 int /*<<< orphan*/  mite_dma_arm (TYPE_1__*) ; 
 int /*<<< orphan*/  mite_prep_dma (TYPE_1__*,int,int) ; 
 int ni_pcidio_request_di_mite_channel (struct comedi_device*) ; 

__attribute__((used)) static int setup_mite_dma(struct comedi_device *dev, struct comedi_subdevice *s)
{
	int retval;

	retval = ni_pcidio_request_di_mite_channel(dev);
	if (retval)
		return retval;

	devpriv->di_mite_chan->dir = COMEDI_INPUT;

	mite_prep_dma(devpriv->di_mite_chan, 32, 32);

	mite_dma_arm(devpriv->di_mite_chan);
	return 0;
}