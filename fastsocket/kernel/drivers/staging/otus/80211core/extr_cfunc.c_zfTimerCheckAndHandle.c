#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zdev_t ;
typedef  scalar_t__ u8_t ;
typedef  int /*<<< orphan*/  u16_t ;
struct zsTimerEntry {scalar_t__ timer; struct zsTimerEntry* pre; struct zsTimerEntry* next; int /*<<< orphan*/  event; } ;
struct TYPE_3__ {int freeCount; struct zsTimerEntry* tail; struct zsTimerEntry* head; } ;
struct TYPE_4__ {scalar_t__ tick; TYPE_1__ timerList; int /*<<< orphan*/  bTimerReady; } ;

/* Variables and functions */
 int ZM_MAX_TIMER_COUNT ; 
 TYPE_2__* wd ; 
 int /*<<< orphan*/  zfProcessEvent (int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  zmw_declare_for_critical_section () ; 
 int /*<<< orphan*/  zmw_enter_critical_section (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zmw_get_wlan_dev (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zmw_leave_critical_section (int /*<<< orphan*/ *) ; 

u16_t zfTimerCheckAndHandle(zdev_t* dev)
{
    struct zsTimerEntry *pEntry;
    struct zsTimerEntry *pTheLastEntry = NULL;
    u16_t  event[ZM_MAX_TIMER_COUNT];
    u8_t   i, j=0, count;

    zmw_get_wlan_dev(dev);

    zmw_declare_for_critical_section();

    if ( !wd->bTimerReady )
    {
        return 0;
    }

    zmw_enter_critical_section(dev);

    pEntry = wd->timerList.head;
    count = ZM_MAX_TIMER_COUNT - wd->timerList.freeCount;

    for( i=0; i<count; i++ )
    {
        // prevent from the case of tick overflow
        if ( ( pEntry->timer > wd->tick )&&
             ((pEntry->timer - wd->tick) < 1000000000) )
        {
            break;
        }

        event[j++] = pEntry->event;
        pTheLastEntry = pEntry;
        pEntry = pEntry->next;
    }

    if ( j > 0 )
    {
        wd->timerList.tail->next = wd->timerList.head;
        wd->timerList.head->pre = wd->timerList.tail;
        wd->timerList.head = pEntry;
        wd->timerList.tail = pTheLastEntry;
        wd->timerList.freeCount += j;
        //zm_debug_msg1("free timer count = ", wd->timerList.freeCount);
    }

    zmw_leave_critical_section(dev);

    zfProcessEvent(dev, event, j);

    return 0;
}