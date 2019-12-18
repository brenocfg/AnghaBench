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
typedef  int u32_t ;
struct zsHpPriv {int eepromImageRdReq; } ;
struct TYPE_2__ {scalar_t__ hpPrivate; } ;

/* Variables and functions */
 int /*<<< orphan*/  ZM_EEPROM_READ ; 
 int ZM_HAL_MAX_EEPROM_PRQ ; 
 TYPE_1__* wd ; 
 int zfIssueCmd (int /*<<< orphan*/ *,int*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zmw_get_wlan_dev (int /*<<< orphan*/ *) ; 

u32_t zfHpLoadEEPROMFromFW(zdev_t* dev)
{
    u32_t cmd[16];
    u32_t ret=0, i, j;
    zmw_get_wlan_dev(dev);

    i = ((struct zsHpPriv*)wd->hpPrivate)->eepromImageRdReq;

    cmd[0] = ZM_HAL_MAX_EEPROM_PRQ*4;

    for (j=0; j<ZM_HAL_MAX_EEPROM_PRQ; j++)
    {
        cmd[j+1] = 0x1000 + (((i*ZM_HAL_MAX_EEPROM_PRQ) + j)*4);
    }

    ret = zfIssueCmd(dev, cmd, (ZM_HAL_MAX_EEPROM_PRQ+1)*4, ZM_EEPROM_READ, 0);

    return ret;
}