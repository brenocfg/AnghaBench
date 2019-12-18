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
struct TYPE_4__ {scalar_t__ ticks; scalar_t__ maxSleepPeriods; } ;
struct TYPE_5__ {TYPE_1__ psMgr; } ;
struct TYPE_6__ {TYPE_2__ sta; } ;

/* Variables and functions */
 TYPE_3__* wd ; 
 int /*<<< orphan*/  zfHpPowerSaveSetMode (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zfPowerSavingMgrWakeup (int /*<<< orphan*/ *) ; 
 scalar_t__ zfStaIsDisconnect (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zmw_declare_for_critical_section () ; 
 int /*<<< orphan*/  zmw_enter_critical_section (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zmw_get_wlan_dev (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zmw_leave_critical_section (int /*<<< orphan*/ *) ; 

void zfPowerSavingMgrPreTBTTInterrupt(zdev_t *dev)
{
    zmw_get_wlan_dev(dev);
    zmw_declare_for_critical_section();

    /* disable TBTT interrupt when change from connection to disconnect */
    if (zfStaIsDisconnect(dev)) {
        zfHpPowerSaveSetMode(dev, 0, 0, 0);
        zfPowerSavingMgrWakeup(dev);
        return;
    }

    zmw_enter_critical_section(dev);
    wd->sta.psMgr.ticks++;

    if ( wd->sta.psMgr.ticks < wd->sta.psMgr.maxSleepPeriods )
    {
        zmw_leave_critical_section(dev);
        return;
    }
    else
    {
        wd->sta.psMgr.ticks = 0;
    }

    zmw_leave_critical_section(dev);

    zfPowerSavingMgrWakeup(dev);
}