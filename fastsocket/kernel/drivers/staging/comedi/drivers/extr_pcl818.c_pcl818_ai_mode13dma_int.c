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
struct comedi_device {int irq; scalar_t__ iobase; } ;
struct TYPE_2__ {unsigned int* hwdmasize; int ai_n_chan; int ai_scans; unsigned int dma_runs_to_end; unsigned int last_dma_run; int /*<<< orphan*/  ai_mode; int /*<<< orphan*/  dma; int /*<<< orphan*/ * hwdmaptr; scalar_t__ next_dma_buf; int /*<<< orphan*/  neverending_ai; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_MODE_READ ; 
 int /*<<< orphan*/  INT_TYPE_AI1_DMA ; 
 int /*<<< orphan*/  INT_TYPE_AI3_DMA ; 
 scalar_t__ PCL818_CONTROL ; 
 unsigned int claim_dma_lock () ; 
 int /*<<< orphan*/  clear_dma_ff (int /*<<< orphan*/ ) ; 
 TYPE_1__* devpriv ; 
 int /*<<< orphan*/  disable_dma (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  enable_dma (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  outb (int,scalar_t__) ; 
 int /*<<< orphan*/  printk (char*,int) ; 
 int /*<<< orphan*/  release_dma_lock (unsigned int) ; 
 int /*<<< orphan*/  set_dma_addr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_dma_count (int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  set_dma_mode (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void pcl818_ai_mode13dma_int(int mode, struct comedi_device *dev,
				    struct comedi_subdevice *s)
{
	unsigned int flags;
	unsigned int bytes;

	printk("mode13dma_int, mode: %d\n", mode);
	disable_dma(devpriv->dma);	/*  disable dma */
	bytes = devpriv->hwdmasize[0];
	if (!devpriv->neverending_ai) {
		bytes = devpriv->ai_n_chan * devpriv->ai_scans * sizeof(short);	/*  how many */
		devpriv->dma_runs_to_end = bytes / devpriv->hwdmasize[0];	/*  how many DMA pages we must fiil */
		devpriv->last_dma_run = bytes % devpriv->hwdmasize[0];	/* on last dma transfer must be moved */
		devpriv->dma_runs_to_end--;
		if (devpriv->dma_runs_to_end >= 0)
			bytes = devpriv->hwdmasize[0];
	}

	devpriv->next_dma_buf = 0;
	set_dma_mode(devpriv->dma, DMA_MODE_READ);
	flags = claim_dma_lock();
	clear_dma_ff(devpriv->dma);
	set_dma_addr(devpriv->dma, devpriv->hwdmaptr[0]);
	set_dma_count(devpriv->dma, bytes);
	release_dma_lock(flags);
	enable_dma(devpriv->dma);

	if (mode == 1) {
		devpriv->ai_mode = INT_TYPE_AI1_DMA;
		outb(0x87 | (dev->irq << 4), dev->iobase + PCL818_CONTROL);	/* Pacer+IRQ+DMA */
	} else {
		devpriv->ai_mode = INT_TYPE_AI3_DMA;
		outb(0x86 | (dev->irq << 4), dev->iobase + PCL818_CONTROL);	/* Ext trig+IRQ+DMA */
	};
}