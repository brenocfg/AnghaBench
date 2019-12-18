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
struct comedi_cmd {int dummy; } ;
struct TYPE_2__ {int irq_dma_bits; int /*<<< orphan*/  dma1; int /*<<< orphan*/  dma_transfer_size; int /*<<< orphan*/  ai_buf1; int /*<<< orphan*/  dma0; int /*<<< orphan*/  ai_buf0; int /*<<< orphan*/  dma_current_buf; int /*<<< orphan*/  dma_current; } ;

/* Variables and functions */
 int DMA_DUAL ; 
 int DMA_ENABLED ; 
 unsigned long claim_dma_lock () ; 
 int /*<<< orphan*/  clear_dma_ff (int /*<<< orphan*/ ) ; 
 TYPE_1__* devpriv ; 
 int /*<<< orphan*/  disable_dma (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  enable_dma (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  release_dma_lock (unsigned long) ; 
 int /*<<< orphan*/  set_dma_addr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_dma_count (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  suggest_transfer_size (struct comedi_cmd*) ; 
 int /*<<< orphan*/  virt_to_bus (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void setup_dma(struct comedi_device *dev, struct comedi_cmd cmd)
{
	unsigned long lock_flags;
	const int dual_dma = devpriv->irq_dma_bits & DMA_DUAL;

	if ((devpriv->irq_dma_bits & DMA_ENABLED) == 0)
		return;

	/* determine a reasonable dma transfer size */
	devpriv->dma_transfer_size = suggest_transfer_size(&cmd);
	lock_flags = claim_dma_lock();
	disable_dma(devpriv->dma0);
	/* clear flip-flop to make sure 2-byte registers for
	 * count and address get set correctly */
	clear_dma_ff(devpriv->dma0);
	set_dma_addr(devpriv->dma0, virt_to_bus(devpriv->ai_buf0));
	/*  set appropriate size of transfer */
	set_dma_count(devpriv->dma0, devpriv->dma_transfer_size);
	devpriv->dma_current = devpriv->dma0;
	devpriv->dma_current_buf = devpriv->ai_buf0;
	enable_dma(devpriv->dma0);
	/*  set up dual dma if appropriate */
	if (dual_dma) {
		disable_dma(devpriv->dma1);
		/* clear flip-flop to make sure 2-byte registers for
		 * count and address get set correctly */
		clear_dma_ff(devpriv->dma1);
		set_dma_addr(devpriv->dma1, virt_to_bus(devpriv->ai_buf1));
		/*  set appropriate size of transfer */
		set_dma_count(devpriv->dma1, devpriv->dma_transfer_size);
		enable_dma(devpriv->dma1);
	}
	release_dma_lock(lock_flags);

	return;
}