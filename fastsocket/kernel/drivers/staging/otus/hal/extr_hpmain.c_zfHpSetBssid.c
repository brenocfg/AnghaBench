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
typedef  int /*<<< orphan*/  u8_t ;
typedef  int u32_t ;
typedef  int u16_t ;

/* Variables and functions */
 int /*<<< orphan*/  zfDelayWriteInternalReg (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  zfFlushDelayWrite (int /*<<< orphan*/ *) ; 

u16_t zfHpSetBssid(zdev_t* dev, u8_t* bssidSrc)
{
    u32_t  address;
    u16_t *bssid = (u16_t *)bssidSrc;

    address = bssid[0] + (((u32_t)bssid[1]) << 16);
    zfDelayWriteInternalReg(dev, 0x1c3618, address);

    address = (u32_t)bssid[2];
    zfDelayWriteInternalReg(dev, 0x1c361C, address);
    zfFlushDelayWrite(dev);
    return 0;
}