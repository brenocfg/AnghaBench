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
struct TYPE_3__ {scalar_t__ powerSaveMode; scalar_t__ ibssPrevPSDataCount; scalar_t__ txBeaconInd; scalar_t__ recvAtim; } ;
struct TYPE_4__ {TYPE_1__ sta; } ;

/* Variables and functions */
 scalar_t__ ZM_STA_PS_NONE ; 
 TYPE_2__* wd ; 
 int /*<<< orphan*/  zfPowerSavingMgrOnHandleT1 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zm_debug_msg0 (char*) ; 
 int /*<<< orphan*/  zmw_get_wlan_dev (int /*<<< orphan*/ *) ; 

void zfPowerSavingMgrAtimWinExpired(zdev_t* dev)
{
    zmw_get_wlan_dev(dev);

//printk("zfPowerSavingMgrAtimWinExpired #1\n");
    if ( wd->sta.powerSaveMode == ZM_STA_PS_NONE )
    {
        return;
    }

//printk("zfPowerSavingMgrAtimWinExpired #2\n");
    // if we received any ATIM window from the others to indicate we have buffered data
    // at the other station, we can't go to sleep
    if ( wd->sta.recvAtim )
    {
        wd->sta.recvAtim = 0;
        zm_debug_msg0("Can't sleep due to receving ATIM window!");
        return;
    }

    // if we are the one to tx beacon during last beacon interval. we can't go to sleep
    // since we need to be alive to respond the probe request!
    if ( wd->sta.txBeaconInd )
    {
        zm_debug_msg0("Can't sleep due to just transmit a beacon!");
        return;
    }

    // If we buffer any data for the other stations. we could not go to sleep
    if ( wd->sta.ibssPrevPSDataCount != 0 )
    {
        zm_debug_msg0("Can't sleep due to buffering data for the others!");
        return;
    }

    // before sleeping, we still need to notify the others by transmitting null
    // pkt with power mgmt bit turned on.
    zfPowerSavingMgrOnHandleT1(dev);
}