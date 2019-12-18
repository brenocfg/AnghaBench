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
typedef  size_t u8_t ;
typedef  int u16_t ;
struct TYPE_3__ {int /*<<< orphan*/  bssid; int /*<<< orphan*/  bAutoReconnect; int /*<<< orphan*/  cmDisallowSsidLength; int /*<<< orphan*/  cmMicFailureCount; } ;
struct TYPE_4__ {int addbaCount; int TKIP_Group_KeyChanging; TYPE_1__ sta; int /*<<< orphan*/  addbaComplete; int /*<<< orphan*/  (* zfcbConnectNotify ) (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 size_t FALSE ; 
 size_t TRUE ; 
#define  ZM_EVENT_CM_BLOCK_TIMER 137 
#define  ZM_EVENT_CM_DISCONNECT 136 
#define  ZM_EVENT_CM_TIMER 135 
#define  ZM_EVENT_IBSS_MONITOR 134 
#define  ZM_EVENT_IN_SCAN 133 
#define  ZM_EVENT_SCAN 132 
#define  ZM_EVENT_SKIP_COUNTERMEASURE 131 
#define  ZM_EVENT_TIMEOUT_ADDBA 130 
#define  ZM_EVENT_TIMEOUT_PERFORMANCE 129 
#define  ZM_EVENT_TIMEOUT_SCAN 128 
 int /*<<< orphan*/  ZM_LV_0 ; 
 int /*<<< orphan*/  ZM_SCAN_MGR_SCAN_INTERNAL ; 
 int /*<<< orphan*/  ZM_STATUS_MEDIA_DISCONNECT_MIC_FAIL ; 
 int /*<<< orphan*/  ZM_STA_STATE_DISCONNECT ; 
 int ZM_TICK_CM_BLOCK_TIMEOUT ; 
 int ZM_TICK_CM_BLOCK_TIMEOUT_OFFSET ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_2__* wd ; 
 int /*<<< orphan*/  zfAggSendAddbaRequest (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zfChangeAdapterState (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zfHpResetKeyCache (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zfScanMgrScanEventRetry (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zfScanMgrScanEventStart (int /*<<< orphan*/ *) ; 
 size_t zfScanMgrScanEventTimeout (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zfScanMgrScanStart (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zfScanMgrScanStop (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zfStaIbssMonitoring (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zfTimerCancel (int /*<<< orphan*/ *,int const) ; 
 int /*<<< orphan*/  zfTimerSchedule (int /*<<< orphan*/ *,int const,int) ; 
 int /*<<< orphan*/  zfZeroMemory (size_t*,int) ; 
 int /*<<< orphan*/  zfiPerformanceRefresh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zm_debug_msg0 (char*) ; 
 int /*<<< orphan*/  zm_msg0_mm (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  zmw_declare_for_critical_section () ; 
 int /*<<< orphan*/  zmw_enter_critical_section (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zmw_get_wlan_dev (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zmw_leave_critical_section (int /*<<< orphan*/ *) ; 

void zfProcessEvent(zdev_t* dev, u16_t* eventArray, u8_t eventCount)
{
    u8_t i, j, bypass = FALSE;
    u16_t eventBypass[32];
    u8_t eventBypassCount = 0;

    zmw_get_wlan_dev(dev);

    zmw_declare_for_critical_section();

    zfZeroMemory((u8_t*) eventBypass, 64);

    for( i=0; i<eventCount; i++ )
    {
        for( j=0; j<eventBypassCount; j++ )
        {
            if ( eventBypass[j] == eventArray[i] )
            {
                bypass = TRUE;
                break;
            }
        }

        if ( bypass )
        {
            continue;
        }

        switch( eventArray[i] )
        {
            case ZM_EVENT_SCAN:
                {
                    zfScanMgrScanEventStart(dev);
                    eventBypass[eventBypassCount++] = ZM_EVENT_IN_SCAN;
                    eventBypass[eventBypassCount++] = ZM_EVENT_TIMEOUT_SCAN;
                }
                break;

            case ZM_EVENT_TIMEOUT_SCAN:
                {
                    u8_t res;

                    res = zfScanMgrScanEventTimeout(dev);
                    if ( res == 0 )
                    {
                        eventBypass[eventBypassCount++] = ZM_EVENT_TIMEOUT_SCAN;
                    }
                    else if ( res == 1 )
                    {
                        eventBypass[eventBypassCount++] = ZM_EVENT_IN_SCAN;
                    }
                }
                break;

            case ZM_EVENT_IBSS_MONITOR:
                {
                    zfStaIbssMonitoring(dev, 0);
                }
                break;

            case ZM_EVENT_IN_SCAN:
                {
                    zfScanMgrScanEventRetry(dev);
                }
                break;

            case ZM_EVENT_CM_TIMER:
                {
                    zm_msg0_mm(ZM_LV_0, "ZM_EVENT_CM_TIMER");

                    wd->sta.cmMicFailureCount = 0;
                }
                break;

            case ZM_EVENT_CM_DISCONNECT:
                {
                    zm_msg0_mm(ZM_LV_0, "ZM_EVENT_CM_DISCONNECT");

                    zfChangeAdapterState(dev, ZM_STA_STATE_DISCONNECT);

                    zmw_enter_critical_section(dev);
                    //zfTimerSchedule(dev, ZM_EVENT_CM_BLOCK_TIMER,
                    //                ZM_TICK_CM_BLOCK_TIMEOUT);

                    /* Timer Resolution on WinXP is 15/16 ms  */
                    /* Decrease Time offset for <XP> Counter Measure */
                    zfTimerSchedule(dev, ZM_EVENT_CM_BLOCK_TIMER,
                                         ZM_TICK_CM_BLOCK_TIMEOUT - ZM_TICK_CM_BLOCK_TIMEOUT_OFFSET);

                    zmw_leave_critical_section(dev);
                    wd->sta.cmMicFailureCount = 0;
                    //zfiWlanDisable(dev);
                    zfHpResetKeyCache(dev);
                    if (wd->zfcbConnectNotify != NULL)
                    {
                        wd->zfcbConnectNotify(dev, ZM_STATUS_MEDIA_DISCONNECT_MIC_FAIL,
                             wd->sta.bssid);
                    }
                }
                break;

            case ZM_EVENT_CM_BLOCK_TIMER:
                {
                    zm_msg0_mm(ZM_LV_0, "ZM_EVENT_CM_BLOCK_TIMER");

                    //zmw_enter_critical_section(dev);
                    wd->sta.cmDisallowSsidLength = 0;
                    if ( wd->sta.bAutoReconnect )
                    {
                        zm_msg0_mm(ZM_LV_0, "ZM_EVENT_CM_BLOCK_TIMER:bAutoReconnect!=0");
                        zfScanMgrScanStop(dev, ZM_SCAN_MGR_SCAN_INTERNAL);
                        zfScanMgrScanStart(dev, ZM_SCAN_MGR_SCAN_INTERNAL);
                    }
                    //zmw_leave_critical_section(dev);
                }
                break;

            case ZM_EVENT_TIMEOUT_ADDBA:
                {
                    if (!wd->addbaComplete && (wd->addbaCount < 5))
                    {
                        zfAggSendAddbaRequest(dev, wd->sta.bssid, 0, 0);
                        wd->addbaCount++;
                        zfTimerSchedule(dev, ZM_EVENT_TIMEOUT_ADDBA, 100);
                    }
                    else
                    {
                        zfTimerCancel(dev, ZM_EVENT_TIMEOUT_ADDBA);
                    }
                }
                break;

            #ifdef ZM_ENABLE_PERFORMANCE_EVALUATION
            case ZM_EVENT_TIMEOUT_PERFORMANCE:
                {
                    zfiPerformanceRefresh(dev);
                }
                break;
            #endif
            case ZM_EVENT_SKIP_COUNTERMEASURE:
				//enable the Countermeasure
				{
					zm_debug_msg0("Countermeasure : Enable MIC Check ");
					wd->TKIP_Group_KeyChanging = 0x0;
				}
				break;

            default:
                break;
        }
    }
}