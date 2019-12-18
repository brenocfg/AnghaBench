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
typedef  int u8_t ;
typedef  int u32_t ;
struct TYPE_4__ {scalar_t__ macAddr; int /*<<< orphan*/  size; } ;
struct TYPE_5__ {int osRxFilter; TYPE_1__ multicastList; } ;
struct TYPE_6__ {TYPE_2__ sta; } ;

/* Variables and functions */
 int ZM_PACKET_TYPE_ALL_MULTICAST ; 
 TYPE_3__* wd ; 
 int /*<<< orphan*/  zfHpSetMulticastList (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*,int) ; 
 int /*<<< orphan*/  zmw_get_wlan_dev (int /*<<< orphan*/ *) ; 

void zfiWlanSetPacketFilter(zdev_t* dev, u32_t PacketFilter)
{
    u8_t  bAllMulticast = 0;
    u32_t oldFilter;

    zmw_get_wlan_dev(dev);

    oldFilter = wd->sta.osRxFilter;

    wd->sta.osRxFilter = PacketFilter;

    if ((oldFilter & ZM_PACKET_TYPE_ALL_MULTICAST) !=
        (wd->sta.osRxFilter & ZM_PACKET_TYPE_ALL_MULTICAST))
    {
        if ( wd->sta.osRxFilter & ZM_PACKET_TYPE_ALL_MULTICAST )
            bAllMulticast = 1;
        zfHpSetMulticastList(dev, wd->sta.multicastList.size,
                             (u8_t*)wd->sta.multicastList.macAddr, bAllMulticast);
    }
}