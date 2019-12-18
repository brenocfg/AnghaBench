#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct r592_device {int dma_error; int /*<<< orphan*/  dummy_dma_page_physical_address; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_IRQ_ACK_MASK ; 
 int /*<<< orphan*/  DMA_IRQ_EN_MASK ; 
 int /*<<< orphan*/  R592_FIFO_DMA ; 
 int /*<<< orphan*/  R592_FIFO_DMA_SETTINGS ; 
 int /*<<< orphan*/  R592_FIFO_DMA_SETTINGS_EN ; 
 int /*<<< orphan*/  R592_REG_MSC ; 
 int /*<<< orphan*/  r592_clear_reg_mask (struct r592_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  r592_write_reg (struct r592_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void r592_stop_dma(struct r592_device *dev, int error)
{
	r592_clear_reg_mask(dev, R592_FIFO_DMA_SETTINGS,
		R592_FIFO_DMA_SETTINGS_EN);

	/* This is only a precation */
	r592_write_reg(dev, R592_FIFO_DMA,
			dev->dummy_dma_page_physical_address);

	r592_clear_reg_mask(dev, R592_REG_MSC, DMA_IRQ_EN_MASK);
	r592_clear_reg_mask(dev, R592_REG_MSC, DMA_IRQ_ACK_MASK);
	dev->dma_error = error;
}