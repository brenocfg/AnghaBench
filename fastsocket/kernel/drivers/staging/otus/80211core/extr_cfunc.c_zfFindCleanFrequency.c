#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zdev_t ;
typedef  size_t u8_t ;
typedef  scalar_t__ u32_t ;
typedef  size_t u16_t ;
struct zsBssInfo {size_t frequency; int channel; struct zsBssInfo* next; } ;
struct TYPE_9__ {size_t allowChannelCnt; TYPE_3__* allowChannel; } ;
struct TYPE_6__ {struct zsBssInfo* head; } ;
struct TYPE_7__ {TYPE_1__ bssList; } ;
struct TYPE_10__ {TYPE_4__ regulationTable; TYPE_2__ sta; } ;
struct TYPE_8__ {int channel; } ;

/* Variables and functions */
 scalar_t__ ZM_ADHOCBAND_A ; 
 scalar_t__ ZM_ADHOCBAND_ABG ; 
 scalar_t__ ZM_ADHOCBAND_B ; 
 scalar_t__ ZM_ADHOCBAND_BG ; 
 scalar_t__ ZM_ADHOCBAND_G ; 
 int /*<<< orphan*/  printk (char*,size_t,size_t) ; 
 TYPE_5__* wd ; 
 size_t zfChGetFirst2GhzChannel (int /*<<< orphan*/ *) ; 
 size_t zfChGetFirst5GhzChannel (int /*<<< orphan*/ *) ; 
 size_t zfFindMinimumUtilizationChannelIndex (int /*<<< orphan*/ *,size_t*,size_t) ; 
 int /*<<< orphan*/  zmw_declare_for_critical_section () ; 
 int /*<<< orphan*/  zmw_enter_critical_section (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zmw_get_wlan_dev (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zmw_leave_critical_section (int /*<<< orphan*/ *) ; 

u16_t zfFindCleanFrequency(zdev_t* dev, u32_t adhocMode)
{
    u8_t   i, j;
    u16_t  returnChannel;
    u16_t  count_24G = 0, min24GIndex = 0;
    u16_t  count_5G = 0,  min5GIndex = 0;
    u16_t  CombinationBssNumberIn24G[15] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
    u16_t  BssNumberIn24G[17]  = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
    u16_t  Array_24G[15]       = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
    u16_t  BssNumberIn5G[31]   = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
    u16_t  Array_5G[31]        = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
    struct zsBssInfo* pBssInfo;

    zmw_get_wlan_dev(dev);

    if ((pBssInfo = wd->sta.bssList.head) == NULL)
    {
        if( adhocMode == ZM_ADHOCBAND_B || adhocMode == ZM_ADHOCBAND_G ||
            adhocMode == ZM_ADHOCBAND_BG || adhocMode == ZM_ADHOCBAND_ABG )
        {
            returnChannel = zfChGetFirst2GhzChannel(dev);
        }
        else
        {
            returnChannel = zfChGetFirst5GhzChannel(dev);
        }

        return returnChannel;
    }

    /* #1 Get Allowed Channel following Country Code ! */
    zmw_declare_for_critical_section();
    zmw_enter_critical_section(dev);
    for (i = 0; i < wd->regulationTable.allowChannelCnt; i++)
    {
        if (wd->regulationTable.allowChannel[i].channel < 3000)
        { // 2.4GHz
            Array_24G[count_24G] = wd->regulationTable.allowChannel[i].channel;
            count_24G++;
        }
        else
        { // 5GHz
            count_5G++;
            Array_5G[i] = wd->regulationTable.allowChannel[i].channel;
        }
    }
    zmw_leave_critical_section(dev);

    while( pBssInfo != NULL )
    {
        /* #2_1 Count BSS number in some specificed frequency in 2.4GHz band ! */
        if( adhocMode == ZM_ADHOCBAND_B || adhocMode == ZM_ADHOCBAND_G ||
            adhocMode == ZM_ADHOCBAND_BG || adhocMode == ZM_ADHOCBAND_ABG )
        {
            for( i=0; i<=(count_24G+3); i++ )
            {
                if( pBssInfo->frequency == Array_24G[i] )
                { // Array_24G[0] correspond to BssNumberIn24G[2]
                    BssNumberIn24G[pBssInfo->channel+1]++;
                }
            }
        }

        /* #2_2 Count BSS number in some specificed frequency in 5GHz band ! */
        if( adhocMode == ZM_ADHOCBAND_A || adhocMode == ZM_ADHOCBAND_ABG )
        {
            for( i=0; i<count_5G; i++ )
            { // 5GHz channel is not equal to array index
                if( pBssInfo->frequency == Array_5G[i] )
                { // Array_5G[0] correspond to BssNumberIn5G[0]
                    BssNumberIn5G[i]++;
                }
            }
        }

        pBssInfo = pBssInfo->next;
    }

#if 0
    for(i=0; i<=(count_24G+3); i++)
    {
        printk("2.4GHz Before combin, %d BSS network : %d", i, BssNumberIn24G[i]);
    }

    for(i=0; i<count_5G; i++)
    {
        printk("5GHz Before combin, %d BSS network : %d", i, BssNumberIn5G[i]);
    }
#endif

    if( adhocMode == ZM_ADHOCBAND_B || adhocMode == ZM_ADHOCBAND_G ||
        adhocMode == ZM_ADHOCBAND_BG || adhocMode == ZM_ADHOCBAND_ABG )
    {
        /* #3_1 Count BSS number that influence the specificed frequency in 2.4GHz ! */
        for( j=0; j<count_24G; j++ )
        {
            CombinationBssNumberIn24G[j] = BssNumberIn24G[j]   + BssNumberIn24G[j+1] +
                                           BssNumberIn24G[j+2] + BssNumberIn24G[j+3] +
                                           BssNumberIn24G[j+4];
            //printk("After combine, the number of BSS network channel %d is %d",
            //                                   j , CombinationBssNumberIn24G[j]);
        }

        /* #4_1 Find the less utilized frequency in 2.4GHz band ! */
        min24GIndex = zfFindMinimumUtilizationChannelIndex(dev, CombinationBssNumberIn24G, count_24G);
    }

    /* #4_2 Find the less utilized frequency in 5GHz band ! */
    if( adhocMode == ZM_ADHOCBAND_A || adhocMode == ZM_ADHOCBAND_ABG )
    {
        min5GIndex = zfFindMinimumUtilizationChannelIndex(dev, BssNumberIn5G, count_5G);
    }

    if( adhocMode == ZM_ADHOCBAND_B || adhocMode == ZM_ADHOCBAND_G || adhocMode == ZM_ADHOCBAND_BG )
    {
        return Array_24G[min24GIndex];
    }
    else if( adhocMode == ZM_ADHOCBAND_A )
    {
        return Array_5G[min5GIndex];
    }
    else if( adhocMode == ZM_ADHOCBAND_ABG )
    {
        if ( CombinationBssNumberIn24G[min24GIndex] <= BssNumberIn5G[min5GIndex] )
            return Array_24G[min24GIndex];
        else
            return Array_5G[min5GIndex];
    }
    else
        return 2412;
}