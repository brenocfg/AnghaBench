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
typedef  int u16_t ;
struct TYPE_5__ {TYPE_1__* blockingApList; } ;
struct TYPE_6__ {TYPE_2__ sta; } ;
struct TYPE_4__ {scalar_t__* addr; scalar_t__ weight; } ;

/* Variables and functions */
 int ZM_MAX_BLOCKING_AP_LIST_SIZE ; 
 TYPE_3__* wd ; 
 int /*<<< orphan*/  zmw_declare_for_critical_section () ; 
 int /*<<< orphan*/  zmw_enter_critical_section (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zmw_get_wlan_dev (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zmw_leave_critical_section (int /*<<< orphan*/ *) ; 

void zfStaPutApIntoBlockingList(zdev_t* dev, u8_t* bssid, u8_t weight)
{
    u16_t i, j;
    zmw_get_wlan_dev(dev);
    zmw_declare_for_critical_section();

    if (weight > 0)
    {
        zmw_enter_critical_section(dev);
        /*Find same bssid entry first*/
        for (i=0; i<ZM_MAX_BLOCKING_AP_LIST_SIZE; i++)
        {
            for (j=0; j<6; j++)
            {
                if(wd->sta.blockingApList[i].addr[j]!= bssid[j])
                {
                    break;
                }
            }

            if(j==6)
            {
                break;
            }
        }
        /*This bssid doesn't have old record.Find an empty entry*/
        if (i == ZM_MAX_BLOCKING_AP_LIST_SIZE)
        {
            for (i=0; i<ZM_MAX_BLOCKING_AP_LIST_SIZE; i++)
            {
                if (wd->sta.blockingApList[i].weight == 0)
                {
                    break;
                }
            }
        }

        /* If the list is full, pick one entry for replacement */
        if (i == ZM_MAX_BLOCKING_AP_LIST_SIZE)
        {
            i = bssid[5] & (ZM_MAX_BLOCKING_AP_LIST_SIZE-1);
        }

        /* Update AP address and weight */
        for (j=0; j<6; j++)
        {
            wd->sta.blockingApList[i].addr[j] = bssid[j];
        }

        wd->sta.blockingApList[i].weight = weight;
        zmw_leave_critical_section(dev);
    }

    return;
}