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
struct m2p_channel {struct ep93xx_dma_m2p_client* client; scalar_t__ base; } ;
struct ep93xx_dma_m2p_client {int flags; scalar_t__ name; } ;

/* Variables and functions */
 int /*<<< orphan*/  EBUSY ; 
 int /*<<< orphan*/  ENODEV ; 
 int EP93XX_DMA_M2P_PORT_MASK ; 
 int EP93XX_DMA_M2P_RX ; 
 struct m2p_channel* ERR_PTR (int /*<<< orphan*/ ) ; 
 struct m2p_channel* m2p_rx ; 
 struct m2p_channel* m2p_tx ; 
 int /*<<< orphan*/  pr_warning (char*,char*) ; 

__attribute__((used)) static struct m2p_channel *find_free_channel(struct ep93xx_dma_m2p_client *cl)
{
	struct m2p_channel *ch;
	int i;

	if (cl->flags & EP93XX_DMA_M2P_RX)
		ch = m2p_rx;
	else
		ch = m2p_tx;

	for (i = 0; ch[i].base; i++) {
		struct ep93xx_dma_m2p_client *client;

		client = ch[i].client;
		if (client != NULL) {
			int port;

			port = cl->flags & EP93XX_DMA_M2P_PORT_MASK;
			if (port == (client->flags &
				     EP93XX_DMA_M2P_PORT_MASK)) {
				pr_warning("DMA channel already used by %s\n",
					   cl->name ? : "unknown client");
				return ERR_PTR(-EBUSY);
			}
		}
	}

	for (i = 0; ch[i].base; i++) {
		if (ch[i].client == NULL)
			return ch + i;
	}

	pr_warning("No free DMA channel for %s\n",
		   cl->name ? : "unknown client");
	return ERR_PTR(-ENODEV);
}