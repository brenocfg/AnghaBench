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
struct TYPE_3__ {scalar_t__ prevNumBytes; scalar_t__ prevDstData; scalar_t__ prevSrcData; int /*<<< orphan*/  ring; } ;
typedef  size_t DMA_Device_t ;
typedef  TYPE_1__ DMA_DeviceAttribute_t ;
typedef  int /*<<< orphan*/  DMA_DescriptorRing_t ;

/* Variables and functions */
 TYPE_1__* DMA_gDeviceAttribute ; 
 int ENODEV ; 
 int /*<<< orphan*/  IsDeviceValid (size_t) ; 
 int /*<<< orphan*/  dma_free_descriptor_ring (int /*<<< orphan*/ *) ; 

int dma_set_device_descriptor_ring(DMA_Device_t device,	/* Device to update the descriptor ring for. */
				   DMA_DescriptorRing_t *ring	/* Descriptor ring to add descriptors to */
    ) {
	DMA_DeviceAttribute_t *devAttr;

	if (!IsDeviceValid(device)) {
		return -ENODEV;
	}
	devAttr = &DMA_gDeviceAttribute[device];

	/* Free the previously allocated descriptor ring */

	dma_free_descriptor_ring(&devAttr->ring);

	if (ring != NULL) {
		/* Copy in the new one */

		devAttr->ring = *ring;
	}

	/* Set things up so that if dma_transfer is called then this descriptor */
	/* ring will get freed. */

	devAttr->prevSrcData = 0;
	devAttr->prevDstData = 0;
	devAttr->prevNumBytes = 0;

	return 0;
}