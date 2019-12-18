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
typedef  scalar_t__ u8_t ;
typedef  int /*<<< orphan*/  u16_t ;
struct zsOppositeInfo {int dummy; } ;
struct TYPE_3__ {scalar_t__ currentAuthMode; scalar_t__ rifsState; scalar_t__ SWEncryptEnable; scalar_t__ oppositeInfo; scalar_t__ bSafeMode; scalar_t__ osRxFilter; scalar_t__ rifsCount; scalar_t__ rifsLikeFrameCnt; scalar_t__ leapEnabled; scalar_t__ connectTimeoutCount; scalar_t__ ibssWpa2Psk; scalar_t__ ibssBssIsCreator; scalar_t__ cmMicFailureCount; int /*<<< orphan*/  wpaState; int /*<<< orphan*/  wepStatus; int /*<<< orphan*/  encryMode; scalar_t__ InternalScanReq; scalar_t__ bAutoReconnect; scalar_t__ cmDisallowSsidLength; int /*<<< orphan*/  connectByReasso; int /*<<< orphan*/  connectState; int /*<<< orphan*/  bssid; } ;
struct TYPE_4__ {scalar_t__ wlanMode; TYPE_1__ sta; int /*<<< orphan*/  (* zfcbConnectNotify ) (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ ZM_AUTH_MODE_WPA2 ; 
 int /*<<< orphan*/  ZM_ENCRYPTION_WEP_DISABLED ; 
 int /*<<< orphan*/  ZM_EVENT_CM_BLOCK_TIMER ; 
 int /*<<< orphan*/  ZM_EVENT_CM_DISCONNECT ; 
 int /*<<< orphan*/  ZM_EVENT_IBSS_MONITOR ; 
 int ZM_MAX_OPPOSITE_COUNT ; 
 scalar_t__ ZM_MODE_INFRASTRUCTURE ; 
 scalar_t__ ZM_MODE_PSEUDO ; 
 int /*<<< orphan*/  ZM_NO_WEP ; 
 scalar_t__ ZM_RIFS_STATE_DETECTED ; 
 scalar_t__ ZM_RIFS_STATE_DETECTING ; 
 int /*<<< orphan*/  ZM_SCAN_MGR_SCAN_EXTERNAL ; 
 int /*<<< orphan*/  ZM_SCAN_MGR_SCAN_INTERNAL ; 
 int /*<<< orphan*/  ZM_STATUS_MEDIA_CONNECTION_RESET ; 
 int /*<<< orphan*/  ZM_STATUS_MEDIA_RESET ; 
 int /*<<< orphan*/  ZM_STA_CONN_STATE_NONE ; 
 int /*<<< orphan*/  ZM_STA_STATE_DISCONNECT ; 
 int /*<<< orphan*/  ZM_STA_WPA_STATE_INIT ; 
 int /*<<< orphan*/  ZM_WLAN_FRAME_TYPE_DEAUTH ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_2__* wd ; 
 int /*<<< orphan*/  zfAggRxFreeBuf (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zfAgingDefragList (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  zfChangeAdapterState (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zfFlushVtxq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zfHpDisableBeacon (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zfHpDisableRifs (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zfHpResetKeyCache (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zfScanMgrScanStop (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zfSendMmFrame (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zfStaDisableSWEncryption (int /*<<< orphan*/ *) ; 
 scalar_t__ zfStaIsConnected (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zfStaRefreshBlockList (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  zfTimerCancel (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zfZeroMemory (scalar_t__*,int) ; 
 int /*<<< orphan*/  zm_debug_msg0 (char*) ; 
 int /*<<< orphan*/  zmw_declare_for_critical_section () ; 
 int /*<<< orphan*/  zmw_enter_critical_section (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zmw_get_wlan_dev (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zmw_leave_critical_section (int /*<<< orphan*/ *) ; 

u16_t zfWlanReset(zdev_t *dev)
{
	u8_t isConnected;
	zmw_get_wlan_dev(dev);

	zmw_declare_for_critical_section();

	zm_debug_msg0("zfWlanReset");

	isConnected = zfStaIsConnected(dev);

	/* if ( wd->wlanMode != ZM_MODE_AP ) */
	{
		if ((wd->wlanMode == ZM_MODE_INFRASTRUCTURE) &&
		(wd->sta.currentAuthMode != ZM_AUTH_MODE_WPA2)) {
			/* send deauthentication frame */
			if (isConnected) {
				/* zfiWlanDeauth(dev, NULL, 0); */
				zfSendMmFrame(dev, ZM_WLAN_FRAME_TYPE_DEAUTH,
						wd->sta.bssid, 3, 0, 0);
				/* zmw_debug_msg0("send a Deauth frame!"); */
			}
		}
	}

	zfChangeAdapterState(dev, ZM_STA_STATE_DISCONNECT);
	zfHpResetKeyCache(dev);

	if (isConnected) {
		/* zfiWlanDisable(dev); */
		if (wd->zfcbConnectNotify != NULL)
			wd->zfcbConnectNotify(dev,
			ZM_STATUS_MEDIA_CONNECTION_RESET, wd->sta.bssid);
	} else {
		if (wd->zfcbConnectNotify != NULL)
			wd->zfcbConnectNotify(dev, ZM_STATUS_MEDIA_RESET,
								wd->sta.bssid);
	}

	/* stop beacon */
	zfHpDisableBeacon(dev);

	/* Free buffer in defragment list*/
	zfAgingDefragList(dev, 1);

	/* Flush VTxQ and MmQ */
	zfFlushVtxq(dev);

#ifdef ZM_ENABLE_AGGREGATION
	/* add by honda */
	zfAggRxFreeBuf(dev, 0);  /* 1 for release structure memory */
	/* end of add by honda */
#endif

	zfStaRefreshBlockList(dev, 1);

	zmw_enter_critical_section(dev);

	zfTimerCancel(dev, ZM_EVENT_IBSS_MONITOR);
	zfTimerCancel(dev, ZM_EVENT_CM_BLOCK_TIMER);
	zfTimerCancel(dev, ZM_EVENT_CM_DISCONNECT);

	wd->sta.connectState = ZM_STA_CONN_STATE_NONE;
	wd->sta.connectByReasso = FALSE;
	wd->sta.cmDisallowSsidLength = 0;
	wd->sta.bAutoReconnect = 0;
	wd->sta.InternalScanReq = 0;
	wd->sta.encryMode = ZM_NO_WEP;
	wd->sta.wepStatus = ZM_ENCRYPTION_WEP_DISABLED;
	wd->sta.wpaState = ZM_STA_WPA_STATE_INIT;
	wd->sta.cmMicFailureCount = 0;
	wd->sta.ibssBssIsCreator = 0;
#ifdef ZM_ENABLE_IBSS_WPA2PSK
	wd->sta.ibssWpa2Psk = 0;
#endif
	/* reset connect timeout counter */
	wd->sta.connectTimeoutCount = 0;

	/* reset leap enable variable */
	wd->sta.leapEnabled = 0;

	/* Reset the RIFS Status / RIFS-like frame count / RIFS count */
	if (wd->sta.rifsState == ZM_RIFS_STATE_DETECTED)
		zfHpDisableRifs(dev);
	wd->sta.rifsState = ZM_RIFS_STATE_DETECTING;
	wd->sta.rifsLikeFrameCnt = 0;
	wd->sta.rifsCount = 0;

	wd->sta.osRxFilter = 0;
	wd->sta.bSafeMode = 0;

	/* 	Clear the information for the peer
		stations of IBSS or AP of Station mode
	*/
	zfZeroMemory((u8_t *)wd->sta.oppositeInfo,
			sizeof(struct zsOppositeInfo) * ZM_MAX_OPPOSITE_COUNT);

	zmw_leave_critical_section(dev);

	zfScanMgrScanStop(dev, ZM_SCAN_MGR_SCAN_INTERNAL);
	zfScanMgrScanStop(dev, ZM_SCAN_MGR_SCAN_EXTERNAL);

	/* Turn off Software WEP/TKIP */
	if (wd->sta.SWEncryptEnable != 0) {
		zm_debug_msg0("Disable software encryption");
		zfStaDisableSWEncryption(dev);
	}

	/* 	Improve WEP/TKIP performace with HT AP,
		detail information please look bug#32495
	*/
	/* zfHpSetTTSIFSTime(dev, 0x8); */

	/* Keep Pseudo mode */
	if (wd->wlanMode != ZM_MODE_PSEUDO)
		wd->wlanMode = ZM_MODE_INFRASTRUCTURE;

	return 0;
}