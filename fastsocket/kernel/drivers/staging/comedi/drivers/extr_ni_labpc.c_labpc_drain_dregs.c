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
struct comedi_device {int dummy; } ;
struct TYPE_2__ {scalar_t__ current_transfer; } ;

/* Variables and functions */
 TYPE_1__* devpriv ; 
 scalar_t__ isa_dma_transfer ; 
 int /*<<< orphan*/  labpc_drain_dma (struct comedi_device*) ; 
 int /*<<< orphan*/  labpc_drain_fifo (struct comedi_device*) ; 

__attribute__((used)) static void labpc_drain_dregs(struct comedi_device *dev)
{
	if (devpriv->current_transfer == isa_dma_transfer)
		labpc_drain_dma(dev);

	labpc_drain_fifo(dev);
}