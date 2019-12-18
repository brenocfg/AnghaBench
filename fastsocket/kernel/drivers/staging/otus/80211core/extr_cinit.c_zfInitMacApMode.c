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
struct TYPE_3__ {int vapNumber; int apBitmap; } ;
struct TYPE_4__ {int beaconInterval; int* macAddr; int /*<<< orphan*/  gRateBasic; int /*<<< orphan*/  bRateBasic; TYPE_1__ ap; } ;

/* Variables and functions */
 int /*<<< orphan*/  ZM_HAL_80211_MODE_AP ; 
 int ZM_MAX_AP_SUPPORT ; 
 int /*<<< orphan*/  ZM_MODE_AP ; 
 TYPE_2__* wd ; 
 int /*<<< orphan*/  zfHpEnableBeacon (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zfHpSetApStaMode (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zfHpSetBasicRateSet (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zfHpSetMacAddress (int /*<<< orphan*/ *,int*,int) ; 
 int /*<<< orphan*/  zfUpdateDefaultQosParameter (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  zmw_get_wlan_dev (int /*<<< orphan*/ *) ; 

void zfInitMacApMode(zdev_t* dev)
{
    u16_t i;

    zmw_get_wlan_dev(dev);

    zfHpEnableBeacon(dev, ZM_MODE_AP, (wd->beaconInterval/wd->ap.vapNumber), 1, 0);

    /* AP mode */
    zfHpSetApStaMode(dev, ZM_HAL_80211_MODE_AP);

    /* VAP test code */
    /* AP + VAP mode */
    if (wd->ap.vapNumber >= 2)
    {
        for (i=1; i<ZM_MAX_AP_SUPPORT; i++)
        {
            if (((wd->ap.apBitmap >> i) & 0x1) != 0)
            {
                u16_t mac[3];
                mac[0] = wd->macAddr[0];
                mac[1] = wd->macAddr[1];
#ifdef ZM_VAPMODE_MULTILE_SSID
                mac[2] = wd->macAddr[2]; //Multiple SSID
#else
                mac[2] = wd->macAddr[2] + (i<<8); //VAP
#endif
                zfHpSetMacAddress(dev, mac, i);

            }
        }
    }

    /* basic rate setting */
    zfHpSetBasicRateSet(dev, wd->bRateBasic, wd->gRateBasic);

    /* Set TxQs CWMIN, CWMAX, AIFS and TXO to WME AP default. */
    zfUpdateDefaultQosParameter(dev, 1);

    return;
}