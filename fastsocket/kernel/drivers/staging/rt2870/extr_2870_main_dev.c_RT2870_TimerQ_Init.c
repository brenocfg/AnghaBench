#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_5__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  status; int /*<<< orphan*/ * pQTail; int /*<<< orphan*/ * pQHead; TYPE_2__* pQPollFreeList; scalar_t__ pTimerQPoll; } ;
struct TYPE_7__ {struct TYPE_7__* pNext; } ;
struct TYPE_6__ {int /*<<< orphan*/  TimerQLock; TYPE_5__ TimerQ; } ;
typedef  TYPE_1__ RTMP_ADAPTER ;
typedef  TYPE_2__ RT2870_TIMER_ENTRY ;

/* Variables and functions */
 int /*<<< orphan*/  NdisAllocateSpinLock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  NdisZeroMemory (TYPE_5__*,int) ; 
 int /*<<< orphan*/  RT2870_THREAD_INITED ; 
 int /*<<< orphan*/  RTMP_IRQ_LOCK (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  RTMP_IRQ_UNLOCK (int /*<<< orphan*/ *,unsigned long) ; 
 int TIMER_QUEUE_SIZE_MAX ; 
 int /*<<< orphan*/  os_alloc_mem (TYPE_1__*,scalar_t__*,int) ; 

void RT2870_TimerQ_Init(RTMP_ADAPTER *pAd)
{
	int 	i;
	RT2870_TIMER_ENTRY *pQNode, *pEntry;
	unsigned long irqFlags;

	NdisAllocateSpinLock(&pAd->TimerQLock);

	RTMP_IRQ_LOCK(&pAd->TimerQLock, irqFlags);
	NdisZeroMemory(&pAd->TimerQ, sizeof(pAd->TimerQ));
	//InterlockedExchange(&pAd->TimerQ.count, 0);

	/* Initialise the wait q head */
	//init_waitqueue_head(&timerWaitQ);

	os_alloc_mem(pAd, &pAd->TimerQ.pTimerQPoll, sizeof(RT2870_TIMER_ENTRY) * TIMER_QUEUE_SIZE_MAX);
	if (pAd->TimerQ.pTimerQPoll)
	{
		pEntry = NULL;
		pQNode = (RT2870_TIMER_ENTRY *)pAd->TimerQ.pTimerQPoll;
		for (i = 0 ;i <TIMER_QUEUE_SIZE_MAX; i++)
		{
			pQNode->pNext = pEntry;
			pEntry = pQNode;
			pQNode++;
		}
		pAd->TimerQ.pQPollFreeList = pEntry;
		pAd->TimerQ.pQHead = NULL;
		pAd->TimerQ.pQTail = NULL;
		pAd->TimerQ.status = RT2870_THREAD_INITED;
	}
	RTMP_IRQ_UNLOCK(&pAd->TimerQLock, irqFlags);
}