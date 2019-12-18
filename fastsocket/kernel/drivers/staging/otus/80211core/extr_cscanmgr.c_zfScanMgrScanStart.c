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
struct TYPE_4__ {int* scanReqs; scalar_t__ currScanType; int scanStartDelay; } ;
struct TYPE_5__ {TYPE_1__ scanMgr; void* bScheduleScan; void* bChannelScan; } ;
struct TYPE_6__ {TYPE_2__ sta; } ;

/* Variables and functions */
 void* FALSE ; 
 void* TRUE ; 
 int /*<<< orphan*/  ZM_EVENT_IN_SCAN ; 
 int /*<<< orphan*/  ZM_EVENT_SCAN ; 
 int /*<<< orphan*/  ZM_EVENT_TIMEOUT_SCAN ; 
 scalar_t__ ZM_SCAN_MGR_SCAN_EXTERNAL ; 
 scalar_t__ ZM_SCAN_MGR_SCAN_INTERNAL ; 
 scalar_t__ ZM_SCAN_MGR_SCAN_NONE ; 
 TYPE_3__* wd ; 
 int /*<<< orphan*/  zfPowerSavingMgrIsSleeping (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zfSendNullData (int /*<<< orphan*/ *,int) ; 
 scalar_t__ zfStaIsConnected (int /*<<< orphan*/ *) ; 
 scalar_t__ zfStaIsConnecting (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zfTimerCancel (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zfTimerSchedule (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  zm_debug_msg0 (char*) ; 
 int /*<<< orphan*/  zm_debug_msg1 (char*,scalar_t__) ; 
 int /*<<< orphan*/  zmw_declare_for_critical_section () ; 
 int /*<<< orphan*/  zmw_enter_critical_section (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zmw_get_wlan_dev (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zmw_leave_critical_section (int /*<<< orphan*/ *) ; 

u8_t zfScanMgrScanStart(zdev_t* dev, u8_t scanType)
{
    u8_t i;

    zmw_get_wlan_dev(dev);

    zm_debug_msg1("scanType = ", scanType);

    zmw_declare_for_critical_section();

    if ( scanType != ZM_SCAN_MGR_SCAN_INTERNAL &&
         scanType != ZM_SCAN_MGR_SCAN_EXTERNAL )
    {
        zm_debug_msg0("unknown scanType");
        return 1;
    }
    else if (zfStaIsConnecting(dev))
    {
        zm_debug_msg0("reject scan request due to connecting");
        return 1;
    }

    i = scanType - 1;

    zmw_enter_critical_section(dev);

    if ( wd->sta.scanMgr.scanReqs[i] == 1 )
    {
        zm_debug_msg1("scan rescheduled", scanType);
        goto scan_done;
    }

    wd->sta.scanMgr.scanReqs[i] = 1;
    zm_debug_msg1("scan scheduled: ", scanType);

    // If there's no scan pending, we do the scan right away.
    // If there's an internal scan and the new scan request is external one,
    // we will restart the scan.
    if ( wd->sta.scanMgr.currScanType == ZM_SCAN_MGR_SCAN_NONE )
    {
        goto schedule_scan;
    }
    else if ( wd->sta.scanMgr.currScanType == ZM_SCAN_MGR_SCAN_INTERNAL &&
              scanType == ZM_SCAN_MGR_SCAN_EXTERNAL )
    {
        // Stop the internal scan & schedule external scan first
        zfTimerCancel(dev, ZM_EVENT_SCAN);

        /* Fix for WHQL sendrecv => we do not apply delay time in which the device
           stop transmitting packet when we already connect to some AP  */
        wd->sta.bScheduleScan = FALSE;

        zfTimerCancel(dev, ZM_EVENT_TIMEOUT_SCAN);
        zfTimerCancel(dev, ZM_EVENT_IN_SCAN);

        wd->sta.bChannelScan = FALSE;
        goto schedule_scan;
    }
    else
    {
        zm_debug_msg0("Scan is busy...waiting later to start\n");
    }

    zmw_leave_critical_section(dev);
    return 0;

scan_done:
    zmw_leave_critical_section(dev);
    return 1;

schedule_scan:

    wd->sta.bScheduleScan = TRUE;

    zfTimerSchedule(dev, ZM_EVENT_SCAN, wd->sta.scanMgr.scanStartDelay);
    wd->sta.scanMgr.scanStartDelay = 3;
    //wd->sta.scanMgr.scanStartDelay = 0;
    wd->sta.scanMgr.currScanType = scanType;
    zmw_leave_critical_section(dev);

    if ((zfStaIsConnected(dev)) && (!zfPowerSavingMgrIsSleeping(dev)))
    {
        zfSendNullData(dev, 1);
    }
    return 0;
}