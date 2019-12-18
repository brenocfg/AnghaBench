#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {unsigned long long ust; void* msc; } ;
typedef  TYPE_1__ ustmsc_t ;
struct TYPE_9__ {int /*<<< orphan*/  lock; } ;
typedef  TYPE_2__ lithium_t ;
struct TYPE_10__ {TYPE_4__* desc; TYPE_2__* lith; } ;
typedef  TYPE_3__ dma_chan_t ;
struct TYPE_11__ {int /*<<< orphan*/  ustreg; int /*<<< orphan*/  mscreg; } ;
typedef  TYPE_4__ dma_chan_desc_t ;

/* Variables and functions */
 int /*<<< orphan*/  LI_UST_HIGH ; 
 int /*<<< orphan*/  LI_UST_LOW ; 
 void* li_readl (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void li_read_USTMSC(dma_chan_t *chan, ustmsc_t *ustmsc)
{
	lithium_t *lith = chan->lith;
	const dma_chan_desc_t *desc = chan->desc;
	unsigned long now_low, now_high0, now_high1, chan_ust;

	spin_lock(&lith->lock);
	{
		/*
		 * retry until we do all five reads without the
		 * high word changing.  (High word increments
		 * every 2^32 microseconds, i.e., not often)
		 */
		do {
			now_high0 = li_readl(lith, LI_UST_HIGH);
			now_low = li_readl(lith, LI_UST_LOW);

			/*
			 * Lithium guarantees these two reads will be
			 * atomic -- ust will not increment after msc
			 * is read.
			 */

			ustmsc->msc = li_readl(lith, desc->mscreg);
			chan_ust = li_readl(lith, desc->ustreg);

			now_high1 = li_readl(lith, LI_UST_HIGH);
		} while (now_high0 != now_high1);
	}	
	spin_unlock(&lith->lock);
	ustmsc->ust = ((unsigned long long) now_high0 << 32 | chan_ust);
}