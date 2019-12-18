#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct spider_net_descr_chain {int /*<<< orphan*/  dma_addr; int /*<<< orphan*/  hwring; int /*<<< orphan*/  num_desc; struct spider_net_descr* ring; } ;
struct spider_net_descr {struct spider_net_descr* next; TYPE_2__* hwdescr; scalar_t__ bus_addr; } ;
struct spider_net_card {TYPE_1__* pdev; } ;
struct TYPE_4__ {scalar_t__ next_descr_addr; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
spider_net_free_chain(struct spider_net_card *card,
		      struct spider_net_descr_chain *chain)
{
	struct spider_net_descr *descr;

	descr = chain->ring;
	do {
		descr->bus_addr = 0;
		descr->hwdescr->next_descr_addr = 0;
		descr = descr->next;
	} while (descr != chain->ring);

	dma_free_coherent(&card->pdev->dev, chain->num_desc,
	    chain->hwring, chain->dma_addr);
}