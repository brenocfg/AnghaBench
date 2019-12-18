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
typedef  int /*<<< orphan*/  u16_t ;
struct TYPE_5__ {TYPE_1__* oppositeInfo; } ;
struct TYPE_6__ {TYPE_2__ sta; } ;
struct TYPE_4__ {scalar_t__ pkInstalled; } ;

/* Variables and functions */
 TYPE_3__* wd ; 
 scalar_t__ zfStaFindOppositeByMACAddr (int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__*) ; 
 int /*<<< orphan*/  zmw_declare_for_critical_section () ; 
 int /*<<< orphan*/  zmw_enter_critical_section (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zmw_get_wlan_dev (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zmw_leave_critical_section (int /*<<< orphan*/ *) ; 

u8_t zfiWlanQueryIsPKInstalled(zdev_t *dev, u8_t *staMacAddr)
{
    u8_t isInstalled = 0;

#if 1
//#ifdef ZM_ENABLE_IBSS_WPA2PSK
    u8_t   res, peerIdx;

    zmw_get_wlan_dev(dev);

    zmw_declare_for_critical_section();

    zmw_enter_critical_section(dev);
    res = zfStaFindOppositeByMACAddr(dev, (u16_t *)staMacAddr, &peerIdx);
    if( res == 0 )
    {
        isInstalled = wd->sta.oppositeInfo[peerIdx].pkInstalled;
    }
    zmw_leave_critical_section(dev);
//#endif
#endif

    return isInstalled;
}