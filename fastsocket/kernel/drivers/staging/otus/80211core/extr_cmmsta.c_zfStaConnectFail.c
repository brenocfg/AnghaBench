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
typedef  int /*<<< orphan*/  u8_t ;
typedef  int /*<<< orphan*/  u16_t ;
struct TYPE_3__ {scalar_t__ bAutoReconnect; } ;
struct TYPE_4__ {TYPE_1__ sta; int /*<<< orphan*/  (* zfcbConnectNotify ) (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  ZM_SCAN_MGR_SCAN_INTERNAL ; 
 int /*<<< orphan*/  ZM_STA_STATE_DISCONNECT ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_2__* wd ; 
 int /*<<< orphan*/  zfChangeAdapterState (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zfScanMgrScanStart (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zfScanMgrScanStop (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zfStaPutApIntoBlockingList (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zm_debug_msg0 (char*) ; 
 int /*<<< orphan*/  zmw_get_wlan_dev (int /*<<< orphan*/ *) ; 

void zfStaConnectFail(zdev_t* dev, u16_t reason, u16_t* bssid, u8_t weight)
{
    zmw_get_wlan_dev(dev);

    /* Change internal state */
    zfChangeAdapterState(dev, ZM_STA_STATE_DISCONNECT);

    /* Improve WEP/TKIP performace with HT AP, detail information please look bug#32495 */
    //zfHpSetTTSIFSTime(dev, 0x8);

    /* Notify wrapper of connection status changes */
    if (wd->zfcbConnectNotify != NULL)
    {
        wd->zfcbConnectNotify(dev, reason, bssid);
    }

    /* Put AP into internal blocking list */
    zfStaPutApIntoBlockingList(dev, (u8_t *)bssid, weight);

    /* Issue another SCAN */
    if ( wd->sta.bAutoReconnect )
    {
        zm_debug_msg0("Start internal scan...");
        zfScanMgrScanStop(dev, ZM_SCAN_MGR_SCAN_INTERNAL);
        zfScanMgrScanStart(dev, ZM_SCAN_MGR_SCAN_INTERNAL);
    }
}