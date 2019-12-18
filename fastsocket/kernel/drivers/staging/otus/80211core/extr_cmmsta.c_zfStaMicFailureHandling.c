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
typedef  int /*<<< orphan*/  zbuf_t ;
typedef  int u8_t ;
struct TYPE_3__ {scalar_t__ wpaState; int cmMicFailureCount; int /*<<< orphan*/  bssid; int /*<<< orphan*/  ssidLen; int /*<<< orphan*/  ssid; int /*<<< orphan*/  cmDisallowSsid; int /*<<< orphan*/  cmDisallowSsidLength; } ;
struct TYPE_4__ {TYPE_1__ sta; int /*<<< orphan*/  (* zfcbMicFailureNotify ) (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  ZM_EVENT_CM_DISCONNECT ; 
 int /*<<< orphan*/  ZM_EVENT_CM_TIMER ; 
 int /*<<< orphan*/  ZM_MIC_GROUP_ERROR ; 
 int /*<<< orphan*/  ZM_MIC_PAIRWISE_ERROR ; 
 scalar_t__ ZM_STA_WPA_STATE_PK_OK ; 
 scalar_t__ ZM_TICK_CM_DISCONNECT ; 
 scalar_t__ ZM_TICK_CM_DISCONNECT_OFFSET ; 
 scalar_t__ ZM_TICK_CM_TIMEOUT ; 
 scalar_t__ ZM_TICK_CM_TIMEOUT_OFFSET ; 
 int /*<<< orphan*/  ZM_WLAN_HEADER_A1_OFFSET ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_2__* wd ; 
 int /*<<< orphan*/  zfMemoryCopy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zfTimerCancel (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zfTimerSchedule (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  zm_debug_msg0 (char*) ; 
 int /*<<< orphan*/  zmw_declare_for_critical_section () ; 
 int /*<<< orphan*/  zmw_enter_critical_section (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zmw_get_wlan_dev (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zmw_leave_critical_section (int /*<<< orphan*/ *) ; 
 int zmw_rx_buf_readb (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void zfStaMicFailureHandling(zdev_t* dev, zbuf_t* buf)
{
    u8_t   da0;
    u8_t   micNotify = 1;

    zmw_get_wlan_dev(dev);

    zmw_declare_for_critical_section();

    if ( wd->sta.wpaState <  ZM_STA_WPA_STATE_PK_OK )
    {
        return;
    }

    zmw_enter_critical_section(dev);

    wd->sta.cmMicFailureCount++;

    if ( wd->sta.cmMicFailureCount == 1 )
    {
        zm_debug_msg0("get the first MIC failure");
        //zfTimerSchedule(dev, ZM_EVENT_CM_TIMER, ZM_TICK_CM_TIMEOUT);

        /* Timer Resolution on WinXP is 15/16 ms  */
        /* Decrease Time offset for <XP> Counter Measure */
        zfTimerSchedule(dev, ZM_EVENT_CM_TIMER, ZM_TICK_CM_TIMEOUT - ZM_TICK_CM_TIMEOUT_OFFSET);
    }
    else if ( wd->sta.cmMicFailureCount == 2 )
    {
        zm_debug_msg0("get the second MIC failure");
        /* reserve 2 second for OS to send MIC failure report to AP */
        wd->sta.cmDisallowSsidLength = wd->sta.ssidLen;
        zfMemoryCopy(wd->sta.cmDisallowSsid, wd->sta.ssid, wd->sta.ssidLen);
        //wd->sta.cmMicFailureCount = 0;
        zfTimerCancel(dev, ZM_EVENT_CM_TIMER);
        //zfTimerSchedule(dev, ZM_EVENT_CM_DISCONNECT, ZM_TICK_CM_DISCONNECT);

        /* Timer Resolution on WinXP is 15/16 ms  */
        /* Decrease Time offset for <XP> Counter Measure */
        zfTimerSchedule(dev, ZM_EVENT_CM_DISCONNECT, ZM_TICK_CM_DISCONNECT - ZM_TICK_CM_DISCONNECT_OFFSET);
    }
    else
    {
        micNotify = 0;
    }

    zmw_leave_critical_section(dev);

    if (micNotify == 1)
    {
        da0 = zmw_rx_buf_readb(dev, buf, ZM_WLAN_HEADER_A1_OFFSET);
        if ( da0 & 0x01 )
        {
            if (wd->zfcbMicFailureNotify != NULL)
            {
                wd->zfcbMicFailureNotify(dev, wd->sta.bssid, ZM_MIC_GROUP_ERROR);
            }
        }
        else
        {
            if (wd->zfcbMicFailureNotify != NULL)
            {
                wd->zfcbMicFailureNotify(dev, wd->sta.bssid, ZM_MIC_PAIRWISE_ERROR);
            }
        }
    }
}