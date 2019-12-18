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
typedef  int uint32_t ;
struct TYPE_10__ {TYPE_2__* pFree; TYPE_2__* pTail; } ;
typedef  TYPE_3__ dmacHw_DESC_RING_t ;
struct TYPE_11__ {int /*<<< orphan*/  transferType; } ;
typedef  TYPE_4__ dmacHw_CONFIG_t ;
struct TYPE_8__ {int lo; } ;
struct TYPE_9__ {int /*<<< orphan*/  devCtl; scalar_t__ sar; scalar_t__ dar; TYPE_1__ ctl; } ;

/* Variables and functions */
 int dmacHw_DESC_FREE ; 
 scalar_t__ dmacHw_DST_IS_MEMORY (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dmacHw_FREE_USER_MEMORY ; 
 TYPE_3__* dmacHw_GET_DESC_RING (void*) ; 
 int /*<<< orphan*/  dmacHw_NEXT_DESC (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pFree ; 
 void stub1 (void*) ; 
 void stub2 (void*) ; 

int dmacHw_freeMem(dmacHw_CONFIG_t *pConfig,	/*   [ IN ] Configuration settings */
		   void *pDescriptor,	/*   [ IN ] Descriptor buffer */
		   void (*fpFree) (void *)	/*   [ IN ] Function pointer to free data memory */
    ) {
	dmacHw_DESC_RING_t *pRing = dmacHw_GET_DESC_RING(pDescriptor);
	uint32_t count = 0;

	if (fpFree == NULL) {
		return -1;
	}

	while ((pRing->pFree != pRing->pTail)
	       && (pRing->pFree->ctl.lo & dmacHw_DESC_FREE)) {
		if (pRing->pFree->devCtl == dmacHw_FREE_USER_MEMORY) {
			/* Identify, which memory to free */
			if (dmacHw_DST_IS_MEMORY(pConfig->transferType)) {
				(*fpFree) ((void *)pRing->pFree->dar);
			} else {
				/* Destination was a peripheral */
				(*fpFree) ((void *)pRing->pFree->sar);
			}
			/* Unmark user memory to indicate it is freed */
			pRing->pFree->devCtl = ~dmacHw_FREE_USER_MEMORY;
		}
		dmacHw_NEXT_DESC(pRing, pFree);

		count++;
	}

	return count;
}