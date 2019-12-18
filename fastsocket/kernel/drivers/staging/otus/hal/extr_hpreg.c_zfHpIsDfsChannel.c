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
typedef  size_t u8_t ;
typedef  size_t u16_t ;
struct TYPE_4__ {size_t allowChannelCnt; TYPE_2__* allowChannel; } ;
struct TYPE_6__ {TYPE_1__ regulationTable; } ;
struct TYPE_5__ {size_t channel; size_t privFlags; } ;

/* Variables and functions */
 size_t ZM_REG_FLAG_CHANNEL_DFS ; 
 size_t ZM_REG_FLAG_CHANNEL_DFS_CLEAR ; 
 TYPE_3__* wd ; 
 int /*<<< orphan*/  zmw_declare_for_critical_section () ; 
 int /*<<< orphan*/  zmw_enter_critical_section (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zmw_get_wlan_dev (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zmw_leave_critical_section (int /*<<< orphan*/ *) ; 

u16_t zfHpIsDfsChannel(zdev_t* dev, u16_t freq)
{
    u8_t flag = ZM_REG_FLAG_CHANNEL_DFS;
    u16_t i;
    zmw_get_wlan_dev(dev);

    zmw_declare_for_critical_section();

    zmw_enter_critical_section(dev);

    for (i = 0; i < wd->regulationTable.allowChannelCnt; i++)
    {
        //DbgPrint("DFS:freq=%d, chan=%d", freq, wd->regulationTable.allowChannel[i].channel);
        if (wd->regulationTable.allowChannel[i].channel == freq)
        {
            flag = wd->regulationTable.allowChannel[i].privFlags;
            break;
        }
    }

    zmw_leave_critical_section(dev);

    return (flag & (ZM_REG_FLAG_CHANNEL_DFS|ZM_REG_FLAG_CHANNEL_DFS_CLEAR));
}