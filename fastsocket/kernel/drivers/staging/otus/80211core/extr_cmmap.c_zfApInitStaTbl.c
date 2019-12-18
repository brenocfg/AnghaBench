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
struct TYPE_5__ {TYPE_1__* staTable; } ;
struct TYPE_6__ {TYPE_2__ ap; } ;
struct TYPE_4__ {int /*<<< orphan*/  encryMode; scalar_t__ vap; scalar_t__ time; scalar_t__* addr; scalar_t__ state; scalar_t__ valid; } ;

/* Variables and functions */
 size_t ZM_MAX_STA_SUPPORT ; 
 int /*<<< orphan*/  ZM_NO_WEP ; 
 TYPE_3__* wd ; 
 int /*<<< orphan*/  zmw_get_wlan_dev (int /*<<< orphan*/ *) ; 

void zfApInitStaTbl(zdev_t* dev)
{
    u16_t i;

    zmw_get_wlan_dev(dev);

    for (i=0; i<ZM_MAX_STA_SUPPORT; i++)
    {
        wd->ap.staTable[i].valid = 0;
        wd->ap.staTable[i].state = 0;
        wd->ap.staTable[i].addr[0] = 0;
        wd->ap.staTable[i].addr[1] = 0;
        wd->ap.staTable[i].addr[2] = 0;
        wd->ap.staTable[i].time = 0;
        wd->ap.staTable[i].vap = 0;
        wd->ap.staTable[i].encryMode = ZM_NO_WEP;
    }
    return;
}