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
typedef  int /*<<< orphan*/  (* zfpFreqChangeCompleteCb ) (int /*<<< orphan*/ *) ;
typedef  int /*<<< orphan*/  zdev_t ;
typedef  scalar_t__ u8_t ;
typedef  int /*<<< orphan*/  u16_t ;
struct TYPE_3__ {scalar_t__ currentBw40; scalar_t__ currentExtOffset; scalar_t__ flagFreqChanging; int /*<<< orphan*/  connPowerInHalfDbm; int /*<<< orphan*/  currentFrequency; } ;
struct TYPE_4__ {TYPE_1__ sta; int /*<<< orphan*/  frequency; } ;

/* Variables and functions */
 int /*<<< orphan*/  ZM_LV_1 ; 
 TYPE_2__* wd ; 
 int /*<<< orphan*/  zfAddFreqChangeReq (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__,scalar_t__,int /*<<< orphan*/  (*) (int /*<<< orphan*/ *)) ; 
 int /*<<< orphan*/  zfHpGetTransmitPower (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zfHpSetFrequencyEx (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  zfPushVtxq (int /*<<< orphan*/ *) ; 
 scalar_t__ zfStaIsConnected (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zm_debug_msg0 (char*) ; 
 int /*<<< orphan*/  zm_msg1_scan (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zmw_declare_for_critical_section () ; 
 int /*<<< orphan*/  zmw_enter_critical_section (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zmw_get_wlan_dev (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zmw_leave_critical_section (int /*<<< orphan*/ *) ; 

void zfCoreSetFrequencyExV2(zdev_t* dev, u16_t frequency, u8_t bw40,
        u8_t extOffset, zfpFreqChangeCompleteCb cb, u8_t forceSetFreq)
{
    u8_t setFreqImmed = 0;
    u8_t initRF = 0;
    zmw_get_wlan_dev(dev);
    zmw_declare_for_critical_section();

    zm_msg1_scan(ZM_LV_1, "Freq=", frequency);

    zmw_enter_critical_section(dev);
    if ((wd->sta.currentFrequency == frequency)
        && (wd->sta.currentBw40 == bw40)
        && (wd->sta.currentExtOffset == extOffset))
    {
        if ( forceSetFreq == 0 && wd->sta.flagFreqChanging == 0 )
        {
            goto done;
        }
    }
#ifdef ZM_FB50
    /*if(frequency!=2437) {
        zmw_leave_critical_section(dev);
        return;
    }*/
#endif

    zfAddFreqChangeReq(dev, frequency, bw40, extOffset, cb);

//    zm_assert( wd->sta.flagFreqChanging == 0 );
    //wd->sta.flagFreqChanging = 1;
    if ( wd->sta.flagFreqChanging == 0 )
    {
        if ((wd->sta.currentBw40 != bw40) || (wd->sta.currentExtOffset != extOffset))
        {
            initRF = 1;
        }
        wd->sta.currentFrequency = frequency;
        wd->sta.currentBw40 = bw40;
        wd->sta.currentExtOffset = extOffset;
        setFreqImmed = 1;
    }
    wd->sta.flagFreqChanging++;

    zmw_leave_critical_section(dev);

    if ( setFreqImmed )
    {
        //zfHpSetFrequency(dev, frequency, 0);
        if ( forceSetFreq )
        { // Cold reset to reset the frequency after scanning !
            zm_debug_msg0("#6_1 20070917");
            zm_debug_msg0("It is happen!!! No error message");
            zfHpSetFrequencyEx(dev, frequency, bw40, extOffset, 2);
        }
        else
        {
        zfHpSetFrequencyEx(dev, frequency, bw40, extOffset, initRF);
        }

        if (    zfStaIsConnected(dev)
             && (frequency == wd->frequency)) {
            wd->sta.connPowerInHalfDbm = zfHpGetTransmitPower(dev);
        }
    }
    return;

done:
    zmw_leave_critical_section(dev);

    if ( cb != NULL )
    {
        cb(dev);
    }
    zfPushVtxq(dev);
    return;
}