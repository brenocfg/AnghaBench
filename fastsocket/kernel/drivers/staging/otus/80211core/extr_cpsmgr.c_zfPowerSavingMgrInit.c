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
struct TYPE_4__ {int maxSleepPeriods; scalar_t__ sleepAllowedtick; scalar_t__ ticks; scalar_t__ isSleepAllowed; int /*<<< orphan*/  state; } ;
struct TYPE_5__ {TYPE_1__ psMgr; int /*<<< orphan*/  powerSaveMode; } ;
struct TYPE_6__ {TYPE_2__ sta; } ;

/* Variables and functions */
 int /*<<< orphan*/  ZM_PS_MSG_STATE_ACTIVE ; 
 int /*<<< orphan*/  ZM_STA_PS_NONE ; 
 TYPE_3__* wd ; 
 int /*<<< orphan*/  zmw_get_wlan_dev (int /*<<< orphan*/ *) ; 

void zfPowerSavingMgrInit(zdev_t* dev)
{
    zmw_get_wlan_dev(dev);

    wd->sta.powerSaveMode = ZM_STA_PS_NONE;
    wd->sta.psMgr.state = ZM_PS_MSG_STATE_ACTIVE;
    wd->sta.psMgr.isSleepAllowed = 0;
    wd->sta.psMgr.maxSleepPeriods = 1;
    wd->sta.psMgr.ticks = 0;
    wd->sta.psMgr.sleepAllowedtick = 0;
}