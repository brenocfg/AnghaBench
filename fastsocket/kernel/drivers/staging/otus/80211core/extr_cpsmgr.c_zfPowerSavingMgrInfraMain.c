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
struct TYPE_4__ {int state; } ;
struct TYPE_5__ {TYPE_1__ psMgr; } ;
struct TYPE_6__ {TYPE_2__ sta; } ;

/* Variables and functions */
#define  ZM_PS_MSG_STATE_ACTIVE 131 
#define  ZM_PS_MSG_STATE_SLEEP 130 
#define  ZM_PS_MSG_STATE_T1 129 
#define  ZM_PS_MSG_STATE_T2 128 
 TYPE_3__* wd ; 
 int /*<<< orphan*/  zfPowerSavingMgrOnHandleT1 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zfPowerSavingMgrOnHandleT2 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zfPowerSavingMgrSleepIfIdle (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zmw_get_wlan_dev (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void zfPowerSavingMgrInfraMain(zdev_t* dev)
{
    zmw_get_wlan_dev(dev);

    switch(wd->sta.psMgr.state)
    {
        case ZM_PS_MSG_STATE_ACTIVE:
            zfPowerSavingMgrSleepIfIdle(dev);
            break;

        case ZM_PS_MSG_STATE_SLEEP:
            break;

        case ZM_PS_MSG_STATE_T1:
            zfPowerSavingMgrOnHandleT1(dev);
            break;

        case ZM_PS_MSG_STATE_T2:
            zfPowerSavingMgrOnHandleT2(dev);
            break;
    }
}