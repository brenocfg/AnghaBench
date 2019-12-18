#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct spider_net_descr_chain {TYPE_3__* head; struct spider_net_descr* tail; } ;
struct spider_net_descr {struct spider_net_descr* next; int /*<<< orphan*/  bus_addr; TYPE_2__* prev; } ;
struct spider_net_card {struct spider_net_descr_chain rx_chain; } ;
struct TYPE_6__ {struct TYPE_6__* next; } ;
struct TYPE_5__ {TYPE_1__* hwdescr; } ;
struct TYPE_4__ {int /*<<< orphan*/  next_descr_addr; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  spider_net_enable_rxdmac (struct spider_net_card*) ; 
 int /*<<< orphan*/  spider_net_free_rx_chain_contents (struct spider_net_card*) ; 
 scalar_t__ spider_net_prepare_rx_descr (struct spider_net_card*,TYPE_3__*) ; 
 int /*<<< orphan*/  spider_net_refill_rx_chain (struct spider_net_card*) ; 

__attribute__((used)) static int
spider_net_alloc_rx_skbs(struct spider_net_card *card)
{
	struct spider_net_descr_chain *chain = &card->rx_chain;
	struct spider_net_descr *start = chain->tail;
	struct spider_net_descr *descr = start;

	/* Link up the hardware chain pointers */
	do {
		descr->prev->hwdescr->next_descr_addr = descr->bus_addr;
		descr = descr->next;
	} while (descr != start);

	/* Put at least one buffer into the chain. if this fails,
	 * we've got a problem. If not, spider_net_refill_rx_chain
	 * will do the rest at the end of this function. */
	if (spider_net_prepare_rx_descr(card, chain->head))
		goto error;
	else
		chain->head = chain->head->next;

	/* This will allocate the rest of the rx buffers;
	 * if not, it's business as usual later on. */
	spider_net_refill_rx_chain(card);
	spider_net_enable_rxdmac(card);
	return 0;

error:
	spider_net_free_rx_chain_contents(card);
	return -ENOMEM;
}