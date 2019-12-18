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
struct spider_net_card {TYPE_1__* netdev; } ;
struct TYPE_2__ {int flags; } ;

/* Variables and functions */
 int IFF_UP ; 
 int /*<<< orphan*/  netif_wake_queue (TYPE_1__*) ; 
 int /*<<< orphan*/  spider_net_kick_tx_dma (struct spider_net_card*) ; 
 scalar_t__ spider_net_release_tx_chain (struct spider_net_card*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
spider_net_cleanup_tx_ring(struct spider_net_card *card)
{
	if ((spider_net_release_tx_chain(card, 0) != 0) &&
	    (card->netdev->flags & IFF_UP)) {
		spider_net_kick_tx_dma(card);
		netif_wake_queue(card->netdev);
	}
}