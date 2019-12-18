#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zdev_t ;
typedef  size_t u8_t ;
struct zsMulticastAddr {int /*<<< orphan*/  addr; } ;
struct TYPE_7__ {size_t size; TYPE_1__* macAddr; } ;
struct TYPE_6__ {int osRxFilter; TYPE_3__ multicastList; } ;
struct TYPE_8__ {TYPE_2__ sta; } ;
struct TYPE_5__ {int /*<<< orphan*/  addr; } ;

/* Variables and functions */
 int ZM_PACKET_TYPE_ALL_MULTICAST ; 
 TYPE_4__* wd ; 
 int /*<<< orphan*/  zfHpSetMulticastList (int /*<<< orphan*/ *,size_t,size_t*,size_t) ; 
 int /*<<< orphan*/  zfMemoryCopy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  zmw_get_wlan_dev (int /*<<< orphan*/ *) ; 

void zfiWlanSetMulticastList(zdev_t* dev, u8_t size, u8_t* pList)
{
    struct zsMulticastAddr* pMacList = (struct zsMulticastAddr*) pList;
    u8_t   i;
    u8_t   bAllMulticast = 0;
    //u32_t  value;

    zmw_get_wlan_dev(dev);

    wd->sta.multicastList.size = size;
    for(i=0; i<size; i++)
    {
        zfMemoryCopy(wd->sta.multicastList.macAddr[i].addr,
                     pMacList[i].addr, 6);
    }

    if ( wd->sta.osRxFilter & ZM_PACKET_TYPE_ALL_MULTICAST )
        bAllMulticast = 1;
    zfHpSetMulticastList(dev, size, pList, bAllMulticast);

}