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
typedef  scalar_t__ u8_t ;
typedef  int u32_t ;
typedef  scalar_t__ u16_t ;
struct zsHpPriv {int ibssBcnEnabled; int ibssBcnInterval; } ;
struct TYPE_2__ {scalar_t__ hpPrivate; } ;

/* Variables and functions */
 int ZM_BEACON_BUFFER_ADDRESS ; 
 int /*<<< orphan*/  ZM_MAC_REG_BCN_ADDR ; 
 int /*<<< orphan*/  ZM_MAC_REG_BCN_CTRL ; 
 int /*<<< orphan*/  ZM_MAC_REG_BCN_PERIOD ; 
 int /*<<< orphan*/  ZM_MAC_REG_PRETBTT ; 
 scalar_t__ ZM_MODE_AP ; 
 scalar_t__ ZM_MODE_IBSS ; 
 TYPE_1__* wd ; 
 int /*<<< orphan*/  zfDelayWriteInternalReg (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  zfFlushDelayWrite (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zmw_get_wlan_dev (int /*<<< orphan*/ *) ; 

void zfHpEnableBeacon(zdev_t* dev, u16_t mode, u16_t bcnInterval, u16_t dtim, u8_t enableAtim)
{
    u32_t  value;

    zmw_get_wlan_dev(dev);

    /* Beacon Ready */
    zfDelayWriteInternalReg(dev, ZM_MAC_REG_BCN_CTRL, 0);
    /* Beacon DMA buffer address */
    zfDelayWriteInternalReg(dev, ZM_MAC_REG_BCN_ADDR, ZM_BEACON_BUFFER_ADDRESS);

    value = bcnInterval;

    value |= (((u32_t) dtim) << 16);

    if (mode == ZM_MODE_AP)
    {

        value |= 0x1000000;
    }
    else if (mode == ZM_MODE_IBSS)
    {
        value |= 0x2000000;

		if ( enableAtim )
		{
			value |= 0x4000000;
		}
		((struct zsHpPriv*)wd->hpPrivate)->ibssBcnEnabled = 1;
        ((struct zsHpPriv*)wd->hpPrivate)->ibssBcnInterval = value;
    }
    zfDelayWriteInternalReg(dev, ZM_MAC_REG_PRETBTT, (bcnInterval-6)<<16);

    /* Beacon period and beacon enable */
    zfDelayWriteInternalReg(dev, ZM_MAC_REG_BCN_PERIOD, value);
    zfFlushDelayWrite(dev);
}