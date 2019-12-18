#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct musb_dma_channel {int idx; TYPE_1__* controller; scalar_t__ len; scalar_t__ start_addr; } ;
struct dma_channel {int /*<<< orphan*/  status; scalar_t__ actual_len; struct musb_dma_channel* private_data; } ;
struct TYPE_2__ {int used_channels; } ;

/* Variables and functions */
 int /*<<< orphan*/  MUSB_DMA_STATUS_UNKNOWN ; 

__attribute__((used)) static void dma_channel_release(struct dma_channel *channel)
{
	struct musb_dma_channel *musb_channel = channel->private_data;

	channel->actual_len = 0;
	musb_channel->start_addr = 0;
	musb_channel->len = 0;

	musb_channel->controller->used_channels &=
		~(1 << musb_channel->idx);

	channel->status = MUSB_DMA_STATUS_UNKNOWN;
}