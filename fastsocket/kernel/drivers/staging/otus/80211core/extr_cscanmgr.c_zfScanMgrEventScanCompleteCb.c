#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  zdev_t ;

/* Variables and functions */
 int /*<<< orphan*/  zfPowerSavingMgrIsSleeping (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zfSendNullData (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ zfStaIsConnected (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zmw_get_wlan_dev (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void zfScanMgrEventScanCompleteCb(zdev_t* dev)
{
    zmw_get_wlan_dev(dev);

    if ((zfStaIsConnected(dev)) && (!zfPowerSavingMgrIsSleeping(dev)))
    {
        zfSendNullData(dev, 0);
    }
    return;
}