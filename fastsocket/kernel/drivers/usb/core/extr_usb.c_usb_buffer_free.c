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
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  hcd_buffer_free (int /*<<< orphan*/ ,size_t,void*,int /*<<< orphan*/ ) ; 

void usb_buffer_free(struct usb_device *dev, size_t size, void *addr,
		     dma_addr_t dma)
{
	if (!dev || !dev->bus)
		return;
	if (!addr)
		return;
	hcd_buffer_free(dev->bus, size, addr, dma);
}