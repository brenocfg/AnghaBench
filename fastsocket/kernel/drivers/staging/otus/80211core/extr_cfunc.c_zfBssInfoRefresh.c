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
typedef  scalar_t__ u8_t ;
typedef  int u16_t ;
struct zsBssInfo {int flag; int tick; struct zsBssInfo* next; } ;
struct TYPE_4__ {scalar_t__ bssCount; struct zsBssInfo* head; } ;
struct TYPE_5__ {TYPE_1__ bssList; } ;
struct TYPE_6__ {int tick; TYPE_2__ sta; } ;

/* Variables and functions */
 int ZM_BSS_CACHE_TIME_IN_MS ; 
 int ZM_BSS_INFO_VALID_BIT ; 
 int ZM_MS_PER_TICK ; 
 TYPE_3__* wd ; 
 int /*<<< orphan*/  zfBssInfoFree (int /*<<< orphan*/ *,struct zsBssInfo*) ; 
 int /*<<< orphan*/  zfBssInfoRemoveFromList (int /*<<< orphan*/ *,struct zsBssInfo*) ; 
 int /*<<< orphan*/  zmw_get_wlan_dev (int /*<<< orphan*/ *) ; 

void zfBssInfoRefresh(zdev_t* dev, u16_t mode)
{
    struct zsBssInfo*   pBssInfo;
    struct zsBssInfo*   pNextBssInfo;
    u8_t   i, bssCount;

    zmw_get_wlan_dev(dev);

    pBssInfo = wd->sta.bssList.head;
    bssCount = wd->sta.bssList.bssCount;

    for( i=0; i<bssCount; i++ )
    {
        if (mode == 1)
        {
            pNextBssInfo = pBssInfo->next;
            zfBssInfoRemoveFromList(dev, pBssInfo);
            zfBssInfoFree(dev, pBssInfo);
            pBssInfo = pNextBssInfo;
        }
        else
        {
            if ( pBssInfo->flag & ZM_BSS_INFO_VALID_BIT )
            {   /* this one must be kept */
                pBssInfo->flag &= ~ZM_BSS_INFO_VALID_BIT;
                pBssInfo = pBssInfo->next;
            }
            else
            {
                #define ZM_BSS_CACHE_TIME_IN_MS   20000
                if ((wd->tick - pBssInfo->tick) > (ZM_BSS_CACHE_TIME_IN_MS/ZM_MS_PER_TICK))
                {
                    pNextBssInfo = pBssInfo->next;
                    zfBssInfoRemoveFromList(dev, pBssInfo);
                    zfBssInfoFree(dev, pBssInfo);
                    pBssInfo = pNextBssInfo;
                }
                else
                {
                    pBssInfo = pBssInfo->next;
                }
            }
        }
    } //for( i=0; i<bssCount; i++ )
    return;
}