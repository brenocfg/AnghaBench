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
struct m2p_channel {int /*<<< orphan*/  buffers_pending; } ;
struct ep93xx_dma_m2p_client {struct m2p_channel* channel; } ;
struct ep93xx_dma_buffer {int /*<<< orphan*/  list; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void ep93xx_dma_m2p_submit_recursive(struct ep93xx_dma_m2p_client *cl,
				     struct ep93xx_dma_buffer *buf)
{
	struct m2p_channel *ch = cl->channel;

	list_add_tail(&buf->list, &ch->buffers_pending);
}