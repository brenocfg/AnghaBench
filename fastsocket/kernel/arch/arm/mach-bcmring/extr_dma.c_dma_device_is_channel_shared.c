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
struct TYPE_3__ {int flags; } ;
typedef  size_t DMA_Device_t ;
typedef  TYPE_1__ DMA_DeviceAttribute_t ;

/* Variables and functions */
 int DMA_DEVICE_FLAG_IS_DEDICATED ; 
 TYPE_1__* DMA_gDeviceAttribute ; 
 int ENODEV ; 
 int /*<<< orphan*/  IsDeviceValid (size_t) ; 

int dma_device_is_channel_shared(DMA_Device_t device	/* Device to check. */
    ) {
	DMA_DeviceAttribute_t *devAttr;

	if (!IsDeviceValid(device)) {
		return -ENODEV;
	}
	devAttr = &DMA_gDeviceAttribute[device];

	return ((devAttr->flags & DMA_DEVICE_FLAG_IS_DEDICATED) == 0);
}