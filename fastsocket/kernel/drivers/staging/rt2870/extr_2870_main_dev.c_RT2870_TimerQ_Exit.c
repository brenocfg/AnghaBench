#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {struct TYPE_8__* pNext; } ;
struct TYPE_6__ {int /*<<< orphan*/  status; TYPE_3__* pQHead; int /*<<< orphan*/ * pQTail; int /*<<< orphan*/  pTimerQPoll; int /*<<< orphan*/ * pQPollFreeList; } ;
struct TYPE_7__ {int /*<<< orphan*/  TimerQLock; TYPE_1__ TimerQ; } ;
typedef  TYPE_2__ RTMP_ADAPTER ;
typedef  TYPE_3__ RT2870_TIMER_ENTRY ;

/* Variables and functions */
 int /*<<< orphan*/  RT2870_THREAD_STOPED ; 
 int /*<<< orphan*/  RTMP_IRQ_LOCK (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  RTMP_IRQ_UNLOCK (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  os_free_mem (TYPE_2__*,int /*<<< orphan*/ ) ; 

void RT2870_TimerQ_Exit(RTMP_ADAPTER *pAd)
{
	RT2870_TIMER_ENTRY *pTimerQ;
	unsigned long irqFlags;

	RTMP_IRQ_LOCK(&pAd->TimerQLock, irqFlags);
	while (pAd->TimerQ.pQHead)
	{
		pTimerQ = pAd->TimerQ.pQHead;
		pAd->TimerQ.pQHead = pTimerQ->pNext;
		// remove the timeQ
	}
	pAd->TimerQ.pQPollFreeList = NULL;
	os_free_mem(pAd, pAd->TimerQ.pTimerQPoll);
	pAd->TimerQ.pQTail = NULL;
	pAd->TimerQ.pQHead = NULL;
	pAd->TimerQ.status = RT2870_THREAD_STOPED;
	RTMP_IRQ_UNLOCK(&pAd->TimerQLock, irqFlags);

}