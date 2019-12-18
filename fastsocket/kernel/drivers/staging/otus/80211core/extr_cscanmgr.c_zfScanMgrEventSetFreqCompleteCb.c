#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zdev_t ;
struct TYPE_3__ {int /*<<< orphan*/  activescanTickPerChannel; int /*<<< orphan*/  passiveScanTickPerChannel; scalar_t__ bPassiveScan; } ;
struct TYPE_4__ {TYPE_1__ sta; } ;

/* Variables and functions */
 int /*<<< orphan*/  ZM_EVENT_IN_SCAN ; 
 int /*<<< orphan*/  ZM_EVENT_TIMEOUT_SCAN ; 
 int /*<<< orphan*/  ZM_TICK_IN_SCAN ; 
 TYPE_2__* wd ; 
 int /*<<< orphan*/  zfScanSendProbeRequest (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zfTimerSchedule (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zmw_declare_for_critical_section () ; 
 int /*<<< orphan*/  zmw_enter_critical_section (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zmw_get_wlan_dev (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zmw_leave_critical_section (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void zfScanMgrEventSetFreqCompleteCb(zdev_t* dev)
{
    zmw_get_wlan_dev(dev);

    zmw_declare_for_critical_section();

//printk("zfScanMgrEventSetFreqCompleteCb #1\n");

    zmw_enter_critical_section(dev);
    zfTimerSchedule(dev, ZM_EVENT_IN_SCAN, ZM_TICK_IN_SCAN);
    if (wd->sta.bPassiveScan)
    {
        zfTimerSchedule(dev, ZM_EVENT_TIMEOUT_SCAN, wd->sta.passiveScanTickPerChannel);
    }
    else
    {
        zfTimerSchedule(dev, ZM_EVENT_TIMEOUT_SCAN, wd->sta.activescanTickPerChannel);
    }
    zmw_leave_critical_section(dev);

    zfScanSendProbeRequest(dev);
}