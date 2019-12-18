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
 int /*<<< orphan*/  ASSERT (struct reordering_mpdu*) ; 
 int /*<<< orphan*/  NdisAcquireSpinLock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  NdisReleaseSpinLock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ba_enqueue (int /*<<< orphan*/ *,struct reordering_mpdu*) ; 

__attribute__((used)) static void ba_mpdu_blk_free(PRTMP_ADAPTER pAd, struct reordering_mpdu *mpdu_blk)
{
	ASSERT(mpdu_blk);

	NdisAcquireSpinLock(&pAd->mpdu_blk_pool.lock);
//	blk_count--;
	ba_enqueue(&pAd->mpdu_blk_pool.freelist, mpdu_blk);
	NdisReleaseSpinLock(&pAd->mpdu_blk_pool.lock);
}