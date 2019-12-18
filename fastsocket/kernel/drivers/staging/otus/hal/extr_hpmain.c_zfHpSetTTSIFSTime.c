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
typedef  int u8_t ;
typedef  int u32_t ;

/* Variables and functions */
 int /*<<< orphan*/  ZM_MAC_REG_EIFS_AND_SIFS ; 
 int /*<<< orphan*/  zfDelayWriteInternalReg (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  zfFlushDelayWrite (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zmw_get_wlan_dev (int /*<<< orphan*/ *) ; 

void zfHpSetTTSIFSTime(zdev_t* dev, u8_t sifs_time)
{
    u32_t reg_value = 0;
    zmw_get_wlan_dev(dev);

    sifs_time &= 0x3f;
    reg_value = 0x14400b | (((u32_t)sifs_time)<<24);

    zfDelayWriteInternalReg(dev, ZM_MAC_REG_EIFS_AND_SIFS, reg_value);
    zfFlushDelayWrite(dev);
}