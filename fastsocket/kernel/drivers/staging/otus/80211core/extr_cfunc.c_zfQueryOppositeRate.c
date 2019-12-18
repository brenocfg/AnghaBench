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
typedef  int u8_t ;
struct TYPE_3__ {int mTxRate; int uTxRate; int mmTxRate; } ;
struct TYPE_4__ {scalar_t__ wlanMode; TYPE_1__ sta; } ;

/* Variables and functions */
 scalar_t__ ZM_IS_MULTICAST (int*) ; 
 scalar_t__ ZM_MODE_AP ; 
 int ZM_WLAN_DATA_FRAME ; 
 TYPE_2__* wd ; 
 int /*<<< orphan*/  zmw_get_wlan_dev (int /*<<< orphan*/ *) ; 

u8_t zfQueryOppositeRate(zdev_t* dev, u8_t dst_mac[6], u8_t frameType)
{
    zmw_get_wlan_dev(dev);

    /* For AP's rate adaption */
    if ( wd->wlanMode == ZM_MODE_AP )
    {
        return 0;
    }

    /* For STA's rate adaption */
    if ( (frameType & 0x0c) == ZM_WLAN_DATA_FRAME )
    {
        if ( ZM_IS_MULTICAST(dst_mac) )
        {
            return wd->sta.mTxRate;
        }
        else
        {
            return wd->sta.uTxRate;
        }
    }

    return wd->sta.mmTxRate;
}