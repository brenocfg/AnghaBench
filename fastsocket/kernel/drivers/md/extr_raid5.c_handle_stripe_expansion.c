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
struct stripe_head {int disks; int pd_idx; int qd_idx; int /*<<< orphan*/  state; TYPE_1__* dev; } ;
struct r5conf {int raid_disks; } ;
struct dma_async_tx_descriptor {int dummy; } ;
struct async_submit_ctl {int dummy; } ;
typedef  int /*<<< orphan*/  sector_t ;
struct TYPE_2__ {int /*<<< orphan*/  flags; int /*<<< orphan*/  page; } ;

/* Variables and functions */
 int /*<<< orphan*/  R5_Expanded ; 
 int /*<<< orphan*/  R5_UPTODATE ; 
 int /*<<< orphan*/  STRIPE_EXPANDING ; 
 int /*<<< orphan*/  STRIPE_EXPAND_READY ; 
 int /*<<< orphan*/  STRIPE_EXPAND_SOURCE ; 
 int /*<<< orphan*/  STRIPE_HANDLE ; 
 int /*<<< orphan*/  STRIPE_SIZE ; 
 struct dma_async_tx_descriptor* async_memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct async_submit_ctl*) ; 
 int /*<<< orphan*/  async_tx_quiesce (struct dma_async_tx_descriptor**) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  compute_blocknr (struct stripe_head*,int,int) ; 
 struct stripe_head* get_active_stripe (struct r5conf*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  init_async_submit (struct async_submit_ctl*,int /*<<< orphan*/ ,struct dma_async_tx_descriptor*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  raid5_compute_sector (struct r5conf*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  release_stripe (struct stripe_head*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void handle_stripe_expansion(struct r5conf *conf, struct stripe_head *sh)
{
	int i;

	/* We have read all the blocks in this stripe and now we need to
	 * copy some of them into a target stripe for expand.
	 */
	struct dma_async_tx_descriptor *tx = NULL;
	clear_bit(STRIPE_EXPAND_SOURCE, &sh->state);
	for (i = 0; i < sh->disks; i++)
		if (i != sh->pd_idx && i != sh->qd_idx) {
			int dd_idx, j;
			struct stripe_head *sh2;
			struct async_submit_ctl submit;

			sector_t bn = compute_blocknr(sh, i, 1);
			sector_t s = raid5_compute_sector(conf, bn, 0,
							  &dd_idx, NULL);
			sh2 = get_active_stripe(conf, s, 0, 1, 1);
			if (sh2 == NULL)
				/* so far only the early blocks of this stripe
				 * have been requested.  When later blocks
				 * get requested, we will try again
				 */
				continue;
			if (!test_bit(STRIPE_EXPANDING, &sh2->state) ||
			   test_bit(R5_Expanded, &sh2->dev[dd_idx].flags)) {
				/* must have already done this block */
				release_stripe(sh2);
				continue;
			}

			/* place all the copies on one channel */
			init_async_submit(&submit, 0, tx, NULL, NULL, NULL);
			tx = async_memcpy(sh2->dev[dd_idx].page,
					  sh->dev[i].page, 0, 0, STRIPE_SIZE,
					  &submit);

			set_bit(R5_Expanded, &sh2->dev[dd_idx].flags);
			set_bit(R5_UPTODATE, &sh2->dev[dd_idx].flags);
			for (j = 0; j < conf->raid_disks; j++)
				if (j != sh2->pd_idx &&
				    j != sh2->qd_idx &&
				    !test_bit(R5_Expanded, &sh2->dev[j].flags))
					break;
			if (j == conf->raid_disks) {
				set_bit(STRIPE_EXPAND_READY, &sh2->state);
				set_bit(STRIPE_HANDLE, &sh2->state);
			}
			release_stripe(sh2);

		}
	/* done submitting copies, wait for them to complete */
	async_tx_quiesce(&tx);
}