#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zdev_t ;
struct TYPE_2__ {scalar_t__ wlanMode; } ;

/* Variables and functions */
 scalar_t__ ZM_MODE_IBSS ; 
 TYPE_1__* wd ; 
 int /*<<< orphan*/  zfPowerSavingMgrAtimWinExpired (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zmw_get_wlan_dev (int /*<<< orphan*/ *) ; 

void zfEndOfAtimWindowInterrupt(zdev_t* dev)
{
#ifdef ZM_ENABLE_IBSS_PS
    zmw_get_wlan_dev(dev);

    if ( wd->wlanMode == ZM_MODE_IBSS )
    {
        // Transmit any queued pkt for the stations!!
        zfPowerSavingMgrAtimWinExpired(dev);
    }
#endif
}