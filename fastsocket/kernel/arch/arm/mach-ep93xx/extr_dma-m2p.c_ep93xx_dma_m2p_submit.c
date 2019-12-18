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
typedef  int /*<<< orphan*/  u32 ;
struct m2p_channel {int /*<<< orphan*/  lock; int /*<<< orphan*/  buffers_pending; struct ep93xx_dma_buffer* buffer_next; struct ep93xx_dma_buffer* buffer_xfer; scalar_t__ base; } ;
struct ep93xx_dma_m2p_client {int /*<<< orphan*/  cookie; int /*<<< orphan*/  (* buffer_started ) (int /*<<< orphan*/ ,struct ep93xx_dma_buffer*) ;struct m2p_channel* channel; } ;
struct ep93xx_dma_buffer {int /*<<< orphan*/  list; } ;

/* Variables and functions */
 scalar_t__ M2P_CONTROL ; 
 int /*<<< orphan*/  M2P_CONTROL_NFB_IRQ_EN ; 
 int /*<<< orphan*/  M2P_CONTROL_STALL_IRQ_EN ; 
 int /*<<< orphan*/  feed_buf (struct m2p_channel*,struct ep93xx_dma_buffer*) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  m2p_set_control (struct m2p_channel*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  readl (scalar_t__) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,struct ep93xx_dma_buffer*) ; 

void ep93xx_dma_m2p_submit(struct ep93xx_dma_m2p_client *cl,
			   struct ep93xx_dma_buffer *buf)
{
	struct m2p_channel *ch = cl->channel;
	unsigned long flags;
	u32 v;

	spin_lock_irqsave(&ch->lock, flags);
	v = readl(ch->base + M2P_CONTROL);
	if (ch->buffer_xfer == NULL) {
		ch->buffer_xfer = buf;
		feed_buf(ch, buf);
		cl->buffer_started(cl->cookie, buf);

		v |= M2P_CONTROL_STALL_IRQ_EN;
		m2p_set_control(ch, v);

	} else if (ch->buffer_next == NULL) {
		ch->buffer_next = buf;
		feed_buf(ch, buf);

		v |= M2P_CONTROL_NFB_IRQ_EN;
		m2p_set_control(ch, v);
	} else {
		list_add_tail(&buf->list, &ch->buffers_pending);
	}
	spin_unlock_irqrestore(&ch->lock, flags);
}