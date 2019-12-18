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
struct TYPE_2__ {scalar_t__ cnt; scalar_t__ off; } ;
struct rsxx_dma {unsigned int laddr; int /*<<< orphan*/  list; void* cb_data; int /*<<< orphan*/  cb; scalar_t__ pg_off; int /*<<< orphan*/ * page; TYPE_1__ sub_page; scalar_t__ dma_addr; int /*<<< orphan*/  cmd; } ;
struct rsxx_cardinfo {int dummy; } ;
struct list_head {int dummy; } ;
typedef  int /*<<< orphan*/  rsxx_dma_cb ;

/* Variables and functions */
 int /*<<< orphan*/  CARD_TO_DEV (struct rsxx_cardinfo*) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  HW_CMD_BLK_DISCARD ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,unsigned int) ; 
 struct rsxx_dma* kmem_cache_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,struct list_head*) ; 
 int /*<<< orphan*/  rsxx_dma_pool ; 

__attribute__((used)) static int rsxx_queue_discard(struct rsxx_cardinfo *card,
				  struct list_head *q,
				  unsigned int laddr,
				  rsxx_dma_cb cb,
				  void *cb_data)
{
	struct rsxx_dma *dma;

	dma = kmem_cache_alloc(rsxx_dma_pool, GFP_KERNEL);
	if (!dma)
		return -ENOMEM;

	dma->cmd          = HW_CMD_BLK_DISCARD;
	dma->laddr        = laddr;
	dma->dma_addr     = 0;
	dma->sub_page.off = 0;
	dma->sub_page.cnt = 0;
	dma->page         = NULL;
	dma->pg_off       = 0;
	dma->cb	          = cb;
	dma->cb_data      = cb_data;

	dev_dbg(CARD_TO_DEV(card), "Queuing[D] laddr %x\n", dma->laddr);

	list_add_tail(&dma->list, q);

	return 0;
}