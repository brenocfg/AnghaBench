#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zdev_t ;
typedef  int /*<<< orphan*/  u8_t ;
typedef  int u16_t ;
struct TYPE_11__ {char* countryIsoName; scalar_t__ wlanMode; int frequency; scalar_t__ adhocMode; int preambleType; scalar_t__ authMode; int beaconInterval; scalar_t__ dtim; int apWmeEnabled; scalar_t__ ssidLen; scalar_t__ staWmeQosInfo; int /*<<< orphan*/  staWmeEnabled; int /*<<< orphan*/  ssid; void* bDesiredBssid; int /*<<< orphan*/  desiredBssid; int /*<<< orphan*/  ibssJoinOnly; int /*<<< orphan*/  dropUnencryptedPkts; scalar_t__ atimWindow; int /*<<< orphan*/  wepStatus; int /*<<< orphan*/  encryMode; } ;
struct TYPE_8__ {scalar_t__ bssidCount; } ;
struct TYPE_9__ {scalar_t__ authMode; scalar_t__ currentAuthMode; int ssidLen; scalar_t__ wmeQosInfo; int /*<<< orphan*/  wmeEnabled; scalar_t__* ssid; TYPE_2__ pmkidInfo; scalar_t__ failCntOfReasso; void* connectByReasso; void* bDesiredBssid; scalar_t__* desiredBssid; int /*<<< orphan*/  ibssJoinOnly; int /*<<< orphan*/  dropUnencryptedPkts; scalar_t__ atimWindow; int /*<<< orphan*/  wepStatus; } ;
struct TYPE_7__ {int bIbssGMode; } ;
struct TYPE_10__ {scalar_t__* authAlgo; int qosMode; int uapsdEnabled; int /*<<< orphan*/ * encryMode; } ;
struct TYPE_12__ {scalar_t__ wlanMode; int frequency; int preambleType; int beaconInterval; int dtim; TYPE_5__ ws; TYPE_3__ sta; TYPE_1__ wfc; TYPE_4__ ap; } ;

/* Variables and functions */
 void* FALSE ; 
 void* TRUE ; 
 scalar_t__ ZM_ADHOCBAND_A ; 
 scalar_t__ ZM_ADHOCBAND_ABG ; 
 scalar_t__ ZM_ADHOCBAND_BG ; 
 scalar_t__ ZM_ADHOCBAND_G ; 
 scalar_t__ ZM_AUTH_MODE_WPA ; 
 scalar_t__ ZM_AUTH_MODE_WPAPSK ; 
 int ZM_CH_A_36 ; 
 int ZM_CH_G_6 ; 
 scalar_t__ ZM_MODE_AP ; 
 scalar_t__ ZM_MODE_IBSS ; 
 int /*<<< orphan*/  ZM_NO_WEP ; 
#define  ZM_PREAMBLE_TYPE_AUTO 130 
#define  ZM_PREAMBLE_TYPE_LONG 129 
#define  ZM_PREAMBLE_TYPE_SHORT 128 
 TYPE_6__* wd ; 
 int zfChGetFirstChannel (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zfHpGetRegionCodeFromIsoName (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  zfHpGetRegulationTablefromRegionCode (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zfMemoryCopy (scalar_t__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  zfMemoryIsEqual (int /*<<< orphan*/ ,scalar_t__*,int) ; 
 int zfwGetVapId (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zmw_declare_for_critical_section () ; 
 int /*<<< orphan*/  zmw_enter_critical_section (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zmw_get_wlan_dev (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zmw_leave_critical_section (int /*<<< orphan*/ *) ; 

void zfGetWrapperSetting(zdev_t *dev)
{
	u8_t bPassive;
	u16_t vapId = 0;

	zmw_get_wlan_dev(dev);

	zmw_declare_for_critical_section();
#if 0
	if ((wd->ws.countryIsoName[0] != 0)
		|| (wd->ws.countryIsoName[1] != 0)
		|| (wd->ws.countryIsoName[2] != '\0')) {
		zfHpGetRegulationTablefromRegionCode(dev,
		zfHpGetRegionCodeFromIsoName(dev, wd->ws.countryIsoName));
	}
#endif
	zmw_enter_critical_section(dev);

	wd->wlanMode = wd->ws.wlanMode;

	/* set channel */
	if (wd->ws.frequency) {
		wd->frequency = wd->ws.frequency;
		wd->ws.frequency = 0;
	} else {
		wd->frequency = zfChGetFirstChannel(dev, &bPassive);

		if (wd->wlanMode == ZM_MODE_IBSS) {
			if (wd->ws.adhocMode == ZM_ADHOCBAND_A)
				wd->frequency = ZM_CH_A_36;
			else
				wd->frequency = ZM_CH_G_6;
		}
	}
#ifdef ZM_AP_DEBUG
	/* honda add for debug, 2437 channel 6, 2452 channel 9 */
	wd->frequency = 2437;
	/* end of add by honda */
#endif

	/* set preamble type */
	switch (wd->ws.preambleType) {
	case ZM_PREAMBLE_TYPE_AUTO:
	case ZM_PREAMBLE_TYPE_SHORT:
	case ZM_PREAMBLE_TYPE_LONG:
		wd->preambleType = wd->ws.preambleType;
		break;
	default:
		wd->preambleType = ZM_PREAMBLE_TYPE_SHORT;
		break;
	}
	wd->ws.preambleType = 0;

	if (wd->wlanMode == ZM_MODE_AP) {
		vapId = zfwGetVapId(dev);

		if (vapId == 0xffff) {
			wd->ap.authAlgo[0] = wd->ws.authMode;
			wd->ap.encryMode[0] = wd->ws.encryMode;
		} else {
			wd->ap.authAlgo[vapId + 1] = wd->ws.authMode;
			wd->ap.encryMode[vapId + 1] = wd->ws.encryMode;
		}
		wd->ws.authMode = 0;
		wd->ws.encryMode = ZM_NO_WEP;

		/* Get beaconInterval from WrapperSetting */
		if ((wd->ws.beaconInterval >= 20) &&
					(wd->ws.beaconInterval <= 1000))
			wd->beaconInterval = wd->ws.beaconInterval;
		else
			wd->beaconInterval = 100; /* 100ms */

		if (wd->ws.dtim > 0)
			wd->dtim = wd->ws.dtim;
		else
			wd->dtim = 1;


		wd->ap.qosMode = wd->ws.apWmeEnabled & 0x1;
		wd->ap.uapsdEnabled = (wd->ws.apWmeEnabled & 0x2) >> 1;
	} else {
		wd->sta.authMode = wd->ws.authMode;
		wd->sta.currentAuthMode = wd->ws.authMode;
		wd->sta.wepStatus = wd->ws.wepStatus;

		if (wd->ws.beaconInterval)
			wd->beaconInterval = wd->ws.beaconInterval;
		else
			wd->beaconInterval = 0x64;

		if (wd->wlanMode == ZM_MODE_IBSS) {
			/* 1. Set default channel 6 (2437MHz) */
			/* wd->frequency = 2437; */

			/* 2. Otus support 802.11g Mode */
			if ((wd->ws.adhocMode == ZM_ADHOCBAND_G) ||
				(wd->ws.adhocMode == ZM_ADHOCBAND_BG) ||
				(wd->ws.adhocMode == ZM_ADHOCBAND_ABG))
				wd->wfc.bIbssGMode = 1;
			else
				wd->wfc.bIbssGMode = 0;

			/* 3. set short preamble  */
			/* wd->sta.preambleType = ZM_PREAMBLE_TYPE_SHORT; */
		}

		/* set ATIM window */
		if (wd->ws.atimWindow)
			wd->sta.atimWindow = wd->ws.atimWindow;
		else {
			/* wd->sta.atimWindow = 0x0a; */
			wd->sta.atimWindow = 0;
		}

		/* wd->sta.connectingHiddenAP = 1;
		   wd->ws.connectingHiddenAP;
		*/
		wd->sta.dropUnencryptedPkts = wd->ws.dropUnencryptedPkts;
		wd->sta.ibssJoinOnly = wd->ws.ibssJoinOnly;

		if (wd->ws.bDesiredBssid) {
			zfMemoryCopy(wd->sta.desiredBssid,
						wd->ws.desiredBssid, 6);
			wd->sta.bDesiredBssid = TRUE;
			wd->ws.bDesiredBssid = FALSE;
		} else
			wd->sta.bDesiredBssid = FALSE;

		/* check ssid */
		if (wd->ws.ssidLen != 0) {
			if ((!zfMemoryIsEqual(wd->ws.ssid, wd->sta.ssid,
				wd->sta.ssidLen)) ||
				(wd->ws.ssidLen != wd->sta.ssidLen) ||
				(wd->sta.authMode == ZM_AUTH_MODE_WPA) ||
				(wd->sta.authMode == ZM_AUTH_MODE_WPAPSK) ||
				(wd->ws.staWmeQosInfo != 0)) {
				/* if u-APSD test(set QosInfo), clear
				   connectByReasso to do association
				   (not reassociation)
				*/
				wd->sta.connectByReasso = FALSE;
				wd->sta.failCntOfReasso = 0;
				wd->sta.pmkidInfo.bssidCount = 0;

				wd->sta.ssidLen = wd->ws.ssidLen;
				zfMemoryCopy(wd->sta.ssid, wd->ws.ssid,
							wd->sta.ssidLen);

				if (wd->sta.ssidLen < 32)
					wd->sta.ssid[wd->sta.ssidLen] = 0;
			}
		} else {
			/* ANY BSS */
			wd->sta.ssid[0] = 0;
			wd->sta.ssidLen = 0;
		}

		wd->sta.wmeEnabled = wd->ws.staWmeEnabled;
		wd->sta.wmeQosInfo = wd->ws.staWmeQosInfo;

	}

	zmw_leave_critical_section(dev);
}