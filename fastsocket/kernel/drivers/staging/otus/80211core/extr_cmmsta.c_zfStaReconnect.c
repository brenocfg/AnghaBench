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
struct TYPE_5__ {scalar_t__ ssidLen; scalar_t__* ssid; scalar_t__ bChannelScan; } ;
struct TYPE_4__ {scalar_t__ ssidLen; } ;
struct TYPE_6__ {scalar_t__ wlanMode; TYPE_2__ sta; TYPE_1__ ws; } ;

/* Variables and functions */
 scalar_t__ ZM_MODE_IBSS ; 
 scalar_t__ ZM_MODE_INFRASTRUCTURE ; 
 TYPE_3__* wd ; 
 int /*<<< orphan*/  zfFlushVtxq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zfScanMgrScanAck (int /*<<< orphan*/ *) ; 
 scalar_t__ zfStaIsConnected (int /*<<< orphan*/ *) ; 
 scalar_t__ zfStaIsConnecting (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zfWlanEnable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zm_debug_msg0 (char*) ; 
 int /*<<< orphan*/  zmw_declare_for_critical_section () ; 
 int /*<<< orphan*/  zmw_enter_critical_section (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zmw_get_wlan_dev (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zmw_leave_critical_section (int /*<<< orphan*/ *) ; 

void zfStaReconnect(zdev_t* dev)
{
    zmw_get_wlan_dev(dev);
    zmw_declare_for_critical_section();

    if ( wd->wlanMode != ZM_MODE_INFRASTRUCTURE &&
         wd->wlanMode != ZM_MODE_IBSS )
    {
        return;
    }

    if ( (zfStaIsConnected(dev))||(zfStaIsConnecting(dev)) )
    {
        return;
    }

    if ( wd->sta.bChannelScan )
    {
        return;
    }

    /* Recover zero SSID length  */
    if ( (wd->wlanMode == ZM_MODE_INFRASTRUCTURE) && (wd->ws.ssidLen == 0))
    {
        zm_debug_msg0("zfStaReconnect: NOT Support!! Set SSID to any BSS");
        /* ANY BSS */
        zmw_enter_critical_section(dev);
        wd->sta.ssid[0] = 0;
        wd->sta.ssidLen = 0;
        zmw_leave_critical_section(dev);
    }

    // RAY: To ensure no TX pending before re-connecting
    zfFlushVtxq(dev);
    zfWlanEnable(dev);
    zfScanMgrScanAck(dev);
}