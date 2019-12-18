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
struct TYPE_3__ {int /*<<< orphan*/  ring; } ;
typedef  size_t DMA_Device_t ;
typedef  TYPE_1__ DMA_DeviceAttribute_t ;
typedef  int /*<<< orphan*/  DMA_DescriptorRing_t ;

/* Variables and functions */
 TYPE_1__* DMA_gDeviceAttribute ; 
 int ENODEV ; 
 int /*<<< orphan*/  IsDeviceValid (size_t) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

int dma_get_device_descriptor_ring(DMA_Device_t device,	/* Device to retrieve the descriptor ring for. */
				   DMA_DescriptorRing_t *ring	/* Place to store retrieved ring */
    ) {
	DMA_DeviceAttribute_t *devAttr;

	memset(ring, 0, sizeof(*ring));

	if (!IsDeviceValid(device)) {
		return -ENODEV;
	}
	devAttr = &DMA_gDeviceAttribute[device];

	*ring = devAttr->ring;

	return 0;
}