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
struct m2p_channel {int /*<<< orphan*/  buffers_pending; int /*<<< orphan*/ * buffer_next; int /*<<< orphan*/ * buffer_xfer; scalar_t__ next_slot; struct ep93xx_dma_m2p_client* client; int /*<<< orphan*/  irq; } ;
struct ep93xx_dma_m2p_client {struct m2p_channel* channel; scalar_t__ name; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 scalar_t__ IS_ERR (struct m2p_channel*) ; 
 int PTR_ERR (struct m2p_channel*) ; 
 int /*<<< orphan*/  channel_enable (struct m2p_channel*) ; 
 struct m2p_channel* find_free_channel (struct ep93xx_dma_m2p_client*) ; 
 int /*<<< orphan*/  m2p_irq ; 
 int request_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,struct m2p_channel*) ; 

int ep93xx_dma_m2p_client_register(struct ep93xx_dma_m2p_client *cl)
{
	struct m2p_channel *ch;
	int err;

	ch = find_free_channel(cl);
	if (IS_ERR(ch))
		return PTR_ERR(ch);

	err = request_irq(ch->irq, m2p_irq, 0, cl->name ? : "dma-m2p", ch);
	if (err)
		return err;

	ch->client = cl;
	ch->next_slot = 0;
	ch->buffer_xfer = NULL;
	ch->buffer_next = NULL;
	INIT_LIST_HEAD(&ch->buffers_pending);

	cl->channel = ch;

	channel_enable(ch);

	return 0;
}