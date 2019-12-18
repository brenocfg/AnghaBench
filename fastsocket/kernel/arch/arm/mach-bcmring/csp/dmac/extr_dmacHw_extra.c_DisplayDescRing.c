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
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_5__ {int /*<<< orphan*/  hi; int /*<<< orphan*/  lo; } ;
struct TYPE_6__ {int /*<<< orphan*/  devCtl; int /*<<< orphan*/  dstat; int /*<<< orphan*/  sstat; TYPE_1__ ctl; scalar_t__ llp; int /*<<< orphan*/  dar; int /*<<< orphan*/  sar; } ;
typedef  TYPE_2__ dmacHw_DESC_t ;
struct TYPE_7__ {TYPE_2__* pFree; TYPE_2__* pEnd; TYPE_2__* pProg; TYPE_2__* pTail; TYPE_2__* pHead; } ;
typedef  TYPE_3__ dmacHw_DESC_RING_t ;

/* Variables and functions */
 TYPE_3__* dmacHw_GET_DESC_RING (void*) ; 
 int stub1 (char const*) ; 
 int stub10 (char const*,...) ; 
 int stub11 (char const*,...) ; 
 int stub12 (char const*,...) ; 
 int stub13 (char const*,...) ; 
 int stub14 (char const*,...) ; 
 int stub15 (char const*) ; 
 int stub16 (char const*) ; 
 int stub17 (char const*) ; 
 int stub18 (char const*) ; 
 int stub19 (char const*) ; 
 int stub2 (char const*) ; 
 int stub20 (char const*,...) ; 
 int stub21 (char const*,...) ; 
 int stub22 (char const*,...) ; 
 int stub23 (char const*,...) ; 
 int stub24 (char const*,...) ; 
 int stub25 (char const*,...) ; 
 int stub26 (char const*,...) ; 
 int stub27 (char const*,...) ; 
 int stub28 (char const*,...) ; 
 int stub3 (char const*) ; 
 int stub4 (char const*) ; 
 int stub5 (char const*) ; 
 int stub6 (char const*,...) ; 
 int stub7 (char const*,...) ; 
 int stub8 (char const*,...) ; 
 int stub9 (char const*,...) ; 

__attribute__((used)) static void DisplayDescRing(void *pDescriptor,	/*   [ IN ] Descriptor buffer */
			    int (*fpPrint) (const char *, ...)	/*   [ IN ] Callback to the print function */
    ) {
	dmacHw_DESC_RING_t *pRing = dmacHw_GET_DESC_RING(pDescriptor);
	dmacHw_DESC_t *pStart;

	if (pRing->pHead == NULL) {
		return;
	}

	pStart = pRing->pHead;

	while ((dmacHw_DESC_t *) pStart->llp != pRing->pHead) {
		if (pStart == pRing->pHead) {
			(*fpPrint) ("Head\n");
		}
		if (pStart == pRing->pTail) {
			(*fpPrint) ("Tail\n");
		}
		if (pStart == pRing->pProg) {
			(*fpPrint) ("Prog\n");
		}
		if (pStart == pRing->pEnd) {
			(*fpPrint) ("End\n");
		}
		if (pStart == pRing->pFree) {
			(*fpPrint) ("Free\n");
		}
		(*fpPrint) ("0x%X:\n", (uint32_t) pStart);
		(*fpPrint) ("sar    0x%0X\n", pStart->sar);
		(*fpPrint) ("dar    0x%0X\n", pStart->dar);
		(*fpPrint) ("llp    0x%0X\n", pStart->llp);
		(*fpPrint) ("ctl.lo 0x%0X\n", pStart->ctl.lo);
		(*fpPrint) ("ctl.hi 0x%0X\n", pStart->ctl.hi);
		(*fpPrint) ("sstat  0x%0X\n", pStart->sstat);
		(*fpPrint) ("dstat  0x%0X\n", pStart->dstat);
		(*fpPrint) ("devCtl 0x%0X\n", pStart->devCtl);

		pStart = (dmacHw_DESC_t *) pStart->llp;
	}
	if (pStart == pRing->pHead) {
		(*fpPrint) ("Head\n");
	}
	if (pStart == pRing->pTail) {
		(*fpPrint) ("Tail\n");
	}
	if (pStart == pRing->pProg) {
		(*fpPrint) ("Prog\n");
	}
	if (pStart == pRing->pEnd) {
		(*fpPrint) ("End\n");
	}
	if (pStart == pRing->pFree) {
		(*fpPrint) ("Free\n");
	}
	(*fpPrint) ("0x%X:\n", (uint32_t) pStart);
	(*fpPrint) ("sar    0x%0X\n", pStart->sar);
	(*fpPrint) ("dar    0x%0X\n", pStart->dar);
	(*fpPrint) ("llp    0x%0X\n", pStart->llp);
	(*fpPrint) ("ctl.lo 0x%0X\n", pStart->ctl.lo);
	(*fpPrint) ("ctl.hi 0x%0X\n", pStart->ctl.hi);
	(*fpPrint) ("sstat  0x%0X\n", pStart->sstat);
	(*fpPrint) ("dstat  0x%0X\n", pStart->dstat);
	(*fpPrint) ("devCtl 0x%0X\n", pStart->devCtl);
}