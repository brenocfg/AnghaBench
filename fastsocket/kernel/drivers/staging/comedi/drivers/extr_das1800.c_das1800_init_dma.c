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
struct comedi_device {scalar_t__ irq; } ;
struct TYPE_4__ {unsigned int dma0; unsigned int dma_current; unsigned int dma1; int /*<<< orphan*/ * ai_buf1; int /*<<< orphan*/ * ai_buf0; int /*<<< orphan*/ * dma_current_buf; int /*<<< orphan*/  dma_bits; } ;
struct TYPE_3__ {int /*<<< orphan*/  driver_name; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_BUF_SIZE ; 
 int /*<<< orphan*/  DMA_CH5 ; 
 int /*<<< orphan*/  DMA_CH5_CH6 ; 
 int /*<<< orphan*/  DMA_CH6 ; 
 int /*<<< orphan*/  DMA_CH6_CH7 ; 
 int /*<<< orphan*/  DMA_CH7 ; 
 int /*<<< orphan*/  DMA_CH7_CH5 ; 
 int /*<<< orphan*/  DMA_MODE_READ ; 
 int EINVAL ; 
 int ENOMEM ; 
 int GFP_DMA ; 
 int GFP_KERNEL ; 
 unsigned long claim_dma_lock () ; 
 TYPE_2__* devpriv ; 
 int /*<<< orphan*/  disable_dma (unsigned int) ; 
 TYPE_1__ driver_das1800 ; 
 void* kmalloc (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  printk (char*,...) ; 
 int /*<<< orphan*/  release_dma_lock (unsigned long) ; 
 scalar_t__ request_dma (unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_dma_mode (unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int das1800_init_dma(struct comedi_device *dev, unsigned int dma0,
			    unsigned int dma1)
{
	unsigned long flags;

	/*  need an irq to do dma */
	if (dev->irq && dma0) {
		/* encode dma0 and dma1 into 2 digit hexadecimal for switch */
		switch ((dma0 & 0x7) | (dma1 << 4)) {
		case 0x5:	/*  dma0 == 5 */
			devpriv->dma_bits |= DMA_CH5;
			break;
		case 0x6:	/*  dma0 == 6 */
			devpriv->dma_bits |= DMA_CH6;
			break;
		case 0x7:	/*  dma0 == 7 */
			devpriv->dma_bits |= DMA_CH7;
			break;
		case 0x65:	/*  dma0 == 5, dma1 == 6 */
			devpriv->dma_bits |= DMA_CH5_CH6;
			break;
		case 0x76:	/*  dma0 == 6, dma1 == 7 */
			devpriv->dma_bits |= DMA_CH6_CH7;
			break;
		case 0x57:	/*  dma0 == 7, dma1 == 5 */
			devpriv->dma_bits |= DMA_CH7_CH5;
			break;
		default:
			printk(" only supports dma channels 5 through 7\n"
			       " Dual dma only allows the following combinations:\n"
			       " dma 5,6 / 6,7 / or 7,5\n");
			return -EINVAL;
			break;
		}
		if (request_dma(dma0, driver_das1800.driver_name)) {
			printk(" failed to allocate dma channel %i\n", dma0);
			return -EINVAL;
		}
		devpriv->dma0 = dma0;
		devpriv->dma_current = dma0;
		if (dma1) {
			if (request_dma(dma1, driver_das1800.driver_name)) {
				printk(" failed to allocate dma channel %i\n",
				       dma1);
				return -EINVAL;
			}
			devpriv->dma1 = dma1;
		}
		devpriv->ai_buf0 = kmalloc(DMA_BUF_SIZE, GFP_KERNEL | GFP_DMA);
		if (devpriv->ai_buf0 == NULL)
			return -ENOMEM;
		devpriv->dma_current_buf = devpriv->ai_buf0;
		if (dma1) {
			devpriv->ai_buf1 =
			    kmalloc(DMA_BUF_SIZE, GFP_KERNEL | GFP_DMA);
			if (devpriv->ai_buf1 == NULL)
				return -ENOMEM;
		}
		flags = claim_dma_lock();
		disable_dma(devpriv->dma0);
		set_dma_mode(devpriv->dma0, DMA_MODE_READ);
		if (dma1) {
			disable_dma(devpriv->dma1);
			set_dma_mode(devpriv->dma1, DMA_MODE_READ);
		}
		release_dma_lock(flags);
	}
	return 0;
}