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
struct usb_device {struct usb_bus* bus; } ;
struct usb_bus {struct device* controller; } ;
struct scatterlist {int dummy; } ;
struct device {int /*<<< orphan*/  dma_mask; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 int /*<<< orphan*/  dma_unmap_sg (struct device*,struct scatterlist*,int,int /*<<< orphan*/ ) ; 

void usb_buffer_unmap_sg(const struct usb_device *dev, int is_in,
			 struct scatterlist *sg, int n_hw_ents)
{
	struct usb_bus		*bus;
	struct device		*controller;

	if (!dev
			|| !(bus = dev->bus)
			|| !(controller = bus->controller)
			|| !controller->dma_mask)
		return;

	dma_unmap_sg(controller, sg, n_hw_ents,
			is_in ? DMA_FROM_DEVICE : DMA_TO_DEVICE);
}