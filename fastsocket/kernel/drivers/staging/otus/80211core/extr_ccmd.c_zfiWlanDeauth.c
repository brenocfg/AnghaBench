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
typedef  int u16_t ;
struct TYPE_3__ {int* bssid; } ;
struct TYPE_4__ {scalar_t__ wlanMode; TYPE_1__ sta; } ;

/* Variables and functions */
 scalar_t__ ZM_MODE_AP ; 
 int /*<<< orphan*/  ZM_WLAN_FRAME_TYPE_DEAUTH ; 
 TYPE_2__* wd ; 
 int /*<<< orphan*/  zfSendMmFrame (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zmw_get_wlan_dev (int /*<<< orphan*/ *) ; 

u16_t zfiWlanDeauth(zdev_t *dev, u16_t *macAddr, u16_t reason)
{
	zmw_get_wlan_dev(dev);

	if (wd->wlanMode == ZM_MODE_AP) {
		/* u16_t id; */

		/*
		* we will reset all key in zfHpResetKeyCache() when call
		* zfiWlanDisable(), if we want to reset PairwiseKey for each
		* sta, need to use a nullAddr to let keyindex not match.
		* otherwise hardware will still find PairwiseKey when AP change
		* encryption mode from WPA to WEP
		*/

		/*
		if ((id = zfApFindSta(dev, macAddr)) != 0xffff)
		{
			u32_t key[8];
			u16_t nullAddr[3] = { 0x0, 0x0, 0x0 };

			if (wd->ap.staTable[i].encryMode != ZM_NO_WEP)
			{
				zfHpSetApPairwiseKey(dev, nullAddr,
				ZM_NO_WEP, &key[0], &key[4], i+1);
			}
			//zfHpSetApPairwiseKey(dev, (u16_t *)macAddr,
			//        ZM_NO_WEP, &key[0], &key[4], id+1);
		wd->ap.staTable[id].encryMode = ZM_NO_WEP;
		wd->ap.staTable[id].keyIdx = 0xff;
		}
		*/

		zfSendMmFrame(dev, ZM_WLAN_FRAME_TYPE_DEAUTH, macAddr,
								reason, 0, 0);
	} else
		zfSendMmFrame(dev, ZM_WLAN_FRAME_TYPE_DEAUTH,
						wd->sta.bssid, 3, 0, 0);

	/* Issue DEAUTH command to FW */
	return 0;
}