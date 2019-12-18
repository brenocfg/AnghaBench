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
struct TYPE_3__ {int /*<<< orphan*/ * capability; scalar_t__ TPCEnable; } ;
struct TYPE_4__ {TYPE_1__ sta; } ;

/* Variables and functions */
 int /*<<< orphan*/  ZM_BIT_0 ; 
 TYPE_2__* wd ; 
 int /*<<< orphan*/  zmw_get_wlan_dev (int /*<<< orphan*/ *) ; 

u8_t zfiWlanSetDot11HTPCMode(zdev_t* dev, u8_t mode)
{
    zmw_get_wlan_dev(dev);

    // TODO : TPC Enable in 5150~5350 MHz and 5470~5725MHz.
    //if ( Adapter->ZD80211HSupport &&
    //   Adapter->CardSetting.NetworkTypeInUse == Ndis802_11OFDM5 &&
    //   ((ChannelNo == 36 || ChannelNo == 40 || ChannelNo == 44 || ChannelNo == 48) ||	//5150~5250 MHZ , Not Japan
    //    (ChannelNo >=52 && ChannelNo <= 64) ||				//5250~5350 MHZ
    //    (ChannelNo >=100 && ChannelNo <= 140))) 			//5470~5725 MHZ
    //{
    //   Adapter->ZD80211HSetting.TPCEnable=TRUE;
    //}
    //else
    //{
    //   Adapter->ZD80211HSetting.TPCEnable=FALSE;
    //}

    wd->sta.TPCEnable = mode;
    if (mode)
        wd->sta.capability[1] |= ZM_BIT_0;
    else
        wd->sta.capability[1] &= (~ZM_BIT_0);

    return 0;
}