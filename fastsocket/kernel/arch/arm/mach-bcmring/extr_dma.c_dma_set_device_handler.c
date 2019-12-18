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
struct TYPE_3__ {int /*<<< orphan*/  devHandler; void* userData; } ;
typedef  size_t DMA_Device_t ;
typedef  int /*<<< orphan*/  DMA_DeviceHandler_t ;
typedef  TYPE_1__ DMA_DeviceAttribute_t ;

/* Variables and functions */
 TYPE_1__* DMA_gDeviceAttribute ; 
 int ENODEV ; 
 int /*<<< orphan*/  IsDeviceValid (size_t) ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 

int dma_set_device_handler(DMA_Device_t dev,	/* Device to set the callback for. */
			   DMA_DeviceHandler_t devHandler,	/* Function to call when the DMA completes */
			   void *userData	/* Pointer which will be passed to devHandler. */
    ) {
	DMA_DeviceAttribute_t *devAttr;
	unsigned long flags;

	if (!IsDeviceValid(dev)) {
		return -ENODEV;
	}
	devAttr = &DMA_gDeviceAttribute[dev];

	local_irq_save(flags);

	devAttr->userData = userData;
	devAttr->devHandler = devHandler;

	local_irq_restore(flags);

	return 0;
}