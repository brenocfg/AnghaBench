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
typedef  size_t u8_t ;
struct zsBssInfo {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/ * tail; int /*<<< orphan*/ * head; scalar_t__ bssCount; } ;
struct TYPE_5__ {size_t bssInfoFreeCount; int /*<<< orphan*/ * bssInfoArray; scalar_t__ bssInfoArrayTail; scalar_t__ bssInfoArrayHead; TYPE_1__ bssList; } ;
struct TYPE_6__ {TYPE_2__ sta; } ;

/* Variables and functions */
 size_t ZM_MAX_BSS ; 
 TYPE_3__* wd ; 
 int /*<<< orphan*/  zfwMemAllocate (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  zmw_declare_for_critical_section () ; 
 int /*<<< orphan*/  zmw_enter_critical_section (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zmw_get_wlan_dev (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zmw_leave_critical_section (int /*<<< orphan*/ *) ; 

void zfBssInfoCreate(zdev_t* dev)
{
    u8_t   i;

    zmw_get_wlan_dev(dev);

    zmw_declare_for_critical_section();

    zmw_enter_critical_section(dev);

    wd->sta.bssList.bssCount = 0;
    wd->sta.bssList.head = NULL;
    wd->sta.bssList.tail = NULL;
    wd->sta.bssInfoArrayHead = 0;
    wd->sta.bssInfoArrayTail = 0;
    wd->sta.bssInfoFreeCount = ZM_MAX_BSS;

    for( i=0; i< ZM_MAX_BSS; i++ )
    {
        //wd->sta.bssInfoArray[i] = &(wd->sta.bssInfoPool[i]);
        wd->sta.bssInfoArray[i] = zfwMemAllocate(dev, sizeof(struct zsBssInfo));

    }

    zmw_leave_critical_section(dev);
}