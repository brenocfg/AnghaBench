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
struct TYPE_3__ {int /*<<< orphan*/  powerSaveMode; } ;
struct TYPE_4__ {scalar_t__ wlanMode; TYPE_1__ sta; } ;

/* Variables and functions */
 scalar_t__ ZM_MODE_INFRASTRUCTURE ; 
 int /*<<< orphan*/  ZM_STA_PS_NONE ; 
 TYPE_2__* wd ; 
 int /*<<< orphan*/  zfPSDeviceSleep (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zfPowerSavingMgrSetMode (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zfSendNullData (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  zmw_get_wlan_dev (int /*<<< orphan*/ *) ; 

void zfiWlanSetPowerSaveMode(zdev_t* dev, u8_t mode)
{
#if 0
    zmw_get_wlan_dev(dev);

    wd->sta.powerSaveMode = mode;

    /* send null data with PwrBit to inform AP */
    if ( mode > ZM_STA_PS_NONE )
    {
        if ( wd->wlanMode == ZM_MODE_INFRASTRUCTURE )
        {
            zfSendNullData(dev, 1);
        }

        /* device into PS mode */
        zfPSDeviceSleep(dev);
    }
#endif

    zfPowerSavingMgrSetMode(dev, mode);
}