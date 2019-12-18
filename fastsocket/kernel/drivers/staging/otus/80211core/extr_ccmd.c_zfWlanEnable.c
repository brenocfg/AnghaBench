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
typedef  int u32_t ;
typedef  int u16_t ;
struct TYPE_5__ {scalar_t__ cmDisallowSsidLength; scalar_t__ ssidLen; scalar_t__ wepStatus; scalar_t__ EnableHT; int /*<<< orphan*/  bssid; int /*<<< orphan*/  authMode; int /*<<< orphan*/  cmDisallowSsid; int /*<<< orphan*/  ssid; scalar_t__ oppositeCount; } ;
struct TYPE_6__ {int apBitmap; int staAgingTimeSec; int staProbingTimeSec; int* ssidLen; char** ssid; scalar_t__* encryMode; int* capab; scalar_t__* wlanType; int vapNumber; int /*<<< orphan*/ * authAlgo; scalar_t__* bcmcTail; scalar_t__* bcmcHead; scalar_t__* hideSsid; scalar_t__ beaconCounter; } ;
struct TYPE_7__ {int bRateBasic; int gRateBasic; int ssidLen; char* ssid; scalar_t__ encryMode; int /*<<< orphan*/  authMode; int /*<<< orphan*/  bgMode; } ;
struct TYPE_8__ {int wlanMode; int bRate; int gRate; int bRateBasic; int gRateBasic; int CurrentTxRateKbps; int CurrentRxRateKbps; int /*<<< orphan*/  state; TYPE_1__ sta; int /*<<< orphan*/  (* zfcbConnectNotify ) (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  frequency; TYPE_2__ ap; TYPE_3__ ws; int /*<<< orphan*/  bgMode; } ;

/* Variables and functions */
 int /*<<< orphan*/  ZM_AUTH_MODE_WPA2PSK ; 
 scalar_t__ ZM_ENCRYPTION_TKIP ; 
 int /*<<< orphan*/  ZM_HAL_80211_MODE_IBSS_GENERAL ; 
 int /*<<< orphan*/  ZM_HAL_80211_MODE_IBSS_WPA2PSK ; 
 int /*<<< orphan*/  ZM_HAL_80211_MODE_STA ; 
 int ZM_HP_CAP_11N_ONE_TX_STREAM ; 
 int /*<<< orphan*/  ZM_LV_0 ; 
 int ZM_MAX_AP_SUPPORT ; 
 int ZM_MODE_AP ; 
#define  ZM_MODE_IBSS 130 
#define  ZM_MODE_INFRASTRUCTURE 129 
#define  ZM_MODE_PSEUDO 128 
 int ZM_MODE_UNKNOWN ; 
 int /*<<< orphan*/  ZM_SCAN_MGR_SCAN_EXTERNAL ; 
 int /*<<< orphan*/  ZM_SCAN_MGR_SCAN_INTERNAL ; 
 int /*<<< orphan*/  ZM_STATUS_MEDIA_CONNECT ; 
 int /*<<< orphan*/  ZM_STA_STATE_CONNECTED ; 
 int /*<<< orphan*/  ZM_WLAN_STATE_ENABLED ; 
 scalar_t__ ZM_WLAN_TYPE_PURE_B ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_4__* wd ; 
 int /*<<< orphan*/  zfApInitStaTbl (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zfApSendBeacon (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zfApSetProtectionMode (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zfChangeAdapterState (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zfCoreSetFrequency (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int zfHpCapability (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zfHpSetApStaMode (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zfIbssConnectNetwork (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zfInfraConnectNetwork (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zfInitMacApMode (int /*<<< orphan*/ *) ; 
 scalar_t__ zfMemoryIsEqual (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  zfScanMgrScanStop (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zfStaInitOppositeInfo (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zfStaResetStatus (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zfUpdateBssid (int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  zfWlanReset (int /*<<< orphan*/ *) ; 
 int zfwGetVapId (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zm_debug_msg0 (char*) ; 
 int /*<<< orphan*/  zm_msg0_mm (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  zmw_declare_for_critical_section () ; 
 int /*<<< orphan*/  zmw_enter_critical_section (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zmw_get_wlan_dev (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zmw_leave_critical_section (int /*<<< orphan*/ *) ; 

u16_t zfWlanEnable(zdev_t *dev)
{
	u8_t bssid[6] = {0x0, 0x0, 0x0, 0x0, 0x0, 0x0};
	u16_t i;

	zmw_get_wlan_dev(dev);

	zmw_declare_for_critical_section();

	if (wd->wlanMode == ZM_MODE_UNKNOWN) {
		zm_debug_msg0("Unknown Mode...Skip...");
		return 0;
	}

	if (wd->wlanMode == ZM_MODE_AP) {
		u16_t vapId;

		vapId = zfwGetVapId(dev);

		if (vapId == 0xffff) {
			/* AP mode */
			zfApInitStaTbl(dev);

			/* AP default parameters */
			wd->bRate = 0xf;
			wd->gRate = 0xff;
			wd->bRateBasic = 0xf;
			wd->gRateBasic = 0x0;
			/* wd->beaconInterval = 100; */
			wd->ap.apBitmap = 1;
			wd->ap.beaconCounter = 0;
			/* wd->ap.vapNumber = 1; //mark by ygwei for Vap */

			wd->ap.hideSsid[0] = 0;
			wd->ap.staAgingTimeSec = 10*60;
			wd->ap.staProbingTimeSec = 60;

			for (i = 0; i < ZM_MAX_AP_SUPPORT; i++)
				wd->ap.bcmcHead[i] = wd->ap.bcmcTail[i] = 0;

			/* wd->ap.uniHead = wd->ap.uniTail = 0; */

			/* load AP parameters */
			wd->bRateBasic = wd->ws.bRateBasic;
			wd->gRateBasic = wd->ws.gRateBasic;
			wd->bgMode = wd->ws.bgMode;
			if ((wd->ws.ssidLen <= 32) && (wd->ws.ssidLen != 0)) {
				wd->ap.ssidLen[0] = wd->ws.ssidLen;
				for (i = 0; i < wd->ws.ssidLen; i++)
					wd->ap.ssid[0][i] = wd->ws.ssid[i];
				wd->ws.ssidLen = 0; /* Reset Wrapper Variable */
			}

			if (wd->ap.encryMode[0] == 0)
				wd->ap.capab[0] = 0x001;
			else
				wd->ap.capab[0] = 0x011;
			/* set Short Slot Time bit if not 11b */
			if (wd->ap.wlanType[0] != ZM_WLAN_TYPE_PURE_B)
				wd->ap.capab[0] |= 0x400;

			/* wd->ap.vapNumber = 1; //mark by ygwei for Vap Test */
		} else {
#if 0
			/* VAP Test Code */
			wd->ap.apBitmap = 0x3;
			wd->ap.capab[1] = 0x401;
			wd->ap.ssidLen[1] = 4;
			wd->ap.ssid[1][0] = 'v';
			wd->ap.ssid[1][1] = 'a';
			wd->ap.ssid[1][2] = 'p';
			wd->ap.ssid[1][3] = '1';
			wd->ap.authAlgo[1] = wd->ws.authMode;
			wd->ap.encryMode[1] = wd->ws.encryMode;
			wd->ap.vapNumber = 2;
#else
			/* VAP Test Code */
			wd->ap.apBitmap = 0x1 | (0x01 << (vapId+1));

			if ((wd->ws.ssidLen <= 32) && (wd->ws.ssidLen != 0)) {
				wd->ap.ssidLen[vapId+1] = wd->ws.ssidLen;
				for (i = 0; i < wd->ws.ssidLen; i++)
					wd->ap.ssid[vapId+1][i] =
								wd->ws.ssid[i];
				wd->ws.ssidLen = 0; /* Reset Wrapper Variable */
			}

			if (wd->ap.encryMode[vapId+1] == 0)
				wd->ap.capab[vapId+1] = 0x401;
			else
				wd->ap.capab[vapId+1] = 0x411;

			wd->ap.authAlgo[vapId+1] = wd->ws.authMode;
			wd->ap.encryMode[vapId+1] = wd->ws.encryMode;

			/* Need to be modified when VAP is used */
			/* wd->ap.vapNumber = 2; */
#endif
		}

		wd->ap.vapNumber++;

		zfCoreSetFrequency(dev, wd->frequency);

		zfInitMacApMode(dev);

		/* Disable protection mode */
		zfApSetProtectionMode(dev, 0);

		zfApSendBeacon(dev);
	} else { /*if (wd->wlanMode == ZM_MODE_AP) */

		zfScanMgrScanStop(dev, ZM_SCAN_MGR_SCAN_INTERNAL);
		zfScanMgrScanStop(dev, ZM_SCAN_MGR_SCAN_EXTERNAL);

		zmw_enter_critical_section(dev);
		wd->sta.oppositeCount = 0;    /* reset opposite count */
		/* wd->sta.bAutoReconnect = wd->sta.bAutoReconnectEnabled; */
		/* wd->sta.scanWithSSID = 0; */
		zfStaInitOppositeInfo(dev);
		zmw_leave_critical_section(dev);

		zfStaResetStatus(dev, 0);

		if ((wd->sta.cmDisallowSsidLength != 0) &&
		(wd->sta.ssidLen == wd->sta.cmDisallowSsidLength) &&
		(zfMemoryIsEqual(wd->sta.ssid, wd->sta.cmDisallowSsid,
		wd->sta.ssidLen)) &&
		(wd->sta.wepStatus == ZM_ENCRYPTION_TKIP)) {/*countermeasures*/
			zm_debug_msg0("countermeasures disallow association");
		} else {
			switch (wd->wlanMode) {
			case ZM_MODE_IBSS:
				/* some registers may be set here */
				if (wd->sta.authMode == ZM_AUTH_MODE_WPA2PSK)
					zfHpSetApStaMode(dev,
					ZM_HAL_80211_MODE_IBSS_WPA2PSK);
				else
					zfHpSetApStaMode(dev,
					ZM_HAL_80211_MODE_IBSS_GENERAL);

				zm_msg0_mm(ZM_LV_0, "ZM_MODE_IBSS");
				zfIbssConnectNetwork(dev);
				break;

			case ZM_MODE_INFRASTRUCTURE:
				/* some registers may be set here */
				zfHpSetApStaMode(dev, ZM_HAL_80211_MODE_STA);

				zfInfraConnectNetwork(dev);
				break;

			case ZM_MODE_PSEUDO:
				/* some registers may be set here */
				zfHpSetApStaMode(dev, ZM_HAL_80211_MODE_STA);

				zfUpdateBssid(dev, bssid);
				zfCoreSetFrequency(dev, wd->frequency);
				break;

			default:
				break;
			}
		}

	}


	/* if ((wd->wlanMode != ZM_MODE_INFRASTRUCTURE) &&
		(wd->wlanMode != ZM_MODE_AP))
	*/
	if (wd->wlanMode == ZM_MODE_PSEUDO) {
		/* Reset Wlan status */
		zfWlanReset(dev);

		if (wd->zfcbConnectNotify != NULL)
			wd->zfcbConnectNotify(dev, ZM_STATUS_MEDIA_CONNECT,
								wd->sta.bssid);
		zfChangeAdapterState(dev, ZM_STA_STATE_CONNECTED);
	}


	if (wd->wlanMode == ZM_MODE_AP) {
		if (wd->zfcbConnectNotify != NULL)
			wd->zfcbConnectNotify(dev, ZM_STATUS_MEDIA_CONNECT,
								wd->sta.bssid);
		/* zfChangeAdapterState(dev, ZM_STA_STATE_CONNECTED); */
	}

	/* Assign default Tx Rate */
	if (wd->sta.EnableHT) {
		u32_t oneTxStreamCap;
		oneTxStreamCap = (zfHpCapability(dev) &
						ZM_HP_CAP_11N_ONE_TX_STREAM);
		if (oneTxStreamCap)
			wd->CurrentTxRateKbps = 135000;
		else
			wd->CurrentTxRateKbps = 270000;
		wd->CurrentRxRateKbps = 270000;
	} else {
		wd->CurrentTxRateKbps = 54000;
		wd->CurrentRxRateKbps = 54000;
	}

	wd->state = ZM_WLAN_STATE_ENABLED;

	return 0;
}