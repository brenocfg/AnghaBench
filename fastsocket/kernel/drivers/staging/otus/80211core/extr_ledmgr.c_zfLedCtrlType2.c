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
typedef  int /*<<< orphan*/  u32_t ;
typedef  size_t u16_t ;
struct TYPE_5__ {int counter; int* ledMode; scalar_t__ txTraffic; scalar_t__ rxTraffic; } ;
struct TYPE_4__ {scalar_t__ bChannelScan; scalar_t__ bAutoReconnect; } ;
struct TYPE_6__ {scalar_t__ state; int frequency; TYPE_2__ ledStruct; TYPE_1__ sta; } ;

/* Variables and functions */
 scalar_t__ TRUE ; 
 scalar_t__ ZM_WLAN_STATE_DISABLED ; 
 TYPE_3__* wd ; 
 int /*<<< orphan*/  zfHpLedCtrl (int /*<<< orphan*/ *,size_t,int) ; 
 int /*<<< orphan*/  zfLedCtrlType2_scan (int /*<<< orphan*/ *) ; 
 scalar_t__ zfPowerSavingMgrIsSleeping (int /*<<< orphan*/ *) ; 
 scalar_t__ zfStaIsConnected (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zmw_get_wlan_dev (int /*<<< orphan*/ *) ; 

void zfLedCtrlType2(zdev_t* dev)
{
    u32_t ton, toff, tmp, period;
    u16_t OperateLED;
    zmw_get_wlan_dev(dev);

    if (zfStaIsConnected(dev) != TRUE)
    {
        // Disconnect state
        if(wd->ledStruct.counter % 4 != 0)
    	{
      	    // Update LED each 400ms(4*100)
      	    // Prevent this situation
            //              _______         ___
            // LED[0] ON   |       |       | x |
            // ------ OFF->+-+-+-+-+-+-+-+-+-+-+-+->>>...
            // LED[1] ON
            //
            return;
        }

        if (((wd->state == ZM_WLAN_STATE_DISABLED) && (wd->sta.bChannelScan))
            || ((wd->state != ZM_WLAN_STATE_DISABLED) && (wd->sta.bAutoReconnect)))
        {
            // Scan/AutoReconnect state
            zfLedCtrlType2_scan(dev);
        }
        else
        {
            // Neither Connected nor Scan
            zfHpLedCtrl(dev, 0, 0);
            zfHpLedCtrl(dev, 1, 0);
        }
    }
    else
    {
        if( wd->sta.bChannelScan )
        {
            // Scan state
            if(wd->ledStruct.counter % 4 != 0)
                return;
            zfLedCtrlType2_scan(dev);
            return;
        }

        if(wd->frequency < 3000)
        {
            OperateLED = 0;     // LED[0]: work on 2.4G (b/g band)
            zfHpLedCtrl(dev, 1, 0);
        }
        else
        {
            OperateLED = 1;     // LED[1]: work on 5G (a band)
            zfHpLedCtrl(dev, 0, 0);
        }

        if ((zfPowerSavingMgrIsSleeping(dev)) && ((wd->ledStruct.ledMode[OperateLED] & 0x8) == 0))
        {
            // If Sleeping, turn OFF
            zfHpLedCtrl(dev, OperateLED, 0);
        }
        else
        {
            //Connect state
            if ((wd->ledStruct.counter & 1) == 0)   // even
            {
                // No traffic, always ON
                zfHpLedCtrl(dev, OperateLED, 1);
            }
            else       // odd
            {
                if ((wd->ledStruct.txTraffic > 0) || (wd->ledStruct.rxTraffic > 0))
                {
                    // If have traffic, turn OFF
		            //                   _____   _   _   _   _____
		            // LED[Operate] ON        | | | | | | | |
		            // ------------ OFF->-+-+-+-+-+-+-+-+-+-+-+-+-+->>>...
		            //
                    wd->ledStruct.txTraffic = wd->ledStruct.rxTraffic = 0;
                    zfHpLedCtrl(dev, OperateLED, 0);
                }
            }
        }
    }
}