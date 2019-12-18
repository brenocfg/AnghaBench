#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct reordering_mpdu {int dummy; } ;
struct reordering_list {scalar_t__ qlen; int /*<<< orphan*/ * next; } ;
typedef  int /*<<< orphan*/  UINT32 ;
struct TYPE_5__ {int /*<<< orphan*/ * mem; struct reordering_list freelist; int /*<<< orphan*/  lock; } ;
struct TYPE_6__ {TYPE_1__ mpdu_blk_pool; } ;
typedef  int /*<<< orphan*/ * PUCHAR ;
typedef  TYPE_2__* PRTMP_ADAPTER ;
typedef  int /*<<< orphan*/  BOOLEAN ;

/* Variables and functions */
 int /*<<< orphan*/  DBGPRINT (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  NdisAllocateSpinLock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  NdisZeroMemory (struct reordering_mpdu*,int) ; 
 int /*<<< orphan*/  RT_DEBUG_ERROR ; 
 int /*<<< orphan*/  RT_DEBUG_TRACE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  ba_enqueue (struct reordering_list*,struct reordering_mpdu*) ; 
 int /*<<< orphan*/  os_alloc_mem (TYPE_2__*,int /*<<< orphan*/ **,int) ; 

BOOLEAN ba_reordering_resource_init(PRTMP_ADAPTER pAd, int num)
{
	int     i;
	PUCHAR  mem;
	struct reordering_mpdu *mpdu_blk;
	struct reordering_list *freelist;

	/* allocate spinlock */
	NdisAllocateSpinLock(&pAd->mpdu_blk_pool.lock);

	/* initialize freelist */
	freelist = &pAd->mpdu_blk_pool.freelist;
	freelist->next = NULL;
	freelist->qlen = 0;

	DBGPRINT(RT_DEBUG_TRACE, ("Allocate %d memory for BA reordering\n", (UINT32)(num*sizeof(struct reordering_mpdu))));

	/* allocate number of mpdu_blk memory */
	os_alloc_mem(pAd, (PUCHAR *)&mem, (num*sizeof(struct reordering_mpdu)));

	pAd->mpdu_blk_pool.mem = mem;

	if (mem == NULL)
	{
		DBGPRINT(RT_DEBUG_ERROR, ("Can't Allocate Memory for BA Reordering\n"));
		return(FALSE);
	}

	/* build mpdu_blk free list */
	for (i=0; i<num; i++)
	{
		/* get mpdu_blk */
		mpdu_blk = (struct reordering_mpdu *) mem;
		/* initial mpdu_blk */
		NdisZeroMemory(mpdu_blk, sizeof(struct reordering_mpdu));
		/* next mpdu_blk */
		mem += sizeof(struct reordering_mpdu);
		/* insert mpdu_blk into freelist */
		ba_enqueue(freelist, mpdu_blk);
	}

	return(TRUE);
}