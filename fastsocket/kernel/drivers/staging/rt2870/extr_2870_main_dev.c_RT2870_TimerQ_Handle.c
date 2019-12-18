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
struct TYPE_11__ {scalar_t__ State; int /*<<< orphan*/  TimerValue; int /*<<< orphan*/  TimerObj; scalar_t__ Repeat; scalar_t__ cookie; int /*<<< orphan*/  (* handle ) (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_4__*) ;} ;
struct TYPE_10__ {struct TYPE_10__* pNext; TYPE_4__* pRaTimer; } ;
struct TYPE_8__ {scalar_t__ status; TYPE_3__* pQPollFreeList; TYPE_3__* pQTail; TYPE_3__* pQHead; } ;
struct TYPE_9__ {TYPE_1__ TimerQ; int /*<<< orphan*/  PM_FlgSuspend; int /*<<< orphan*/  TimerQLock; int /*<<< orphan*/  RTUSBTimer_semaphore; int /*<<< orphan*/  TimerFunc_kill; } ;
typedef  TYPE_2__ RTMP_ADAPTER ;
typedef  TYPE_3__ RT2870_TIMER_ENTRY ;
typedef  TYPE_4__ RALINK_TIMER_STRUCT ;
typedef  int /*<<< orphan*/  PVOID ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 scalar_t__ RT2870_THREAD_STOPED ; 
 int /*<<< orphan*/  RTMP_IRQ_LOCK (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  RTMP_IRQ_UNLOCK (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  RTMP_OS_Add_Timer (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RTMP_SET_FLAG (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int down_interruptible (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fRTMP_ADAPTER_HALT_IN_PROGRESS ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_4__*) ; 

__attribute__((used)) static void RT2870_TimerQ_Handle(RTMP_ADAPTER *pAd)
{
	int status;
	RALINK_TIMER_STRUCT	*pTimer;
	RT2870_TIMER_ENTRY	*pEntry;
	unsigned long	irqFlag;

	while(!pAd->TimerFunc_kill)
	{
//		printk("waiting for event!\n");
		pTimer = NULL;

		status = down_interruptible(&(pAd->RTUSBTimer_semaphore));

		if (pAd->TimerQ.status == RT2870_THREAD_STOPED)
			break;

		// event happened.
		while(pAd->TimerQ.pQHead)
		{
			RTMP_IRQ_LOCK(&pAd->TimerQLock, irqFlag);
			pEntry = pAd->TimerQ.pQHead;
			if (pEntry)
			{
				pTimer = pEntry->pRaTimer;

				// update pQHead
				pAd->TimerQ.pQHead = pEntry->pNext;
				if (pEntry == pAd->TimerQ.pQTail)
					pAd->TimerQ.pQTail = NULL;

				// return this queue entry to timerQFreeList.
				pEntry->pNext = pAd->TimerQ.pQPollFreeList;
				pAd->TimerQ.pQPollFreeList = pEntry;
			}
			RTMP_IRQ_UNLOCK(&pAd->TimerQLock, irqFlag);

			if (pTimer)
			{
				if (pTimer->handle != NULL)
				if (!pAd->PM_FlgSuspend)
					pTimer->handle(NULL, (PVOID) pTimer->cookie, NULL, pTimer);
				if ((pTimer->Repeat) && (pTimer->State == FALSE))
					RTMP_OS_Add_Timer(&pTimer->TimerObj, pTimer->TimerValue);
			}
		}

		if (status != 0)
		{
			pAd->TimerQ.status = RT2870_THREAD_STOPED;
			RTMP_SET_FLAG(pAd, fRTMP_ADAPTER_HALT_IN_PROGRESS);
			break;
		}
	}
}