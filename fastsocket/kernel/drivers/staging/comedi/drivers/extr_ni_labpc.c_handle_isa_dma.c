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
struct comedi_device {scalar_t__ iobase; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* write_byte ) (int,scalar_t__) ;int /*<<< orphan*/  dma_chan; } ;

/* Variables and functions */
 scalar_t__ DMATC_CLEAR_REG ; 
 TYPE_1__* devpriv ; 
 int /*<<< orphan*/  enable_dma (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  labpc_drain_dma (struct comedi_device*) ; 
 int /*<<< orphan*/  stub1 (int,scalar_t__) ; 

__attribute__((used)) static void handle_isa_dma(struct comedi_device *dev)
{
	labpc_drain_dma(dev);

	enable_dma(devpriv->dma_chan);

	/*  clear dma tc interrupt */
	devpriv->write_byte(0x1, dev->iobase + DMATC_CLEAR_REG);
}