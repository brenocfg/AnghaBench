#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ dmacHw_TRANSFER_TYPE_e ;
typedef  int /*<<< orphan*/  dma_addr_t ;
struct TYPE_10__ {scalar_t__ transferType; } ;
struct TYPE_9__ {size_t devType; int /*<<< orphan*/  dmacHwHandle; } ;
struct TYPE_7__ {int /*<<< orphan*/  virtAddr; } ;
struct TYPE_8__ {size_t numBytes; TYPE_1__ ring; TYPE_4__ config; int /*<<< orphan*/  transferStartTime; } ;
typedef  int /*<<< orphan*/  DMA_Handle_t ;
typedef  TYPE_2__ DMA_DeviceAttribute_t ;
typedef  TYPE_3__ DMA_Channel_t ;

/* Variables and functions */
 TYPE_2__* DMA_gDeviceAttribute ; 
 int EINVAL ; 
 int ENODEV ; 
 TYPE_3__* HandleToChannel (int /*<<< orphan*/ ) ; 
 int dma_alloc_descriptors (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  dmacHw_initiateTransfer (int /*<<< orphan*/ ,TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  timer_get_tick_count () ; 

int dma_transfer(DMA_Handle_t handle,	/* DMA Handle */
		 dmacHw_TRANSFER_TYPE_e transferType,	/* Type of transfer being performed */
		 dma_addr_t srcData,	/* Place to get data to write to device */
		 dma_addr_t dstData,	/* Pointer to device data address */
		 size_t numBytes	/* Number of bytes to transfer to the device */
    ) {
	DMA_Channel_t *channel;
	DMA_DeviceAttribute_t *devAttr;
	int rc = 0;

	channel = HandleToChannel(handle);
	if (channel == NULL) {
		return -ENODEV;
	}

	devAttr = &DMA_gDeviceAttribute[channel->devType];

	if (devAttr->config.transferType != transferType) {
		return -EINVAL;
	}

	/* We keep track of the information about the previous request for this */
	/* device, and if the attributes match, then we can use the descriptors we setup */
	/* the last time, and not have to reinitialize everything. */

	{
		rc =
		     dma_alloc_descriptors(handle, transferType, srcData,
					   dstData, numBytes);
		if (rc != 0) {
			return rc;
		}
	}

	/* And kick off the transfer */

	devAttr->numBytes = numBytes;
	devAttr->transferStartTime = timer_get_tick_count();

	dmacHw_initiateTransfer(channel->dmacHwHandle, &devAttr->config,
				devAttr->ring.virtAddr);

	/* Since we got this far, everything went successfully */

	return 0;
}