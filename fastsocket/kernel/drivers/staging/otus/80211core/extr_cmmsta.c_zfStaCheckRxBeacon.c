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
struct TYPE_3__ {scalar_t__ rxBeaconCount; int beaconMissState; int /*<<< orphan*/  bssid; } ;
struct TYPE_4__ {scalar_t__ wlanMode; int beaconInterval; int tick; TYPE_1__ sta; int /*<<< orphan*/  ExtOffset; int /*<<< orphan*/  BandWidth40; int /*<<< orphan*/  frequency; } ;

/* Variables and functions */
 scalar_t__ ZM_MODE_INFRASTRUCTURE ; 
 int ZM_MS_PER_TICK ; 
 int /*<<< orphan*/  ZM_STATUS_MEDIA_DISCONNECT_BEACON_MISS ; 
 int /*<<< orphan*/  ZM_WLAN_FRAME_TYPE_DEAUTH ; 
 TYPE_2__* wd ; 
 int /*<<< orphan*/  zfCoreSetFrequencyExV2 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  zfSendMmFrame (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zfStaConnectFail (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ zfStaIsConnected (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zmw_get_wlan_dev (int /*<<< orphan*/ *) ; 

void zfStaCheckRxBeacon(zdev_t* dev)
{
    zmw_get_wlan_dev(dev);

    if (( wd->wlanMode == ZM_MODE_INFRASTRUCTURE ) && (zfStaIsConnected(dev)))
    {
        if (wd->beaconInterval == 0)
        {
            wd->beaconInterval = 100;
        }
        if ( (wd->tick % ((wd->beaconInterval * 10) / ZM_MS_PER_TICK)) == 0 )
        {
            /* Check rxBeaconCount */
            if (wd->sta.rxBeaconCount == 0)
            {
                if (wd->sta.beaconMissState == 1)
                {
            	/*notify AP that we left*/
            	zfSendMmFrame(dev, ZM_WLAN_FRAME_TYPE_DEAUTH, wd->sta.bssid, 3, 0, 0);
                /* Beacon Lost */
                zfStaConnectFail(dev, ZM_STATUS_MEDIA_DISCONNECT_BEACON_MISS,
                        wd->sta.bssid, 0);
                }
                else
                {
                    wd->sta.beaconMissState = 1;
                    /* Reset channel */
                    zfCoreSetFrequencyExV2(dev, wd->frequency, wd->BandWidth40,
                            wd->ExtOffset, NULL, 1);
                }
            }
            else
            {
                wd->sta.beaconMissState = 0;
            }
            wd->sta.rxBeaconCount = 0;
        }
    }
}