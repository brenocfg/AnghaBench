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
typedef  size_t u8_t ;
struct TYPE_7__ {size_t allowChannelCnt; TYPE_1__* allowChannel; int /*<<< orphan*/  regionCode; } ;
struct TYPE_6__ {size_t b802_11D; } ;
struct TYPE_8__ {TYPE_3__ regulationTable; TYPE_2__ sta; } ;
struct TYPE_5__ {int /*<<< orphan*/  channelFlags; } ;

/* Variables and functions */
 int /*<<< orphan*/  NO_ENUMRD ; 
 int /*<<< orphan*/  ZM_REG_FLAG_CHANNEL_PASSIVE ; 
 TYPE_4__* wd ; 
 int /*<<< orphan*/  zmw_get_wlan_dev (int /*<<< orphan*/ *) ; 

u8_t zfiWlanSetDot11DMode(zdev_t* dev, u8_t mode)
{
    u8_t i;

    zmw_get_wlan_dev(dev);

    wd->sta.b802_11D = mode;
    if (mode) //Enable 802.11d
    {
        wd->regulationTable.regionCode = NO_ENUMRD;
        for (i = 0; i < wd->regulationTable.allowChannelCnt; i++)
            wd->regulationTable.allowChannel[i].channelFlags |= ZM_REG_FLAG_CHANNEL_PASSIVE;
    }
    else //Disable
    {
        for (i = 0; i < wd->regulationTable.allowChannelCnt; i++)
            wd->regulationTable.allowChannel[i].channelFlags &= ~ZM_REG_FLAG_CHANNEL_PASSIVE;
    }

    return 0;
}