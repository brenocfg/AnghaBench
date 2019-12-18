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
typedef  scalar_t__ u8_t ;
struct zsBssInfo {scalar_t__ sortValue; struct zsBssInfo* next; } ;
struct TYPE_4__ {int bssCount; struct zsBssInfo* head; struct zsBssInfo* tail; } ;
struct TYPE_5__ {TYPE_1__ bssList; } ;
struct TYPE_6__ {TYPE_2__ sta; } ;

/* Variables and functions */
 TYPE_3__* wd ; 
 int /*<<< orphan*/  zmw_declare_for_critical_section () ; 
 int /*<<< orphan*/  zmw_enter_critical_section (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zmw_get_wlan_dev (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zmw_leave_critical_section (int /*<<< orphan*/ *) ; 

void zfBssInfoReorderList(zdev_t* dev)
{
    struct zsBssInfo* pBssInfo = NULL;
    struct zsBssInfo* pInsBssInfo = NULL;
    struct zsBssInfo* pNextBssInfo = NULL;
    struct zsBssInfo* pPreBssInfo = NULL;
    u8_t i = 0;

    zmw_get_wlan_dev(dev);

    zmw_declare_for_critical_section();

    zmw_enter_critical_section(dev);

    if (wd->sta.bssList.bssCount > 1)
    {
        pInsBssInfo = wd->sta.bssList.head;
        wd->sta.bssList.tail = pInsBssInfo;
        pBssInfo = pInsBssInfo->next;
        pInsBssInfo->next = NULL;
        while (pBssInfo != NULL)
        {
            i = 0;
            while (1)
            {
//                if (pBssInfo->signalStrength >= pInsBssInfo->signalStrength)
                if( pBssInfo->sortValue >= pInsBssInfo->sortValue)
                {
                    if (i==0)
                    {
                        //Insert BssInfo to head
                        wd->sta.bssList.head = pBssInfo;
                        pNextBssInfo = pBssInfo->next;
                        pBssInfo->next = pInsBssInfo;
                        break;
                    }
                    else
                    {
                        //Insert BssInfo to neither head nor tail
                        pPreBssInfo->next = pBssInfo;
                        pNextBssInfo = pBssInfo->next;
                        pBssInfo->next = pInsBssInfo;
                        break;
                    }
                }
                else
                {
                    if (pInsBssInfo->next != NULL)
                    {
                        //Signal strength smaller than current BssInfo, check next
                        pPreBssInfo = pInsBssInfo;
                        pInsBssInfo = pInsBssInfo->next;
                    }
                    else
                    {
                        //Insert BssInfo to tail
                        pInsBssInfo->next = pBssInfo;
                        pNextBssInfo = pBssInfo->next;
                        wd->sta.bssList.tail = pBssInfo;
                        pBssInfo->next = NULL;
                        break;
                    }
                }
                i++;
            }
            pBssInfo = pNextBssInfo;
            pInsBssInfo = wd->sta.bssList.head;
        }
    } //if (wd->sta.bssList.bssCount > 1)

    zmw_leave_critical_section(dev);
}