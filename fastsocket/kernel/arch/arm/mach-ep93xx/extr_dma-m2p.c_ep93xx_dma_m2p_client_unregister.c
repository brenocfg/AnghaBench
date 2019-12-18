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
struct m2p_channel {int /*<<< orphan*/ * client; int /*<<< orphan*/  irq; } ;
struct ep93xx_dma_m2p_client {struct m2p_channel* channel; } ;

/* Variables and functions */
 int /*<<< orphan*/  channel_disable (struct m2p_channel*) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct m2p_channel*) ; 

void ep93xx_dma_m2p_client_unregister(struct ep93xx_dma_m2p_client *cl)
{
	struct m2p_channel *ch = cl->channel;

	channel_disable(ch);
	free_irq(ch->irq, ch);
	ch->client = NULL;
}