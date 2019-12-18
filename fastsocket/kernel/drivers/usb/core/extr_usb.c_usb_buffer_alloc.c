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
struct usb_device {int /*<<< orphan*/  bus; } ;
typedef  int /*<<< orphan*/  gfp_t ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 void* hcd_buffer_alloc (int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void *usb_buffer_alloc(struct usb_device *dev, size_t size, gfp_t mem_flags,
		       dma_addr_t *dma)
{
	if (!dev || !dev->bus)
		return NULL;
	return hcd_buffer_alloc(dev->bus, size, mem_flags, dma);
}