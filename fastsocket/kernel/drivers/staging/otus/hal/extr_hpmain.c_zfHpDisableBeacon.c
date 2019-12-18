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
struct zsHpPriv {scalar_t__ ibssBcnEnabled; } ;
struct TYPE_2__ {scalar_t__ hpPrivate; } ;

/* Variables and functions */
 int /*<<< orphan*/  ZM_MAC_REG_BCN_PERIOD ; 
 TYPE_1__* wd ; 
 int /*<<< orphan*/  zfDelayWriteInternalReg (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zfFlushDelayWrite (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zmw_get_wlan_dev (int /*<<< orphan*/ *) ; 

void zfHpDisableBeacon(zdev_t* dev)
{
    zmw_get_wlan_dev(dev);

    ((struct zsHpPriv*)wd->hpPrivate)->ibssBcnEnabled = 0;

    zfDelayWriteInternalReg(dev, ZM_MAC_REG_BCN_PERIOD, 0);
    zfFlushDelayWrite(dev);
}