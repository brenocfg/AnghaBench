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
typedef  int /*<<< orphan*/  u16_t ;
struct TYPE_6__ {size_t size; TYPE_1__* macAddr; } ;
struct TYPE_7__ {TYPE_2__ multicastList; } ;
struct TYPE_8__ {TYPE_3__ sta; } ;
struct TYPE_5__ {scalar_t__ addr; } ;

/* Variables and functions */
 TYPE_4__* wd ; 
 scalar_t__ zfwMemoryIsEqual (size_t*,size_t*,int) ; 
 int /*<<< orphan*/  zmw_get_wlan_dev (int /*<<< orphan*/ *) ; 

u8_t zfiCompareWithMulticastListAddress(zdev_t* dev, u16_t* dstMacAddr)
{
    u8_t i;
    u8_t bIsInMCListAddr = 0;

    zmw_get_wlan_dev(dev);

    for ( i=0; i<wd->sta.multicastList.size; i++ )
    {
    	if ( zfwMemoryIsEqual((u8_t*)dstMacAddr, (u8_t*)wd->sta.multicastList.macAddr[i].addr, 6) )
    	{
            bIsInMCListAddr = 1;
            break;
    	}
    }

    return bIsInMCListAddr;
}