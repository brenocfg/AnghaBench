#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zdev_t ;
typedef  int u8_t ;
typedef  int u16_t ;
struct TYPE_6__ {int currScanType; int scanStartDelay; scalar_t__* scanReqs; } ;
struct TYPE_7__ {int scanFrequency; scalar_t__ bChannelScan; int ibssSiteSurveyStatus; scalar_t__ rifsState; int currentFrequency; int /*<<< orphan*/  HT2040; int /*<<< orphan*/  EnableHT; scalar_t__ ibssReceiveBeaconCount; TYPE_2__ scanMgr; int /*<<< orphan*/  bPassiveScan; } ;
struct TYPE_5__ {int allowChannelCnt; } ;
struct TYPE_8__ {TYPE_3__ sta; int /*<<< orphan*/  (* zfcbScanNotify ) (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ;scalar_t__ tickIbssReceiveBeacon; int /*<<< orphan*/  ExtOffset; int /*<<< orphan*/  BandWidth40; int /*<<< orphan*/  frequency; TYPE_1__ regulationTable; } ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  ZM_EVENT_IN_SCAN ; 
 int /*<<< orphan*/  ZM_EVENT_TIMEOUT_SCAN ; 
 scalar_t__ ZM_RIFS_STATE_DETECTED ; 
#define  ZM_SCAN_MGR_SCAN_EXTERNAL 129 
#define  ZM_SCAN_MGR_SCAN_INTERNAL 128 
 int ZM_SCAN_MGR_SCAN_NONE ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_4__* wd ; 
 int zfChGetLastChannel (int /*<<< orphan*/ *,int*) ; 
 int zfChGetNextChannel (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zfCoreSetFrequencyEx (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zfCoreSetFrequencyV2 (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zfHpEnableRifs (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zfHpFinishSiteSurvey (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  zfScanMgrEventScanCompleteCb ; 
 int /*<<< orphan*/  zfScanMgrEventSetFreqCompleteCb ; 
 scalar_t__ zfStaIsConnected (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zfStaReconnect (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zfTimerCancel (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zm_assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zm_debug_msg0 (char*) ; 
 int /*<<< orphan*/  zm_debug_msg1 (char*,int) ; 
 int /*<<< orphan*/  zmw_declare_for_critical_section () ; 
 int /*<<< orphan*/  zmw_enter_critical_section (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zmw_get_wlan_dev (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zmw_leave_critical_section (int /*<<< orphan*/ *) ; 

u8_t zfScanMgrScanEventTimeout(zdev_t* dev)
{
    u16_t   nextScanFrequency = 0;
    u8_t    temp;

    zmw_get_wlan_dev(dev);

    zmw_declare_for_critical_section();

    zmw_enter_critical_section(dev);
    if ( wd->sta.scanFrequency == 0 )
    {
        zmw_leave_critical_section(dev);
        return -1;
    }

    nextScanFrequency = zfChGetNextChannel(dev, wd->sta.scanFrequency,
                                           &wd->sta.bPassiveScan);

    if ( (nextScanFrequency == 0xffff)
         || (wd->sta.scanFrequency == zfChGetLastChannel(dev, &temp)) )
    {
        u8_t currScanType;
        u8_t isExternalScan = 0;
        u8_t isInternalScan = 0;

        //zm_debug_msg1("end scan = ", KeQueryInterruptTime());
        wd->sta.scanFrequency = 0;

        zm_debug_msg1("scan 1 type: ", wd->sta.scanMgr.currScanType);
        zm_debug_msg1("scan channel count = ", wd->regulationTable.allowChannelCnt);

        //zfBssInfoRefresh(dev);
        zfTimerCancel(dev, ZM_EVENT_TIMEOUT_SCAN);

        if ( wd->sta.bChannelScan == FALSE )
        {
            zm_debug_msg0("WOW!! scan is cancelled\n");
            zmw_leave_critical_section(dev);
            goto report_scan_result;
        }


        currScanType = wd->sta.scanMgr.currScanType;
        switch(currScanType)
        {
            case ZM_SCAN_MGR_SCAN_EXTERNAL:
                isExternalScan = 1;

                if ( wd->sta.scanMgr.scanReqs[ZM_SCAN_MGR_SCAN_INTERNAL - 1] )
                {
                    wd->sta.scanMgr.scanReqs[ZM_SCAN_MGR_SCAN_INTERNAL - 1] = 0;
                    isInternalScan = 1;
                }

                break;

            case ZM_SCAN_MGR_SCAN_INTERNAL:
                isInternalScan = 1;

                if ( wd->sta.scanMgr.scanReqs[ZM_SCAN_MGR_SCAN_EXTERNAL - 1] )
                {
                    // Because the external scan should pre-empts internal scan.
                    // So this shall not be happened!!
                    zm_assert(0);
                }

                break;

            default:
                zm_assert(0);
                break;
        }

        wd->sta.scanMgr.scanReqs[currScanType - 1] = 0;
        wd->sta.scanMgr.scanStartDelay = 100;
        wd->sta.scanMgr.currScanType = ZM_SCAN_MGR_SCAN_NONE;
        zmw_leave_critical_section(dev);

        //Set channel according to AP's configuration
        zfCoreSetFrequencyEx(dev, wd->frequency, wd->BandWidth40,
                wd->ExtOffset, zfScanMgrEventScanCompleteCb);

        wd->sta.bChannelScan = FALSE;

        #if 1
        if (zfStaIsConnected(dev))
        { // Finish site survey, reset the variable to detect using wrong frequency !
            zfHpFinishSiteSurvey(dev, 1);
            zmw_enter_critical_section(dev);
            wd->sta.ibssSiteSurveyStatus = 2;
            wd->tickIbssReceiveBeacon = 0;
            wd->sta.ibssReceiveBeaconCount = 0;
            zmw_leave_critical_section(dev);

            /* #5 Re-enable RIFS function after the site survey ! */
            /* This is because switch band will reset the BB register to initial value */
            if( wd->sta.rifsState == ZM_RIFS_STATE_DETECTED )
            {
                zfHpEnableRifs(dev, ((wd->sta.currentFrequency<3000)?1:0), wd->sta.EnableHT, wd->sta.HT2040);
            }
        }
        else
        {
            zfHpFinishSiteSurvey(dev, 0);
            zmw_enter_critical_section(dev);
            wd->sta.ibssSiteSurveyStatus = 0;
            zmw_leave_critical_section(dev);
        }
        #endif

report_scan_result:
        /* avoid lose receive packet when site survey */
        //if ((zfStaIsConnected(dev)) && (!zfPowerSavingMgrIsSleeping(dev)))
        //{
        //    zfSendNullData(dev, 0);
        //}

        if ( isExternalScan )//Quickly reboot
        {
            if (wd->zfcbScanNotify != NULL)
            {
                wd->zfcbScanNotify(dev, NULL);
            }
        }

        if ( isInternalScan )
        {
            //wd->sta.InternalScanReq = 0;
            zfStaReconnect(dev);
        }

        return 0;
    }
    else
    {
        wd->sta.scanFrequency = nextScanFrequency;

        //zmw_enter_critical_section(dev);
        zfTimerCancel(dev, ZM_EVENT_IN_SCAN);
        zmw_leave_critical_section(dev);

        zm_debug_msg0("scan 2");
        zfCoreSetFrequencyV2(dev, wd->sta.scanFrequency, zfScanMgrEventSetFreqCompleteCb);

        return 1;
    }
}