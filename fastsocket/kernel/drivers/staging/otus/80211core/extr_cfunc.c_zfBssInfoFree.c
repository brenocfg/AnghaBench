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
struct zsBssInfo {scalar_t__ sortValue; scalar_t__ signalQuality; scalar_t__ signalStrength; } ;
struct TYPE_3__ {size_t bssInfoArrayTail; int /*<<< orphan*/  bssInfoFreeCount; struct zsBssInfo** bssInfoArray; } ;
struct TYPE_4__ {TYPE_1__ sta; } ;

/* Variables and functions */
 int ZM_MAX_BSS ; 
 TYPE_2__* wd ; 
 int /*<<< orphan*/  zm_assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zmw_get_wlan_dev (int /*<<< orphan*/ *) ; 

void zfBssInfoFree(zdev_t* dev, struct zsBssInfo* pBssInfo)
{
    zmw_get_wlan_dev(dev);

    zm_assert(wd->sta.bssInfoArray[wd->sta.bssInfoArrayTail] == NULL);

    pBssInfo->signalStrength = pBssInfo->signalQuality = 0;
    pBssInfo->sortValue = 0;

    wd->sta.bssInfoArray[wd->sta.bssInfoArrayTail] = pBssInfo;
    wd->sta.bssInfoArrayTail = (wd->sta.bssInfoArrayTail + 1) & (ZM_MAX_BSS - 1);
    wd->sta.bssInfoFreeCount++;
}