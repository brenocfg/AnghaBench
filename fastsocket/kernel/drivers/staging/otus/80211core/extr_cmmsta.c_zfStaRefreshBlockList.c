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
typedef  size_t u16_t ;
struct TYPE_4__ {TYPE_2__* blockingApList; } ;
struct TYPE_6__ {TYPE_1__ sta; } ;
struct TYPE_5__ {scalar_t__ weight; } ;

/* Variables and functions */
 size_t ZM_MAX_BLOCKING_AP_LIST_SIZE ; 
 TYPE_3__* wd ; 
 int /*<<< orphan*/  zmw_declare_for_critical_section () ; 
 int /*<<< orphan*/  zmw_enter_critical_section (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zmw_get_wlan_dev (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zmw_leave_critical_section (int /*<<< orphan*/ *) ; 

void zfStaRefreshBlockList(zdev_t* dev, u16_t flushFlag)
{
    u16_t i;
    zmw_get_wlan_dev(dev);
    zmw_declare_for_critical_section();

    zmw_enter_critical_section(dev);
    for (i=0; i<ZM_MAX_BLOCKING_AP_LIST_SIZE; i++)
    {
        if (wd->sta.blockingApList[i].weight != 0)
        {
            if (flushFlag != 0)
            {
                wd->sta.blockingApList[i].weight = 0;
            }
            else
            {
                wd->sta.blockingApList[i].weight--;
            }
        }
    }
    zmw_leave_critical_section(dev);
    return;
}