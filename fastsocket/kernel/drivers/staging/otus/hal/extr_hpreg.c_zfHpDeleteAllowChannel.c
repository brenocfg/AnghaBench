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
typedef  int u16_t ;
struct TYPE_5__ {int allowChannelCnt; TYPE_1__* allowChannel; } ;
struct TYPE_6__ {TYPE_2__ regulationTable; } ;
struct TYPE_4__ {int channel; int channelFlags; } ;

/* Variables and functions */
 int ZM_REG_FLAG_CHANNEL_CSA ; 
 int ZM_REG_FLAG_CHANNEL_PASSIVE ; 
 TYPE_3__* wd ; 
 int /*<<< orphan*/  zmw_get_wlan_dev (int /*<<< orphan*/ *) ; 

u16_t zfHpDeleteAllowChannel(zdev_t* dev, u16_t freq)
{
    u16_t i, bandIndex = 0;
    u16_t dfs5GBand[][2] = {{5150, 5240}, {5260, 5350}, {5450, 5700}, {5725, 5825}};

    zmw_get_wlan_dev(dev);
    /* Find which band does this frequency belong */
    for (i = 0; i < 4; i++)
    {
        if ((freq >= dfs5GBand[i][0]) && (freq <= dfs5GBand[i][1]))
            bandIndex = i + 1;
    }

    if (bandIndex == 0)
    {
        /* 2.4G, don't care */
        return 0;
    }
    else
    {
        bandIndex--;
    }
    /* Set all channels in this band to passive scan */
    for (i = 0; i < wd->regulationTable.allowChannelCnt; i++)
    {
        if ((wd->regulationTable.allowChannel[i].channel >= dfs5GBand[bandIndex][0]) &&
            (wd->regulationTable.allowChannel[i].channel <= dfs5GBand[bandIndex][1]))
        {
            /* if channel is not passive, set it to be passive and mark it */
            if ((wd->regulationTable.allowChannel[i].channelFlags &
                    ZM_REG_FLAG_CHANNEL_PASSIVE) == 0)
            {
                wd->regulationTable.allowChannel[i].channelFlags |=
                        (ZM_REG_FLAG_CHANNEL_PASSIVE | ZM_REG_FLAG_CHANNEL_CSA);
            }
        }
    }

    return 0;
}