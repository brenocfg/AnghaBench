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
typedef  int /*<<< orphan*/  u8_t ;
typedef  int u32_t ;
typedef  int /*<<< orphan*/  u16_t ;
struct zsPmkidBssidInfo {int dummy; } ;
struct TYPE_4__ {int bssidCount; } ;
struct TYPE_5__ {TYPE_1__ pmkidInfo; } ;
struct TYPE_6__ {TYPE_2__ sta; } ;

/* Variables and functions */
 TYPE_3__* wd ; 
 int /*<<< orphan*/  zfMemoryCopy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zmw_get_wlan_dev (int /*<<< orphan*/ *) ; 

u32_t zfiWlanQueryPmkidInfo(zdev_t* dev, u8_t* buf, u32_t len)
{
    //struct zsPmkidInfo* pPmkidInfo = ( struct zsPmkidInfo* ) buf;
    u32_t  size;

    zmw_get_wlan_dev(dev);

    size = sizeof(u32_t) +
           wd->sta.pmkidInfo.bssidCount * sizeof(struct zsPmkidBssidInfo);

    if ( len < size )
    {
        return wd->sta.pmkidInfo.bssidCount;
    }

    zfMemoryCopy(buf, (u8_t*) &wd->sta.pmkidInfo, (u16_t) size);

    return 0;
}