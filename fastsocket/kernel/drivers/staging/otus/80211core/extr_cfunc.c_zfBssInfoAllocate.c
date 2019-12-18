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
typedef  int /*<<< orphan*/  u8_t ;
struct zsBssInfo {int dummy; } ;
struct TYPE_3__ {scalar_t__ bssInfoFreeCount; size_t bssInfoArrayHead; struct zsBssInfo** bssInfoArray; } ;
struct TYPE_4__ {TYPE_1__ sta; } ;

/* Variables and functions */
 int ZM_MAX_BSS ; 
 TYPE_2__* wd ; 
 int /*<<< orphan*/  zfZeroMemory (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  zmw_get_wlan_dev (int /*<<< orphan*/ *) ; 

struct zsBssInfo* zfBssInfoAllocate(zdev_t* dev)
{
    struct zsBssInfo* pBssInfo;

    zmw_get_wlan_dev(dev);

    if (wd->sta.bssInfoFreeCount == 0)
        return NULL;

    pBssInfo = wd->sta.bssInfoArray[wd->sta.bssInfoArrayHead];
    wd->sta.bssInfoArray[wd->sta.bssInfoArrayHead] = NULL;
    wd->sta.bssInfoArrayHead = (wd->sta.bssInfoArrayHead + 1) & (ZM_MAX_BSS - 1);
    wd->sta.bssInfoFreeCount--;

    zfZeroMemory((u8_t*)pBssInfo, sizeof(struct zsBssInfo));

    return pBssInfo;
}