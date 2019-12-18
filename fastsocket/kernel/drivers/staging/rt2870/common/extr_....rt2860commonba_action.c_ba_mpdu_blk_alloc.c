#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct reordering_mpdu {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  lock; int /*<<< orphan*/  freelist; } ;
struct TYPE_5__ {TYPE_1__ mpdu_blk_pool; } ;
typedef  TYPE_2__* PRTMP_ADAPTER ;

/* Variables and functions */
 int /*<<< orphan*/  NdisAcquireSpinLock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  NdisReleaseSpinLock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  NdisZeroMemory (struct reordering_mpdu*,int) ; 
 struct reordering_mpdu* ba_dequeue (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct reordering_mpdu *ba_mpdu_blk_alloc(PRTMP_ADAPTER pAd)
{
	struct reordering_mpdu *mpdu_blk;

	NdisAcquireSpinLock(&pAd->mpdu_blk_pool.lock);
	mpdu_blk = ba_dequeue(&pAd->mpdu_blk_pool.freelist);
	if (mpdu_blk)
	{
//		blk_count++;
		/* reset mpdu_blk */
		NdisZeroMemory(mpdu_blk, sizeof(struct reordering_mpdu));
	}
	NdisReleaseSpinLock(&pAd->mpdu_blk_pool.lock);
	return mpdu_blk;
}