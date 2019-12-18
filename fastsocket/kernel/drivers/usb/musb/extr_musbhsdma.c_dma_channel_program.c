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
typedef  int u8 ;
typedef  void* u32 ;
typedef  void* u16 ;
struct musb_dma_channel {void* max_packet_sz; void* len; int /*<<< orphan*/  start_addr; scalar_t__ transmit; int /*<<< orphan*/  epnum; } ;
struct dma_channel {scalar_t__ status; scalar_t__ actual_len; struct musb_dma_channel* private_data; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  DBG (int,char*,int /*<<< orphan*/ ,char*,void*,int /*<<< orphan*/ ,void*,int) ; 
 scalar_t__ MUSB_DMA_STATUS_BUSY ; 
 scalar_t__ MUSB_DMA_STATUS_UNKNOWN ; 
 int /*<<< orphan*/  configure_channel (struct dma_channel*,void*,int,int /*<<< orphan*/ ,void*) ; 

__attribute__((used)) static int dma_channel_program(struct dma_channel *channel,
				u16 packet_sz, u8 mode,
				dma_addr_t dma_addr, u32 len)
{
	struct musb_dma_channel *musb_channel = channel->private_data;

	DBG(2, "ep%d-%s pkt_sz %d, dma_addr 0x%x length %d, mode %d\n",
		musb_channel->epnum,
		musb_channel->transmit ? "Tx" : "Rx",
		packet_sz, dma_addr, len, mode);

	BUG_ON(channel->status == MUSB_DMA_STATUS_UNKNOWN ||
		channel->status == MUSB_DMA_STATUS_BUSY);

	channel->actual_len = 0;
	musb_channel->start_addr = dma_addr;
	musb_channel->len = len;
	musb_channel->max_packet_sz = packet_sz;
	channel->status = MUSB_DMA_STATUS_BUSY;

	if ((mode == 1) && (len >= packet_sz))
		configure_channel(channel, packet_sz, 1, dma_addr, len);
	else
		configure_channel(channel, packet_sz, 0, dma_addr, len);

	return true;
}