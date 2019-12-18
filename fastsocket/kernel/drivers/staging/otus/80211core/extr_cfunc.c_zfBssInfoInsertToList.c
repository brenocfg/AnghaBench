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
struct zsBssInfo {struct zsBssInfo* next; } ;
struct TYPE_5__ {scalar_t__ bssCount; struct zsBssInfo* tail; struct zsBssInfo* head; } ;
struct TYPE_4__ {TYPE_2__ bssList; } ;
struct TYPE_6__ {TYPE_1__ sta; } ;

/* Variables and functions */
 TYPE_3__* wd ; 
 int /*<<< orphan*/  zm_assert (struct zsBssInfo*) ; 
 int /*<<< orphan*/  zmw_get_wlan_dev (int /*<<< orphan*/ *) ; 

void zfBssInfoInsertToList(zdev_t* dev, struct zsBssInfo* pBssInfo)
{
    zmw_get_wlan_dev(dev);

    zm_assert(pBssInfo);

    //zm_debug_msg2("pBssInfo = ", pBssInfo);

    if ( wd->sta.bssList.bssCount == 0 )
    {
        wd->sta.bssList.head = pBssInfo;
        wd->sta.bssList.tail = pBssInfo;
    }
    else
    {
        wd->sta.bssList.tail->next = pBssInfo;
        wd->sta.bssList.tail = pBssInfo;
    }

    pBssInfo->next = NULL;
    wd->sta.bssList.bssCount++;

    //zm_debug_msg2("bss count = ", wd->sta.bssList.bssCount);
}