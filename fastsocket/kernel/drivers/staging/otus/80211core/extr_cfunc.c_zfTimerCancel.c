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
typedef  scalar_t__ u16_t ;
struct zsTimerEntry {scalar_t__ event; struct zsTimerEntry* next; struct zsTimerEntry* pre; } ;
struct TYPE_3__ {scalar_t__ freeCount; struct zsTimerEntry* tail; struct zsTimerEntry* head; } ;
struct TYPE_4__ {TYPE_1__ timerList; } ;

/* Variables and functions */
 scalar_t__ ZM_MAX_TIMER_COUNT ; 
 TYPE_2__* wd ; 
 int /*<<< orphan*/  zmw_get_wlan_dev (int /*<<< orphan*/ *) ; 

u16_t zfTimerCancel(zdev_t* dev, u16_t event)
{
    struct zsTimerEntry *pEntry;
    u8_t   i, count;

    zmw_get_wlan_dev(dev);

    //zm_debug_msg2("event = ", event);
    //zm_debug_msg1("free timer count(b) = ", wd->timerList.freeCount);

    pEntry = wd->timerList.head;
    count = ZM_MAX_TIMER_COUNT - wd->timerList.freeCount;

    for( i=0; i<count; i++ )
    {
        if ( pEntry->event == event )
        {
            if ( pEntry == wd->timerList.head )
            {   /* remove head entry */
                wd->timerList.head = pEntry->next;
                wd->timerList.tail->next = pEntry;
                pEntry->pre = wd->timerList.tail;
                wd->timerList.tail = pEntry;
                pEntry = wd->timerList.head;
            }
            else
            {   /* remove non-head entry */
                pEntry->pre->next = pEntry->next;
                pEntry->next->pre = pEntry->pre;
                wd->timerList.tail->next = pEntry;
                pEntry->pre = wd->timerList.tail;
                wd->timerList.tail = pEntry;
                pEntry = pEntry->next;
            }

            wd->timerList.freeCount++;
        }
        else
        {
            pEntry = pEntry->next;
        }
    }

    //zm_debug_msg1("free timer count(a) = ", wd->timerList.freeCount);

    return 0;
}