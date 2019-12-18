#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {size_t devType; int /*<<< orphan*/  dmacHwHandle; } ;
struct TYPE_6__ {int /*<<< orphan*/  virtAddr; } ;
struct TYPE_7__ {TYPE_1__ ring; int /*<<< orphan*/  config; } ;
typedef  int /*<<< orphan*/  DMA_Handle_t ;
typedef  TYPE_2__ DMA_DeviceAttribute_t ;
typedef  TYPE_3__ DMA_Channel_t ;

/* Variables and functions */
 TYPE_2__* DMA_gDeviceAttribute ; 
 int ENODEV ; 
 TYPE_3__* HandleToChannel (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dmacHw_initiateTransfer (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int dma_start_transfer(DMA_Handle_t handle)
{
	DMA_Channel_t *channel;
	DMA_DeviceAttribute_t *devAttr;

	channel = HandleToChannel(handle);
	if (channel == NULL) {
		return -ENODEV;
	}
	devAttr = &DMA_gDeviceAttribute[channel->devType];

	dmacHw_initiateTransfer(channel->dmacHwHandle, &devAttr->config,
				devAttr->ring.virtAddr);

	/* Since we got this far, everything went successfully */

	return 0;
}