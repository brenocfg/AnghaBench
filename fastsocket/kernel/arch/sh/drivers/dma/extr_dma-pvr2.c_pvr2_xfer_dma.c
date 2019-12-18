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
struct dma_channel {int dar; int count; int mode; scalar_t__ sar; } ;

/* Variables and functions */
 int DMA_MODE_MASK ; 
 int EINVAL ; 
 int /*<<< orphan*/  PVR2_DMA_ADDR ; 
 int /*<<< orphan*/  PVR2_DMA_COUNT ; 
 int /*<<< orphan*/  PVR2_DMA_MODE ; 
 int /*<<< orphan*/  ctrl_outl (int,int /*<<< orphan*/ ) ; 
 scalar_t__ xfer_complete ; 

__attribute__((used)) static int pvr2_xfer_dma(struct dma_channel *chan)
{
	if (chan->sar || !chan->dar)
		return -EINVAL;

	xfer_complete = 0;

	ctrl_outl(chan->dar, PVR2_DMA_ADDR);
	ctrl_outl(chan->count, PVR2_DMA_COUNT);
	ctrl_outl(chan->mode & DMA_MODE_MASK, PVR2_DMA_MODE);

	return 0;
}