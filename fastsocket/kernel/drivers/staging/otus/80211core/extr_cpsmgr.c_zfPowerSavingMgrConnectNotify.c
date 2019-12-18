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
struct TYPE_3__ {int powerSaveMode; } ;
struct TYPE_4__ {scalar_t__ wlanMode; int /*<<< orphan*/  beaconInterval; TYPE_1__ sta; } ;

/* Variables and functions */
 scalar_t__ ZM_MODE_INFRASTRUCTURE ; 
#define  ZM_STA_PS_FAST 131 
#define  ZM_STA_PS_LIGHT 130 
#define  ZM_STA_PS_MAX 129 
#define  ZM_STA_PS_NONE 128 
 TYPE_2__* wd ; 
 int /*<<< orphan*/  zfHpPowerSaveSetMode (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zmw_get_wlan_dev (int /*<<< orphan*/ *) ; 

void zfPowerSavingMgrConnectNotify(zdev_t *dev)
{
    zmw_get_wlan_dev(dev);

    if ( wd->wlanMode == ZM_MODE_INFRASTRUCTURE )
    {
        switch(wd->sta.powerSaveMode)
        {
            case ZM_STA_PS_NONE:
                zfHpPowerSaveSetMode(dev, 0, 0, wd->beaconInterval);
                break;

            case ZM_STA_PS_FAST:
            case ZM_STA_PS_MAX:
            case ZM_STA_PS_LIGHT:
                zfHpPowerSaveSetMode(dev, 0, 1, wd->beaconInterval);
                break;

            default:
                zfHpPowerSaveSetMode(dev, 0, 0, wd->beaconInterval);
                break;
        }
    }
}