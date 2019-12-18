#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct ni_gpct {TYPE_1__* mite_chan; } ;
struct comedi_async {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  dir; } ;

/* Variables and functions */
 int /*<<< orphan*/  COMEDI_OUTPUT ; 
 int ENOTSUPP ; 
 int /*<<< orphan*/  NI_GPCT_ARM_IMMEDIATE ; 
 int /*<<< orphan*/  mite_dma_arm (TYPE_1__*) ; 
 int /*<<< orphan*/  mite_prep_dma (TYPE_1__*,int,int) ; 
 int ni_tio_arm (struct ni_gpct*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ni_tio_configure_dma (struct ni_gpct*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printk (char*) ; 

__attribute__((used)) static int ni_tio_output_cmd(struct ni_gpct *counter,
			     struct comedi_async *async)
{
	printk("ni_tio: output commands not yet implemented.\n");
	return -ENOTSUPP;

	counter->mite_chan->dir = COMEDI_OUTPUT;
	mite_prep_dma(counter->mite_chan, 32, 32);
	ni_tio_configure_dma(counter, 1, 0);
	mite_dma_arm(counter->mite_chan);
	return ni_tio_arm(counter, 1, NI_GPCT_ARM_IMMEDIATE);
}