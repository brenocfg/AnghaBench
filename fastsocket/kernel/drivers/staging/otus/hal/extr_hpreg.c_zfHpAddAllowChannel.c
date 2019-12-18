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
typedef  size_t u16_t ;
struct TYPE_5__ {size_t allowChannelCnt; TYPE_1__* allowChannel; } ;
struct TYPE_6__ {TYPE_2__ regulationTable; } ;
struct TYPE_4__ {size_t channel; } ;

/* Variables and functions */
 TYPE_3__* wd ; 
 int /*<<< orphan*/  zmw_get_wlan_dev (int /*<<< orphan*/ *) ; 

u16_t zfHpAddAllowChannel(zdev_t* dev, u16_t freq)
{
    u16_t i, j, arrayIndex;

    zmw_get_wlan_dev(dev);

    for (i = 0; i < wd->regulationTable.allowChannelCnt; i++)
    {
        if (wd->regulationTable.allowChannel[i].channel == freq)
            break;
    }

    if ( i == wd->regulationTable.allowChannelCnt)
    {
        for (j = 0; j < wd->regulationTable.allowChannelCnt; j++)
        {
            if (wd->regulationTable.allowChannel[j].channel > freq)
                break;
        }

        //zm_debug_msg1("CWY - add frequency = ", freq);
        //zm_debug_msg1("CWY - channel array index = ", j);

        arrayIndex = j;

        if (arrayIndex < wd->regulationTable.allowChannelCnt)
        {
            for (j = wd->regulationTable.allowChannelCnt; j > arrayIndex; j--)
                wd->regulationTable.allowChannel[j] = wd->regulationTable.allowChannel[j - 1];
        }
        wd->regulationTable.allowChannel[arrayIndex].channel = freq;

        wd->regulationTable.allowChannelCnt++;
    }

    return 0;
}