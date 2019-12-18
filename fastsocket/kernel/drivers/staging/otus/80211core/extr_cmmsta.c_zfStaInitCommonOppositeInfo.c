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
struct TYPE_5__ {TYPE_1__* oppositeInfo; int /*<<< orphan*/  oppositeCount; } ;
struct TYPE_6__ {TYPE_2__ sta; } ;
struct TYPE_4__ {int valid; int camIdx; int /*<<< orphan*/  wpaState; scalar_t__ pkInstalled; int /*<<< orphan*/  aliveCounter; } ;

/* Variables and functions */
 int /*<<< orphan*/  ZM_IBSS_PEER_ALIVE_COUNTER ; 
 int /*<<< orphan*/  ZM_STA_WPA_STATE_INIT ; 
 TYPE_3__* wd ; 
 int /*<<< orphan*/  zmw_get_wlan_dev (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void zfStaInitCommonOppositeInfo(zdev_t* dev, int i)
{
    zmw_get_wlan_dev(dev);

    /* set the default rate to the highest rate */
    wd->sta.oppositeInfo[i].valid = 1;
    wd->sta.oppositeInfo[i].aliveCounter = ZM_IBSS_PEER_ALIVE_COUNTER;
    wd->sta.oppositeCount++;

#ifdef ZM_ENABLE_IBSS_WPA2PSK
    /* Set parameters for new opposite peer station !!! */
    wd->sta.oppositeInfo[i].camIdx = 0xff;  // Not set key in this location
    wd->sta.oppositeInfo[i].pkInstalled = 0;
    wd->sta.oppositeInfo[i].wpaState = ZM_STA_WPA_STATE_INIT ;  // No encryption
#endif
}