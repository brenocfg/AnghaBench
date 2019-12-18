#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  hi; } ;
struct TYPE_6__ {TYPE_1__ ctl; } ;
typedef  TYPE_2__ dmacHw_DESC_t ;
struct TYPE_7__ {int num; int /*<<< orphan*/  pProg; TYPE_2__* pHead; TYPE_2__* pEnd; TYPE_2__* pTail; TYPE_2__* pFree; } ;
typedef  TYPE_3__ dmacHw_DESC_RING_t ;

/* Variables and functions */
 int /*<<< orphan*/  dmacHw_DESC_FREE ; 
 int /*<<< orphan*/  dmacHw_DESC_INIT ; 
 TYPE_3__* dmacHw_GET_DESC_RING (void*) ; 

void dmacHw_resetDescriptorControl(void *pDescriptor	/*   [ IN ] Descriptor buffer  */
    ) {
	int i;
	dmacHw_DESC_RING_t *pRing;
	dmacHw_DESC_t *pDesc;

	pRing = dmacHw_GET_DESC_RING(pDescriptor);
	pDesc = pRing->pHead;

	for (i = 0; i < pRing->num; i++) {
		/* Mark descriptor is ready to use */
		pDesc->ctl.hi = dmacHw_DESC_FREE;
		/* Look into next link list item */
		pDesc++;
	}
	pRing->pFree = pRing->pTail = pRing->pEnd = pRing->pHead;
	pRing->pProg = dmacHw_DESC_INIT;
}