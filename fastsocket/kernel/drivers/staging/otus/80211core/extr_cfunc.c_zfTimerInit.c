#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zdev_t ;
typedef  int u8_t ;
struct TYPE_5__ {int freeCount; TYPE_1__* list; TYPE_1__* tail; TYPE_1__* head; } ;
struct TYPE_6__ {int /*<<< orphan*/  bTimerReady; TYPE_2__ timerList; } ;
struct TYPE_4__ {struct TYPE_4__* next; struct TYPE_4__* pre; } ;

/* Variables and functions */
 int /*<<< orphan*/  TRUE ; 
 int ZM_MAX_TIMER_COUNT ; 
 TYPE_3__* wd ; 
 int /*<<< orphan*/  zm_debug_msg0 (char*) ; 
 int /*<<< orphan*/  zmw_get_wlan_dev (int /*<<< orphan*/ *) ; 

void zfTimerInit(zdev_t* dev)
{
    u8_t   i;

    zmw_get_wlan_dev(dev);

    zm_debug_msg0("");

    wd->timerList.freeCount = ZM_MAX_TIMER_COUNT;
    wd->timerList.head = &(wd->timerList.list[0]);
    wd->timerList.tail = &(wd->timerList.list[ZM_MAX_TIMER_COUNT-1]);
    wd->timerList.head->pre = NULL;
    wd->timerList.head->next = &(wd->timerList.list[1]);
    wd->timerList.tail->pre = &(wd->timerList.list[ZM_MAX_TIMER_COUNT-2]);
    wd->timerList.tail->next = NULL;

    for( i=1; i<(ZM_MAX_TIMER_COUNT-1); i++ )
    {
        wd->timerList.list[i].pre = &(wd->timerList.list[i-1]);
        wd->timerList.list[i].next = &(wd->timerList.list[i+1]);
    }

    wd->bTimerReady = TRUE;
}