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
typedef  int u8_t ;
typedef  size_t u16_t ;
struct zsBssInfo {int signalStrength; int* beaconInterval; int* ssid; int* frameBody; int* rsnIe; int /*<<< orphan*/  atimWindow; int /*<<< orphan*/  frequency; int /*<<< orphan*/  channel; int /*<<< orphan*/ * capability; scalar_t__ bssid; scalar_t__ macaddr; } ;
struct TYPE_3__ {int ssidLen; scalar_t__ authMode; scalar_t__ wepStatus; int /*<<< orphan*/  atimWindow; scalar_t__ ssid; int /*<<< orphan*/ * capability; scalar_t__ bssid; struct zsBssInfo ibssBssDesc; } ;
struct TYPE_4__ {int beaconInterval; TYPE_1__ sta; int /*<<< orphan*/  frequency; scalar_t__ macAddr; } ;

/* Variables and functions */
 scalar_t__ ZM_AUTH_MODE_WPA2PSK ; 
 scalar_t__ ZM_ENCRYPTION_AES ; 
 int ZM_WLAN_EID_RSN_IE ; 
 int ZM_WLAN_EID_SSID ; 
 TYPE_2__* wd ; 
 int /*<<< orphan*/  zfChFreqToNum (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zfMemoryCopy (int*,int*,int) ; 
 int /*<<< orphan*/  zfZeroMemory (int*,int) ; 
 int* zgWpa2AesOui ; 
 int /*<<< orphan*/  zmw_get_wlan_dev (int /*<<< orphan*/ *) ; 

void zfIBSSSetupBssDesc(zdev_t *dev)
{
#ifdef ZM_ENABLE_IBSS_WPA2PSK
    u8_t i;
#endif
    struct zsBssInfo *pBssInfo;
    u16_t offset = 0;

    zmw_get_wlan_dev(dev);

    pBssInfo = &wd->sta.ibssBssDesc;
    zfZeroMemory((u8_t *)pBssInfo, sizeof(struct zsBssInfo));

    pBssInfo->signalStrength = 100;

    zfMemoryCopy((u8_t *)pBssInfo->macaddr, (u8_t *)wd->macAddr,6);
    zfMemoryCopy((u8_t *)pBssInfo->bssid, (u8_t *)wd->sta.bssid, 6);

    pBssInfo->beaconInterval[0] = (u8_t)(wd->beaconInterval) ;
    pBssInfo->beaconInterval[1] = (u8_t)((wd->beaconInterval) >> 8) ;

    pBssInfo->capability[0] = wd->sta.capability[0];
    pBssInfo->capability[1] = wd->sta.capability[1];

    pBssInfo->ssid[0] = ZM_WLAN_EID_SSID;
    pBssInfo->ssid[1] = wd->sta.ssidLen;
    zfMemoryCopy((u8_t *)&pBssInfo->ssid[2], (u8_t *)wd->sta.ssid, wd->sta.ssidLen);
    zfMemoryCopy((u8_t *)&pBssInfo->frameBody[offset], (u8_t *)pBssInfo->ssid,
                 wd->sta.ssidLen + 2);
    offset += wd->sta.ssidLen + 2;

    /* support rate */

    /* DS parameter set */
    pBssInfo->channel = zfChFreqToNum(wd->frequency, NULL);
    pBssInfo->frequency = wd->frequency;
    pBssInfo->atimWindow = wd->sta.atimWindow;

#ifdef ZM_ENABLE_IBSS_WPA2PSK
    if ( wd->sta.authMode == ZM_AUTH_MODE_WPA2PSK )
    {
        u8_t rsn[64]=
        {
                    /* Element ID */
                    0x30,
                    /* Length */
                    0x14,
                    /* Version */
                    0x01, 0x00,
                    /* Group Cipher Suite, default=TKIP */
                    0x00, 0x0f, 0xac, 0x04,
                    /* Pairwise Cipher Suite Count */
                    0x01, 0x00,
                    /* Pairwise Cipher Suite, default=TKIP */
                    0x00, 0x0f, 0xac, 0x02,
                    /* Authentication and Key Management Suite Count */
                    0x01, 0x00,
                    /* Authentication type, default=PSK */
                    0x00, 0x0f, 0xac, 0x02,
                    /* RSN capability */
                    0x00, 0x00
        };

        /* Overwrite Group Cipher Suite by AP's setting */
        zfMemoryCopy(rsn+4, zgWpa2AesOui, 4);

        if ( wd->sta.wepStatus == ZM_ENCRYPTION_AES )
        {
            /* Overwrite Pairwise Cipher Suite by AES */
            zfMemoryCopy(rsn+10, zgWpa2AesOui, 4);
        }

        // RSN element id
        pBssInfo->frameBody[offset++] = ZM_WLAN_EID_RSN_IE ;

        // RSN length
        pBssInfo->frameBody[offset++] = rsn[1] ;

        // RSN information
        for(i=0; i<rsn[1]; i++)
        {
            pBssInfo->frameBody[offset++] = rsn[i+2] ;
        }

        zfMemoryCopy(pBssInfo->rsnIe, rsn, rsn[1]+2);
    }
#endif
}