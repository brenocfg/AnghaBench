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
struct TYPE_4__ {scalar_t__ currScanType; } ;
struct TYPE_5__ {int ibssSiteSurveyStatus; int /*<<< orphan*/  scanFrequency; int /*<<< orphan*/  bPassiveScan; int /*<<< orphan*/  bScheduleScan; scalar_t__ bChannelScan; TYPE_1__ scanMgr; } ;
struct TYPE_6__ {TYPE_2__ sta; } ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  ZM_EVENT_IN_SCAN ; 
 int /*<<< orphan*/  ZM_EVENT_TIMEOUT_SCAN ; 
 scalar_t__ ZM_SCAN_MGR_SCAN_NONE ; 
 TYPE_3__* wd ; 
 int /*<<< orphan*/  zfBssInfoRefresh (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zfChGetFirstChannel (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zfCoreSetFrequencyV2 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zfHpBeginSiteSurvey (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  zfPowerSavingMgrWakeup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zfScanMgrEventSetFreqCompleteCb ; 
 scalar_t__ zfStaIsConnected (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zfTimerCancel (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zm_debug_msg0 (char*) ; 
 int /*<<< orphan*/  zmw_declare_for_critical_section () ; 
 int /*<<< orphan*/  zmw_enter_critical_section (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zmw_get_wlan_dev (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zmw_leave_critical_section (int /*<<< orphan*/ *) ; 

void zfScanMgrScanEventStart(zdev_t* dev)
{
    zmw_get_wlan_dev(dev);

    zmw_declare_for_critical_section();

    if ( wd->sta.bChannelScan )
    {
        return;
    }

    zfPowerSavingMgrWakeup(dev);

    zmw_enter_critical_section(dev);

    if ( wd->sta.scanMgr.currScanType == ZM_SCAN_MGR_SCAN_NONE )
    {
        goto no_scan;
    }

    //zfBssInfoRefresh(dev);
    zfBssInfoRefresh(dev, 0);
    wd->sta.bChannelScan = TRUE;
    wd->sta.bScheduleScan = FALSE;
    zfTimerCancel(dev, ZM_EVENT_IN_SCAN);
    zfTimerCancel(dev, ZM_EVENT_TIMEOUT_SCAN);

    //zm_debug_msg1("start scan = ", KeQueryInterruptTime());
    wd->sta.scanFrequency = zfChGetFirstChannel(dev, &wd->sta.bPassiveScan);
    zmw_leave_critical_section(dev);

    /* avoid lose receive packet when site survey */
    //if ((zfStaIsConnected(dev)) && (!zfPowerSavingMgrIsSleeping(dev)))
    //{
    //    zfSendNullData(dev, 1);
    //}
//    zm_debug_msg0("scan 0");
//    zfCoreSetFrequencyV2(dev, wd->sta.scanFrequency, zfScanMgrEventSetFreqCompleteCb);

    #if 1
    if (zfStaIsConnected(dev))
    {// If doing site survey !
        zfHpBeginSiteSurvey(dev, 1);
        zmw_enter_critical_section(dev);
        wd->sta.ibssSiteSurveyStatus = 1;
        zmw_leave_critical_section(dev);
    }
    else
    {
        zfHpBeginSiteSurvey(dev, 0);
        zmw_enter_critical_section(dev);
        wd->sta.ibssSiteSurveyStatus = 0;
        zmw_leave_critical_section(dev);
    }
    #endif

    zm_debug_msg0("scan 0");
    zfCoreSetFrequencyV2(dev, wd->sta.scanFrequency, zfScanMgrEventSetFreqCompleteCb);

    return;

no_scan:
    zmw_leave_critical_section(dev);
    return;
}